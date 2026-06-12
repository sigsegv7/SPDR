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

#endif  /* !_MACHINE_PRIM_H_ */
