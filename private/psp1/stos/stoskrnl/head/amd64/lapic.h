/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Local APIC driver
 * Author:      Chloe M.
 */

#ifndef _MACHINE_LAPIC_H_
#define _MACHINE_LAPIC_H_ 1

#include <hal/kpcr.h>
#include <stdef.h>

/*
 * Initialize the Local APIC unit
 *
 * @Kpcr: KPCR of current processor
 */
VOID MdLapicInit(KPCR *Kpcr);

#endif  /* !_MACHINE_LAPIC_H_ */
