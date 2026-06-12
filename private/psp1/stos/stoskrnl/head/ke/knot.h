/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel knot handler
 * Author:      Chloe M.
 */

#ifndef _KE_KNOT_H_
#define _KE_KNOT_H_ 1

/*
 * Signal to the machine operator that something went
 * terribly wrong.
 */
VOID KeKnot(const CHAR *Fmt, ...);

#endif  /* !_KE_KNOT_H_ */
