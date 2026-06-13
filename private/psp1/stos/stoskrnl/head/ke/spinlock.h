/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Spinlock logic
 * Author:      Chloe M.
 */

#ifndef _KE_SPINLOCK_H_
#define _KE_SPINLOCK_H_ 1

#include <stdef.h>

/*
 * Represents a spinlock
 *
 * @Lock: Actual private lock data
 */
typedef struct {
    QUAD Lock;
} KE_SPINLOCK;

/*
 * Acquire a spinlock
 *
 * @Lock:       Lock to acquire
 * @IrqlMut:    If true, mutate IRQL
 */
VOID KeSpinLockAcq(KE_SPINLOCK *Lock, BOOL IrqlMut);

/*
 * Release a spinlock
 *
 * @Lock: Lock to release
 */
VOID KeSpinLockRel(KE_SPINLOCK *Lock);

#endif  /* !_KE_SPINLOCK_H_ */
