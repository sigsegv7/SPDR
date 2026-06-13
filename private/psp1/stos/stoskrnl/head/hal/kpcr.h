/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel processor control region
 * Author:      Chloe M.
 */

#ifndef _HAL_KPCR_H_
#define _HAL_KPCR_H_ 1

#include <machine/mcb.h>
#include <stdef.h>

/*
 * Represents a kernel processor control region describing
 * machine independent details about a processor core.
 *
 * @CoreId:     Processor core ID
 * @CoreData:   Machine core block
 */
typedef struct {
    UCHAR CoreId;
    MCB CoreData;
} KPCR;

/*
 * KPCR phase 1 initialization
 *
 * @Kpcr: KPCR of processor to initialize
 */
VOID HalKpcrP1Init(KPCR *Kpcr);

/*
 * KPCR phase 2 initialization
 *
 * @Kpcr: KPCR of processor to initialize
 */
VOID HalKpcrP2Init(KPCR *Kpcr);

/*
 * Obtain a reference to the current processor context
 */
KPCR *HalKpcrSelf(VOID);

#endif  /* !_HAL_KPCR_H_ */
