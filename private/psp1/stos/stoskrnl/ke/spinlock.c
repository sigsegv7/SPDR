/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Spinlock logic
 * Author:      Chloe M.
 */

#include <ke/spinlock.h>
#include <hal/prim.h>
#include <hal/intr.h>
#include <stdef.h>

VOID
KeSpinLockAcq(KE_SPINLOCK *Lock, BOOL IrqlMut)
{
    UCHAR OldIrql;

    if (Lock == NULL) {
        return;
    }

    if (IrqlMut) {
        OldIrql = HalRaiseIrql(IRQL_BIO);
    }

    /* Acquire the lock */
    while (HalCpuAswap(&Lock->Lock, 1)) {
        HalCpuSpinWait();
    }

    if (IrqlMut) {
        HalLowerIrql(OldIrql);
    }
}

VOID
KeSpinLockRel(KE_SPINLOCK *Lock)
{
    if (Lock == NULL) {
        return;
    }

    HalCpuAswap(&Lock->Lock, 0);
}
