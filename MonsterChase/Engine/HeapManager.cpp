#include "HeapManager.h"
#include <Windows.h> // For HeapAlloc and VirtualAlloc
#include <cassert>

namespace HeapManagerProxy
{
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
	}

	HeapManager::~HeapManager()
    {
		// Cleanup logic here, like releasing allocated memory blocks and the heap itself
	}
    

	void* HeapManager::alloc(size_t size)
	{
		assert(size > 0);

		MemoryBlock* currentBlock = pFreeMemoryBlockList;
		MemoryBlock* previousBlock = nullptr;

		while (currentBlock)
		{
			if (currentBlock->BlockSize >= size)
			{
				// Found a suitable block

				// Adjust the size of the current block
				currentBlock->BlockSize -= size;

				// Create a new block for the allocation
				MemoryBlock* newBlock = nullptr;
				newBlock->pBaseAddress = currentBlock->pBaseAddress;
				newBlock->BlockSize = size;

				// track allocation
				newBlock->pNextBlock = pOutstandingAllocationList;
				pOutstandingAllocationList = newBlock;

				// Adjust the free memory block list
				if (currentBlock->BlockSize == 0)
				{
					if (previousBlock)
					{
						previousBlock->pNextBlock = currentBlock->pNextBlock;
					}
					else
					{
						pFreeMemoryBlockList = currentBlock->pNextBlock;
					}
				}

				return newBlock->pBaseAddress;
			}

			previousBlock = currentBlock;
			currentBlock = currentBlock->pNextBlock;
		}

		// No suitable block found
		return nullptr;
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
	
}


