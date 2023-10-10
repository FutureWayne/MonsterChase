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

	HeapManager::~HeapManager() {
		// Cleanup logic here, like releasing allocated memory blocks and the heap itself
	}

	void* HeapManager::malloc(size_t i_size) {
		MemoryBlock* pBlock = GetFreeMemoryBlock();
		assert(pBlock); // Ensure a free block is available

		pBlock->pBaseAddress = TheHeap.pBaseAddress;
		pBlock->BlockSize = i_size;
		TrackAllocation(pBlock);

		// Shrink the heap
		TheHeap.pBaseAddress = static_cast<char*>(TheHeap.pBaseAddress) + i_size;
		TheHeap.BlockSize -= i_size;

		return pBlock->pBaseAddress;
	}

	MemoryBlock* HeapManager::GetFreeMemoryBlock() {
		// Pop a free block from the free blocks list
		if (!pFreeMemoryBlockList) return nullptr; // Return nullptr if no free blocks are available

		MemoryBlock* pBlock = pFreeMemoryBlockList;
		pFreeMemoryBlockList = pFreeMemoryBlockList->pNextBlock; // Update the head of the free blocks list
		return pBlock;
	}

	void HeapManager::TrackAllocation(MemoryBlock* pBlock) {
		// Push the allocated block onto the allocated blocks list
		pBlock->pNextBlock = pOutstandingAllocationList;
		pOutstandingAllocationList = pBlock;
	}

	HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, unsigned int numDescriptors) {
		// You might dynamically allocate the HeapAllocator instance here.
		// However, remember to properly deallocate it later to avoid memory leaks.
		auto* pHeapManager = new HeapManager(pHeapMemory, heapSize, numDescriptors);
		return pHeapManager;
	}
	
}


