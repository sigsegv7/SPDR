/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Virtual address descriptor management
 * Author:      Chloe M.
 */

#ifndef _MM_VAD_H_
#define _MM_VAD_H_ 1

#include <stapi/status.h>
#include <stdef.h>

/*
 * Virtual address descriptor
 *
 * @Free: If set, is free
 * @Next: Next VAD
 * @Prev: Previous VAD
 */
typedef struct _MM_VAD {
    struct _MM_VAD *Next;
    struct _MM_VAD *Prev;
} MM_VAD;

/*
 * Virtual address space descriptor list
 *
 * @First:      First VAD in list
 * @Last:       Last VAD in list
 * @VadCount:   Number of VADs in list
 */
typedef struct {
    MM_VAD *First;
    MM_VAD *Last;
    USIZE VadCount;
} MM_VAD_LIST;

/*
 * Initialize a list of virtual address space descriptor
 *
 * @VadList: VAD list to initialize
 */
ST_STATUS MmVadListInit(MM_VAD_LIST *VadList);

/*
 * Append a page as a VAD to a VAD list
 *
 * @List: VAD list to append to
 * @Page: Page to append as VAD
 */
ST_STATUS MmVadListAppend(MM_VAD_LIST *List, VOID *Page);

#endif  /* !_MM_VAD_H_ */
