/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Virtual address space
 * Author:      Chloe M.
 */

#ifndef _MACHINE_VAS_H_
#define _MACHINE_VAS_H_ 1

#include <stdef.h>

/*
 * Represents a virtual address space descriptor
 *
 * @TopLevel: PML4 or PML5 depending on configuration
 */
typedef struct {
   UPTR TopLevel;
} MMU_VAS;

#endif  /* !_MACHINE_VAS_H_ */
