/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: MMIO helpers
 * Author:      Chloe M.
 */

#ifndef _MU_MMIO_H_
#define _MU_MMIO_H_ 1

#include <stdef.h>

/* Builds mmio_write<n> functions */
#define _MMIO_WRITE_BUILDER(NAME, TYPE)         \
    static inline void                          \
    MMIO##NAME(volatile TYPE *ptr, TYPE val)   \
    {                                           \
        BARRIER();                            \
        *(volatile TYPE *)ptr = val;            \
    }

/* Builds mmio_read<n> functions */
#define _MMIO_READ_BUILDER(NAME, TYPE)      \
    static inline TYPE                      \
    MMIO##NAME(volatile TYPE *ptr)          \
    {                                       \
        BARRIER();                        \
        return *(volatile TYPE *)ptr;       \
    }

/* mmio_write<n> */
_MMIO_WRITE_BUILDER(Write8, UCHAR);
_MMIO_WRITE_BUILDER(Write16, USHORT);
_MMIO_WRITE_BUILDER(Write32, ULONG);
#if __SIZEOF_SIZE_T__ == 8
_MMIO_WRITE_BUILDER(Write64, UQUAD);
#endif

/* Builds mmio_read<n> functions */
_MMIO_READ_BUILDER(Read8, UCHAR);
_MMIO_READ_BUILDER(Read16, USHORT);
_MMIO_READ_BUILDER(Read32, ULONG);
#if __SIZEOF_SIZE_T__ == 8
_MMIO_READ_BUILDER(Read64, UQUAD);
#endif

#endif  /* !_MU_MMIO_H_ */
