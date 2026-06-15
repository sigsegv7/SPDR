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
#include <machine/page.h>
#include <stapi/status.h>
#include <stdef.h>

/* Protection flags */
#define PAGE_READONLY           0x00
#define PAGE_READWRITE          0x01
#define PAGE_EXECUTE_RW         0x02
#define PAGE_EXECUTE_READONLY   0x03

typedef enum {
    PAGESIZE_4K
} MMU_PAGESIZE;

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

/*
 * Map a single page of memory
 *
 * @Vas:  Virtual address space to map within
 * @Vma:  Virtual memory address to map
 * @Pma:  Physical memory address to map
 * @Prot: Protection flags
 * @Ps:   Page size
 */
ST_STATUS HalMapSinglePage(MMU_VAS *Vas, UPTR Vma, UPTR Pma, UCHAR Prot, MMU_PAGESIZE Ps);

#endif  /* !_HAL_MMU_H_ */
