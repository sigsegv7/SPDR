/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Machine core block
 * Author:      Chloe M.
 */

#ifndef _MACHINE_MCB_H_
#define _MACHINE_MCB_H_ 1

#include <stdef.h>

/*
 * The machine core block contains machine specific
 * processor information.
 *
 * @Model:      Processor model ID
 * @Family:     Processor family ID
 * @LapicBase:  Local APIC MMIO base
 */
typedef struct {
    UCHAR Model;
    USHORT Family : 12;
    VOID *LapicBase;
} MCB;

#endif  /* !_MACHINE_MCB_H_ */
