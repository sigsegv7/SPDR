/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel processor control region
 * Author:      Chloe M.
 */

#ifndef _HAL_KPCR_H_
#define _HAL_KPCR_H_ 1

#include <stdef.h>

/*
 * Represents a kernel processor control region describing
 * machine independent details about a processor core.
 *
 * @CoreId:  Processor core ID
 */
typedef struct {
    UCHAR CoreId;
} KPCR;

/*
 * KPCR phase 1 initialization
 *
 * @Kpcr: KPCR of processor to initialize
 */
VOID HalKpcrP1Init(KPCR *Kpcr);

#endif  /* !_HAL_KPCR_H_ */
