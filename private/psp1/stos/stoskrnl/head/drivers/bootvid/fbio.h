/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot video driver
 * Author:      Chloe M.
 */

#ifndef _BOOTVID_FBIO_H_
#define _BOOTVID_FBIO_H_ 1

#include <stapi/status.h>
#include <stdef.h>

/*
 * Initialize the boot video driver
 */
ST_STATUS BootInit(void);

#endif  /* !_BOOTVID_FBIO_H_ */
