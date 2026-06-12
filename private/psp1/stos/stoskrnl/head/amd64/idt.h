/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Interrupt descriptor table
 * Author:      Chloe M.
 */

#ifndef _MACHINE_IDT_H_
#define _MACHINE_IDT_H_

#ifndef __ASSEMBLER__
#include <stdef.h>
#endif  /* !__ASSEMBLER__ */

#define IDT_INT_GATE    0x8E
#define IDT_TRAP_GATE   0x8F
#define IDT_USER_GATE   0xEE

#ifndef __ASSEMBLER__

/*
 * Interrupt descriptor table gate
 *
 * @OffsetLow:  Low 16-bits of ISR base
 * @SegmentSel: Code segment selector
 * @Ist:        Interrupt stack table index
 * @Zero:       Unused, keep zero
 * @Type:       Gate type
 * @Zero1:      Unused, keep zero
 * @Dpl:        Descriptor privilege level
 * @Present:    Must be set to be valid
 * @OffsetMid:  Middle 16-bits of ISR base
 * @OffsetHigh: Upper 32-bits of ISR base
 * @Reserved:   Reserved, keep zero
 */
typedef struct {
    USHORT OffsetLow;
    USHORT SegmentSel;
    UCHAR Ist : 3;
    UCHAR Zero : 5;
    UCHAR Type : 4;
    UCHAR Zero1 : 1;
    UCHAR Dpl : 2;
    UCHAR Present : 1;
    USHORT OffsetMid;
    ULONG OffsetHigh;
    ULONG Reserved;
} IDT_GATE;

/*
 * Interrupt descriptor table register
 *
 * @Limit: Maximum size of IDT minus one
 * @Base:  Base address of IDT
 */
typedef struct PACKED {
    USHORT Limit;
    UPTR Base;
} IDTR;

#endif  /* !__ASSEMBLER__ */
#endif  /* !_MACHINE_IDT_H_ */
