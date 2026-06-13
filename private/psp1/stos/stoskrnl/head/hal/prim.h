/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Processor primitives
 * Author:      Chloe M.
 */

#ifndef _HAL_PRIM_H_
#define _HAL_PRIM_H_ 1

#include <machine/prim.h>

#define HalCpuSuspend    MdCpuSuspend
#define HalCpuSpinWait   MdCpuSpinWait
#define HalCpuAswap      MdCpuAswap

#endif  /* !_HAL_PRIM_H_ */
