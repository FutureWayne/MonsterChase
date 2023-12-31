#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

#include <cstddef>
#include <utility>
#include <cassert>

namespace HeapManagerProxy
{
    struct MemoryBlock
    {
        void* pBaseAddress;
        size_t BlockSize;
        MemoryBlock* pNextBlock;
    };

    class HeapManager
    {
    public:
        HeapManager(void* pHeapMemory, size_t heapSize, unsigned int numDescriptors);
        ~HeapManager();
        
        void ShowFreeBlocks() const;
        void ShowOutstandingAllocations() const;
        size_t GetLargestFreeBlock() const;
        bool Contains(void* ptr) const;
        bool IsAllocated(void* ptr) const;
        void Collect();

        void* alloc(const size_t size, size_t alignment);
        bool free(void* ptr);
    
    private:
        
        std::pair<MemoryBlock*, MemoryBlock*> findFreeBlock(size_t size);
        
        size_t m_heapSize;
        void* pHeapBaseAddress;
        MemoryBlock* pFreeMemoryBlockList; // Linked list of free blocks
        MemoryBlock* pOutstandingAllocationList; // Linked list of allocated blocks
    };

    HeapManager* CreateHeapManager(void* pHeapMemory, size_t heapSize, unsigned int numDescriptors);

    void Destroy(HeapManager* pHeapManager);

    void* alloc(HeapManager* pHeapManager, const size_t size);

    inline void* alloc(HeapManager* pHeapManager, size_t size, size_t alignment)
    {
        assert(pHeapManager != nullptr);

        return pHeapManager->alloc(size, alignment);
    }

    inline void Collect(HeapManager* pHeapManager)
    {
        pHeapManager->Collect();
    }

    inline bool free(HeapManager* pHeapManager, void* ptr)
    {
        return pHeapManager->free(ptr);
    }

    inline void ShowFreeBlocks(HeapManager* pHeapManager)
    {
        pHeapManager->ShowFreeBlocks();
    }

    inline void ShowOutstandingAllocations(HeapManager* pHeapManager)
    {
        pHeapManager->ShowOutstandingAllocations();
    }

    inline size_t GetLargestFreeBlock(HeapManager* pHeapManager)
    {
        return pHeapManager->GetLargestFreeBlock();
    }

    inline bool Contains(HeapManager* pHeapManager, void* ptr)
    {
        return pHeapManager->Contains(ptr);
    }

    inline bool IsAllocated(HeapManager* pHeapManager, void* ptr)
    {
        return pHeapManager->IsAllocated(ptr);
    }

    
}

#endif // HEAP_ALLOCATOR_H
