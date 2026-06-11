/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Port I/O helpers
 * Author:      Chloe M.
 */

#ifndef _MACHINE_PIO_H_
#define _MACHINE_PIO_H_ 1

#include <stdef.h>

ALWAYS_INLINE static inline UCHAR
MdInb(USHORT Port)
{
    UCHAR result;
    ASMV("in %%dx, %%al" : "=a" (result) : "d" (Port));
    return result;
}

ALWAYS_INLINE static inline USHORT
MdInw(USHORT Port)
{
    USHORT Val;
    ASMV("inw %w1, %w0" : "=a" (Val) : "Nd" (Port));
    return Val;
}

ALWAYS_INLINE static inline ULONG
MdInl(USHORT Port)
{
    ULONG Val;
    ASMV("inl %w1, %0" : "=a" (Val) : "Nd" (Port));
    return Val;
}

ALWAYS_INLINE static inline VOID
MdOutb(USHORT Port, UCHAR Val)
{
    ASMV("out %%al, %%dx" : :"a" (Val), "d" (Port));
}

ALWAYS_INLINE static inline VOID
MdOutw(USHORT Port, USHORT Val)
{
    ASMV("outw %w0, %w1" : : "a" (Val), "Nd" (Port));
}

ALWAYS_INLINE static inline VOID
MdOutl(USHORT Port, ULONG Val)
{
    ASMV("outl %0, %w1" : : "a" (Val), "Nd" (Port));
}

#endif  /* !_MACHINE_PIO_H_ */
