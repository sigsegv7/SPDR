/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Page frame manager
 * Author:      Chloe M.
 */

#ifndef _MM_PFRAME_H_
#define _MM_PFRAME_H_ 1

#include <stdef.h>

/*
 * Initialize the page frame manager
 */
VOID MmPFrameInit(VOID);

/*
 * Request a single page
 *
 * Returns the physical memory base on success
 */
UPTR MmRequestPage(VOID);

#endif  /* !_MM_PFRAME_H_ */
