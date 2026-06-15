/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Page management
 * Author:      Chloe M.
 */

#ifndef _MM_PAGE_H_
#define _MM_PAGE_H_ 1

#include <stdef.h>

/*
 * Request a fixed number of contigious pages
 *
 * @Count: Number of pages to request
 *
 * Returns the page aligned base
 */
VOID *MmRequestPages(USIZE Count);

#endif  /* !_MM_PAGE_H_ */
