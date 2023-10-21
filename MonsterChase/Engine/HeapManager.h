#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

#include <cstddef>

namespace HeapManagerProxy
{
    struct MemoryBlock
    {
        void* pBaseAddress;
        size_t BlockSize;
        struct MemoryBlock* pNextBlock;
    };

    class HeapManager
    {
    public:
        HeapManager(void* pHeapMemory, size_t heapSize, unsigned int numDescriptors);
        ~HeapManager();

        void* alloc(size_t i_size);
        bool IsAllocated(void* p_memory);
        MemoryBlock* FindAllocatedMemoryBlock(void* p_memory);
        void RemoveFromAllocatedList(MemoryBlock* memory_block);
        void AddToFreeList(MemoryBlock* memory_block);
        void MergeAdjacentFreeBlocks(MemoryBlock* memory_block);
        bool free(void* pMemory);
        bool Contains(void* pMemory) const;

    private:
        MemoryBlock TheHeap;
        MemoryBlock* pFreeMemoryBlockList; // Linked list of free blocks
        MemoryBlock* pOutstandingAllocationList; // Linked list of allocated blocks

        MemoryBlock* GetFreeMemoryBlock();
        void TrackAllocation(MemoryBlock* pBlock);
        // Other private helper methods
    };

    HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, unsigned int numDescriptors);
}



#endif // HEAP_ALLOCATOR_H
