#include "HeapManager.h"
#include <Windows.h> // For HeapAlloc and VirtualAlloc
#include <cstdio>
#include <tuple>

namespace HeapManagerProxy
{

	HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, unsigned int numDescriptors)
	{
		assert(pHeapMemory != nullptr);
		assert(heapSize > 0);
		
		HeapManager* pHeapManager = new HeapManager(pHeapMemory, heapSize, numDescriptors);

		return pHeapManager;
	}
	
	void Destroy(HeapManager* pHeapManager)
	{
		assert(pHeapManager != nullptr);
		
		delete pHeapManager;
	}
	
	HeapManager::HeapManager(void* pHeapMemory, size_t heapSize, unsigned numDescriptors)
	{
		assert(pHeapMemory != nullptr);
		assert(heapSize > 0);

		// Initialize the linked list of free memory blocks
		pFreeMemoryBlockList = static_cast<MemoryBlock*>(pHeapMemory);
		pFreeMemoryBlockList->pBaseAddress = pHeapMemory;
		pFreeMemoryBlockList->BlockSize = heapSize;
		pFreeMemoryBlockList->pNextBlock = nullptr;

		// Initialize the linked list of outstanding allocations (empty at the start)
		pOutstandingAllocationList = nullptr;

		this->theHeapSize = heapSize;

		pEntireHeap = pFreeMemoryBlockList;
	}

	HeapManager::~HeapManager()
    {
		delete pEntireHeap;
	}


	std::pair<MemoryBlock*, MemoryBlock*> HeapManager::findFreeBlock(size_t size)
	{
		MemoryBlock* currentBlock = pFreeMemoryBlockList;
		MemoryBlock* previousBlock = nullptr;
		while (currentBlock)
		{
			if (currentBlock->BlockSize >= size)
			{
				return {currentBlock, previousBlock};
			}
			previousBlock = currentBlock;
			currentBlock = currentBlock->pNextBlock;
		}
		return {nullptr, nullptr};
	}
	
	void* HeapManager::alloc(size_t size)
	{
		assert(size > 0);
		
		auto [suitableBlock, previousBlock] = findFreeBlock(size);

		// If no suitable block is found, attempt to defragment the heap
		if (!suitableBlock)
		{
			Collect();
			std::tie(suitableBlock, previousBlock) = findFreeBlock(size);
		}

		// If a suitable block is still not found after defragmentation, return nullptr
		if (!suitableBlock)
		{
			return nullptr;
		}
		

		MemoryBlock* newBlock = suitableBlock;
		newBlock->pBaseAddress = suitableBlock->pBaseAddress;
		newBlock->BlockSize = size;

		// Adjust the suitableBlock to account for the allocated memory
		suitableBlock->pBaseAddress = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(suitableBlock->pBaseAddress) + size);
		suitableBlock->BlockSize -= size;
		
		// If the block's size is reduced to 0, remove it from the free list
		if (suitableBlock->BlockSize == 0)
		{
			if (previousBlock)
			{
				previousBlock->pNextBlock = suitableBlock->pNextBlock;
			}
			else
			{
				pFreeMemoryBlockList = suitableBlock->pNextBlock;
			}
		}

		// track allocation
		newBlock->pNextBlock = pOutstandingAllocationList;
		pOutstandingAllocationList = newBlock;

		return newBlock->pBaseAddress;
	}
	
    bool HeapManager::free(void* ptr)
    {
        assert(ptr);

        // Find the block in the outstanding allocation list
        MemoryBlock* currentBlock = pOutstandingAllocationList;
        MemoryBlock* previousBlock = nullptr;

        while (currentBlock)
        {
            if (currentBlock->pBaseAddress == ptr)
            {
                // Found the block to free

                // Remove the block from the outstanding allocation list
                if (previousBlock)
                {
                    previousBlock->pNextBlock = currentBlock->pNextBlock;
                }
                else
                {
                    pOutstandingAllocationList = currentBlock->pNextBlock;
                }

                // Add the block back to the free memory block list
                currentBlock->pNextBlock = pFreeMemoryBlockList;
                pFreeMemoryBlockList = currentBlock;

                return true;
            }

            previousBlock = currentBlock;
            currentBlock = currentBlock->pNextBlock;
        }

        // Block not found in the outstanding allocation list
        return false;
    }

	void HeapManager::ShowFreeBlocks() const
	{
		printf("Free Blocks:\n");
		MemoryBlock* currentBlock = pFreeMemoryBlockList;
		while (currentBlock)
		{
			printf("Base Address: %p, Size: %zu bytes\n", currentBlock->pBaseAddress, currentBlock->BlockSize);
			currentBlock = currentBlock->pNextBlock;
		}
	}

	void HeapManager::ShowOutstandingAllocations() const
	{
		printf("Outstanding Allocations:\n");
		MemoryBlock* currentBlock = pOutstandingAllocationList;
		while (currentBlock)
		{
			printf("Base Address: %p, Size: %zu bytes\n", currentBlock->pBaseAddress, currentBlock->BlockSize);
			currentBlock = currentBlock->pNextBlock;
		}
	}

	size_t HeapManager::GetLargestFreeBlock() const
	{
		size_t largestSize = 0;
		MemoryBlock* currentBlock = pFreeMemoryBlockList;
		while (currentBlock)
		{
			if (currentBlock->BlockSize > largestSize)
			{
				largestSize = currentBlock->BlockSize;
			}
			currentBlock = currentBlock->pNextBlock;
		}
		return largestSize;
	}

	bool HeapManager::Contains(void* ptr) const
	{
		uintptr_t heapStart = reinterpret_cast<uintptr_t>(pEntireHeap->pBaseAddress);
		uintptr_t heapEnd = heapStart + pEntireHeap->BlockSize;
		uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
		return address >= heapStart && address < heapEnd;
	}

	bool HeapManager::IsAllocated(void* ptr) const
	{
		MemoryBlock* currentBlock = pOutstandingAllocationList;
		while (currentBlock)
		{
			if (currentBlock->pBaseAddress == ptr)
			{
				return true;
			}
			currentBlock = currentBlock->pNextBlock;
		}
		return false;
	}
	
	void HeapManager::Collect()
	{
		bool bShouldMerge;

		do
		{
			bShouldMerge = false;
			MemoryBlock* currentBlock = pFreeMemoryBlockList;

			while (currentBlock && currentBlock->pNextBlock)
			{
				uintptr_t currentBlockEnd = reinterpret_cast<uintptr_t>(currentBlock->pBaseAddress) + currentBlock->BlockSize;
				uintptr_t nextBlockStart = reinterpret_cast<uintptr_t>(currentBlock->pNextBlock->pBaseAddress);

				// Check if the current block and the next block are adjacent
				if (currentBlockEnd == nextBlockStart)
				{
					// Merge the blocks
					currentBlock->BlockSize += currentBlock->pNextBlock->BlockSize;

					// Remove the next block from the list
					MemoryBlock* blockToRemove = currentBlock->pNextBlock;
					currentBlock->pNextBlock = blockToRemove->pNextBlock;

					// merging two blocks might create a new opportunity for further merging
					bShouldMerge = true;
				}
				else
				{
					currentBlock = currentBlock->pNextBlock;
				}
			}
		} while (bShouldMerge);
	}

	
}


