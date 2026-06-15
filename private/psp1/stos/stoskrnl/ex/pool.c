/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Pool allocator
 * Author:      Chloe M.
 */

#include <ex/pool.h>
#include <hal/kpcr.h>
#include <mm/page.h>
#include <stdef.h>

#include <ex/trace.h>

/*
 * Initialize a pool block
 *
 * @Block: Pool block to initialize
 */
static ST_STATUS
InitPoolBlock(EX_POOL_BLOCK *Block)
{
    if (Block == NULL) {
        return STATUS_INVALID_PARAM;
    }

    Block->Bitmap = 0;
    Block->Next = NULL;
    Block->Block = MmRequestPages(POOL_BLOCK_PAGES);
    if (Block->Block == NULL) {
        return STATUS_NO_MEMORY;
    }

    return STATUS_SUCCESS;
}

/*
 * Allocate a number of chunks from a block
 *
 * @Block: Block to allocate chunks from
 * @BlockIndex: Index of block
 * @Count: Number of bytes to allocate
 */
static VOID *
AllocateFromBlock(EX_POOL_BLOCK *Block, USIZE BlockIndex, USIZE Count)
{
    USIZE Gran, Idx;
    USIZE BitsNeeded, BitsFound = 0;
    SSIZE BitBase = -1;

    if (Block == NULL) {
        return NULL;
    }

    Gran = POOL_GRAN(BlockIndex);
    BitsNeeded = Count / Gran;

    for (Idx = 0; Idx < sizeof(Block->Bitmap) * 8; ++Idx) {
        if (!TESTBIT(&Block->Bitmap, Idx) && BitsFound < BitsNeeded) {
            if (BitBase < 0)
                BitBase = Idx;

            ++BitsFound;
        } else if (TESTBIT(&Block->Bitmap, Idx)) {
            BitBase = -1;
            BitsFound = 0;
        }

        if (BitsFound >= BitsNeeded) {
            break;
        }
    }

    for (Idx = BitBase; Idx < BitBase + BitsNeeded; ++Idx) {
        SETBIT(&Block->Bitmap, Idx);
    }

    return (BitsFound >= BitsNeeded)
        ? PTR_OFFSET(Block->Block, BitBase * Gran)
        : NULL;
}

/*
 * TODO: Add a block header and use the tag
 */
static VOID *
AllocatePoolWithTag(POOL_TYPE Type, USIZE Count, ULONG Tag)
{
    KPCR *Kpcr;
    EX_POOL_BLOCK *Block;
    EX_POOL *Pool;
    SHORT BlockIndex = 0;
    USIZE TmpCount;
    VOID *Base;

    Kpcr = HalKpcrSelf();
    if (Kpcr == NULL) {
        return NULL;
    }

    Pool = &Kpcr->Pool;

    /*
     * Obtain the block index with the formula:
     *
     * i = (log2(count) - MIN_LOG2) - 1
     */
    Count = ALIGN_UP(Count, POOL_GRAN(0));
    TmpCount = Count;
    while (TmpCount != 0) {
        ++BlockIndex;
        TmpCount >>= 1;
    }

    KeSpinLockAcq(&Pool->Lock, true);
    BlockIndex -= (MIN_LOG2 + 1);
    BlockIndex %= POOL_ENTRIES;
    Block = &Pool->BlockList[BlockIndex];
    Base = AllocateFromBlock(Block, BlockIndex, Count);
    KeSpinLockRel(&Pool->Lock);
    return Base;
}

VOID *
ExAllocatePoolWithTag(POOL_TYPE Type, USIZE Count, ULONG Tag)
{
    if (Count == 0) {
        return NULL;
    }

    /* Verify the type */
    switch (Type) {
    case NON_PAGED_POOL:
        break;
    default:
        return NULL;
    }

    return AllocatePoolWithTag(Type, Count, Tag);
}

ST_STATUS
ExInitPool(EX_POOL *Pool)
{
    ST_STATUS Status;
    EX_POOL_BLOCK *Block;
    USIZE Idx;

    if (Pool == NULL) {
        return STATUS_INVALID_PARAM;
    }

    for (Idx = 0; Idx < POOL_ENTRIES; ++Idx) {
        Block = &Pool->BlockList[Idx];
        Status = InitPoolBlock(Block);
        if (Status != STATUS_SUCCESS) {
            return Status;
        }
    }

    return STATUS_SUCCESS;
}
