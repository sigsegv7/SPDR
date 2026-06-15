/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Machine specific knot logic
 * Author:      Chloe M.
 */

#ifndef _HAL_KNOT_H_
#define _HAL_KNOT_H_ 1

#include <machine/frame.h>
#include <stdef.h>

/*
 * Dump the trapframe during knot conditions
 */
VOID HalKnotDumpFrame(void);

#endif  /* !_HAL_KNOT_H_ */
