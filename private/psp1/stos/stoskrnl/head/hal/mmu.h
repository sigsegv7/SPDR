/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: MMU HAL interface
 * Author:      Chloe M.
 */

#ifndef _HAL_MMU_H_
#define _HAL_MMU_H_ 1

#include <machine/vas.h>
#include <stdef.h>

/*
 * Read the current virtual address space
 *
 * @Result: Result is written here
 */
VOID HalReadVas(MMU_VAS *Result);

/*
 * Write a new virtual address space
 *
 * @Vas: Virtual address space to write
 */
VOID HalWriteVas(MMU_VAS *Vas);

#endif  /* !_HAL_MMU_H_ */
