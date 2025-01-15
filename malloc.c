#include <stdio.h>
#include <stdint.h>

#define SIZE        (100 * 1024 * 1024)
#define ALIGN(size) ((size + 7) & ~7)
#define TRUE        1
#define FALSE       0

typedef struct Block
{
    size_t        size;
    uint8_t       isFree;
    struct Block* next;
} block_t;

static uint8_t  memoryPool[SIZE] = {};
static block_t* freeList         = NULL;

void initializeMemory()
{
    freeList         = (block_t*)memoryPool;
    freeList->size   = SIZE - sizeof(block_t);
    freeList->isFree = TRUE;
    freeList->next   = NULL;
}

block_t* findFreeBlock(const size_t size)
{
    block_t* block = freeList;
    while (NULL != block)
    {
        if ((TRUE == block->isFree) && (size <= block->size))
        {
            printf("Free block found at %#llx, size %lu\n", (uint64_t)block, block->size);
            return block;
        }
        block = block->next;
    }
    return NULL;
}

void splitBlock(block_t* pBlock, const size_t size)
{
    block_t* newBlock = (block_t*)((uint8_t*)pBlock + size + sizeof(block_t));
    newBlock->isFree  = TRUE;
    newBlock->next    = pBlock->next;
    newBlock->size    = pBlock->size - size - sizeof(block_t);

    printf("Block split: %#llx size= %lu  into newSize %lu | newBlock %#llx newSize %lu\n", (uint64_t)pBlock, pBlock->size, size, (uint64_t)newBlock, newBlock->size);
    pBlock->size = size;
    pBlock->next = newBlock;

}

void mergeBlocks()
{
    block_t* block = freeList;
    while ((NULL != block) && (NULL != block->next))
    {
        if ((TRUE == block->isFree) && (TRUE == block->next->isFree))
        {
            block->size += block->next->size + sizeof(block_t);
        }
        block->next = block->next->next;
    }
}

void* alloc(size_t size)
{
    if ((0 == size) || (SIZE - sizeof(block_t) < size))
    {
        return NULL;
    }
    size = ALIGN(size);

    block_t* block = findFreeBlock(size);
    if (NULL != block)
    {
        if ((size + sizeof(block_t)) < block->size)
        {
            splitBlock(block, size);
        }
        block->isFree = FALSE;
    }
    return (void*)((uint8_t*)block + sizeof(block_t));
}

void freeBlock(void* ptr)
{
    if (NULL == ptr)
    {
        return;
    }
    block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    block->isFree  = TRUE;
    mergeBlocks();
}

void printMemoryBlock()
{
    block_t* block = freeList;
    while (NULL != block) {
        printf("Block %#llx, isFree %hhu, size %lu, next %#llx\n", (uint64_t)block, block->isFree, block->size, (uint64_t)block->next);
        block = block->next;
    }
}

int main()
{
    initializeMemory();
    printf("Allocating memory\n");
    void* ptr = alloc(1024);
    void* ptr2 = alloc(1024);

    printf("Memory after allocation\n");
    printMemoryBlock();

    printf("Deallocating memory\n");
    freeBlock(ptr);
    freeBlock(ptr2);

    printf("Memory blocks after deallocation\n");
    printMemoryBlock();
}
