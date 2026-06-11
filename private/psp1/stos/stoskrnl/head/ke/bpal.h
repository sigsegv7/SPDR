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
 * Represents the handle used to abstract away boot loader
 * specific protocols. It acts as its own protocol for the
 * sake of indirection.
 *
 * @StLoadBase: Slut technology kernel load base
 */
typedef struct {
    UPTR StLoadBase;
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
