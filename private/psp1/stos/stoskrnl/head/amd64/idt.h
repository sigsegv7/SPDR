/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Interrupt descriptor table
 * Author:      Chloe M.
 */

#ifndef _MACHINE_IDT_H_
#define _MACHINE_IDT_H_ 1

#define IDT_INT_GATE    0x8E
#define IDT_TRAP_GATE   0x8F
#define IDT_USER_GATE   0xEE

#ifndef __ASSEMBLER__
/*
 * Set an IDT entry
 *
 * @Vector:  Interrupt vector to set
 * @IsrBase: ISR base to set
 * @Type:    Gate type
 * @Ist:     Interrupt stack table index
 */
VOID MdIdtSetEntry(UCHAR Vector, UPTR IsrBase, UCHAR Type, UCHAR Ist);

/*
 * Load the IDT
 */
VOID MdIdtLoad(VOID);

#endif  /* !__ASSEMBLER__ */
#endif  /* !_MACHINE_IDT_H_ */
