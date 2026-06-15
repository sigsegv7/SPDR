/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Pool allocator
 * Author:      Chloe M.
 */

#ifndef _EX_POOL_H_
#define _EX_POOL_H_ 1

#include <stapi/status.h>
#include <ke/spinlock.h>
#include <stdef.h>

/* Minimum log2(size) */
#define MIN_LOG2 3

/*  Number of block entries per pool */
#define POOL_ENTRIES 8

/* Pages per pool block */
#define POOL_BLOCK_PAGES 8

/* Obtain pool granulartiy at a level */
#define POOL_GRAN(X) \
    (1 << ((MIN_LOG2 + (X))))

/*
 * Valid pool types
 *
 * @NON_PAGED_POOL: Not pagable to disk
 */
typedef enum {
    NON_PAGED_POOL
} POOL_TYPE;

/*
 * Represents a block of memory within a pool
 *
 * @Block: Memory backed by pool
 * @Bitmap: Block bitmap (1: allocated, 0: free)
 * @Next:   Next block
 */
typedef struct _EX_POOL_BLOCK {
    VOID *Block;
    UQUAD Bitmap;
    struct _EX_POOL_BLOCK *Next;
} EX_POOL_BLOCK;

/*
 * Represents an actual pool of memory
 *
 * @BlockList: List of allocatable blocks
 * @Lock: Lock protecting the block list
 */
typedef struct {
    EX_POOL_BLOCK BlockList[POOL_ENTRIES];
    KE_SPINLOCK Lock;
} EX_POOL;

/*
 * Initialize a pool
 *
 * @Pool: Pool to initialize
 */
ST_STATUS ExInitPool(EX_POOL *Pool);

/*
 * Allocate pool with an assigned tag
 *
 * @Type:   Pool type
 * @Count:  Number of bytes to allocate
 * @Tag:    Tag to assign to pool
 *
 * Returns memory base on success, otherwise NULL on failure
 */
VOID *ExAllocatePoolWithTag(POOL_TYPE Type, USIZE Count, ULONG Tag);

#endif  /* !_EX_POOL_H_ */
