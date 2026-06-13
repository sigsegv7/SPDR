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

#define PMA_TO_VMA(PMA) \
    PTR_OFFSET((VOID *)PMA, KeBpalLoadBase())
#define VMA_TO_PMA(VMA) \
    (UPTR)PTR_NOFFSET(VMA, KeBpalLoadBase())

#endif  /* !_MM_VMM_H_ */
