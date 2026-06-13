/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Processor primitives
 * Author:      Chloe M.
 */

#ifndef _MACHINE_PRIM_H_
#define _MACHINE_PRIM_H_ 1

#include <stdef.h>

#define MdCpuSuspend()  ASMV("hlt")
#define MdCpuSpinWait() ASMV("pause")

/*
 * Atomic swap operation
 *
 * @Ptr: Location to swap with @Value
 * @Value: Value to swap to @Ptr
 */
ALWAYS_INLINE static inline QUAD
MdCpuAswap(QUAD *Ptr, QUAD Value)
{
    QUAD RetVal;

    if (Ptr == NULL) {
        return 0;
    }

    RetVal = *(volatile QUAD *)Ptr;
    ASMV(
        "xchg %0, %1\n"
        : "+m" (*Ptr), "+r" (Value)
        :
        : "memory"
    );

    return RetVal;
}

#endif  /* !_MACHINE_PRIM_H_ */
