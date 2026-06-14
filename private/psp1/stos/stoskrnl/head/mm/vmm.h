/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Virtual memory management
 * Author:      Chloe M.
 */

#ifndef _MM_VMM_H_
#define _MM_VMM_H_ 1

#include <stdef.h>
#include <ke/bpal.h>

#define VALLOC_BASE 0xFFFF804000000000

#define PMA_TO_VMA(PMA) \
    PTR_OFFSET((VOID *)PMA, KeBpalLoadBase())
#define VMA_TO_PMA(VMA) \
    (UPTR)PTR_NOFFSET(VMA, KeBpalLoadBase())

/*
 * Initialize the virtual memory manager
 */
void MmVmmInit(VOID);

#endif  /* !_MM_VMM_H_ */
