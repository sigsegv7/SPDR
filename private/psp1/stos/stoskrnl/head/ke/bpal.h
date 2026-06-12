/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot Protocol Abstraction Layer
 * Author:      Chloe M.
 */

#ifndef _KE_BPAL_H_
#define _KE_BPAL_H_ 1

#include <stapi/status.h>
#include <stdef.h>

#ifndef BOOT_PROTOCOL
#define BOOT_PROTOCOL "limine"
#endif  /* !BOOT_PROTOCOL */

/*
 * Valid memory types
 */
typedef enum {
    MEMORY_USABLE,
    MEMORY_RESERVED,
    MEMORY_ACPI_RECLAIM,
    MEMORY_ACPI_NVS,
    MEMORY_BAD,
    MEMORY_BOOTLOADER,
    MEMORY_KERNEL,
    MEMORY_FRAMEBUFFER,
    MEMORY_ACPI_TABLES
} KE_MEM_TYPE;

/*
 * Represents a framebuffer
 */
typedef struct {
    VOID *Address;
    UQUAD Width;
    UQUAD Height;
    UQUAD Pitch;
    SHORT Bpp;
    UCHAR RedMaskSize;
    UCHAR RedMaskShift;
    UCHAR GreenMaskSize;
    UCHAR GreenMaskShift;
    UCHAR BlueMaskSize;
    UCHAR BlueMaskShift;
} KE_BPAL_FRAMEBUFFER;

/*
 * Memory map entry
 *
 * @Base:   Entry base
 * @Length: Entry length
 * @Type:   Entry type
 */
typedef struct {
    UQUAD Base;
    UQUAD Length;
    UQUAD Type;
} KE_MEMMAP_ENTRY;

/*
 * Bootloader module
 *
 * @Data: Data backed by module
 * @Length: Length of data in bytes
 */
typedef struct {
    VOID *Data;
    USIZE Length;
} KE_BPAL_MODULE;

/*
 * Represents the handle used to abstract away boot loader
 * specific protocols. It acts as its own protocol for the
 * sake of indirection.
 *
 * @CommandLine: Kernel command line
 * @StLoadBase: Slut technology kernel load base
 * @Framebuffer: Framebuffer descriptor
 * @ModuleLookup: Callback to lookup boot module
 * @MemEntryIdx:  Callback to obtain entry by index
 */
typedef struct {
    const CHAR *CommandLine;
    UPTR StLoadBase;
    KE_BPAL_FRAMEBUFFER Framebuffer;
    ST_STATUS(*ModuleLookup)(CHAR *Path, KE_BPAL_MODULE *Result);
    ST_STATUS(*MemEntryIdx)(USIZE Idx, KE_MEMMAP_ENTRY *Result);
} KE_BPAL_HANDLE;

/*
 * Initialize the boot protocol abstraction layer
 */
ST_STATUS KeBpalInit(VOID);

/*
 * Obtain the BPAL handle
 *
 * @Result: Result is written here
 */
ST_STATUS KeBpalGet(KE_BPAL_HANDLE *Result);

/*
 * Obtain a memory map entry by index
 *
 * @Idx: Index of entry to obtain
 * @Result: Result is written here
 */
ST_STATUS KeBpalMemEntry(USIZE Idx, KE_MEMMAP_ENTRY *Result);

/* Backend init routines */
ST_STATUS KeBpalLimineInit(KE_BPAL_HANDLE *Handle);

#endif  /* !_KE_BPAL_H_ */
