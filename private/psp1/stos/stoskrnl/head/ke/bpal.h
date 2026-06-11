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
 * Represents the handle used to abstract away boot loader
 * specific protocols. It acts as its own protocol for the
 * sake of indirection.
 *
 * @CommandLine: Kernel command line
 * @StLoadBase: Slut technology kernel load base
 * @Framebuffer: Framebuffer descriptor
 */
typedef struct {
    const CHAR *CommandLine;
    UPTR StLoadBase;
    KE_BPAL_FRAMEBUFFER Framebuffer;
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

/* Backend init routines */
ST_STATUS KeBpalLimineInit(KE_BPAL_HANDLE *Handle);

#endif  /* !_KE_BPAL_H_ */
