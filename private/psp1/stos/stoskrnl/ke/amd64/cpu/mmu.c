/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: MMU management core
 * Author:      Chloe M.
 */

#include <hal/mmu.h>
#include <stdef.h>

VOID
HalReadVas(MMU_VAS *Result)
{
    if (Result == NULL) {
        return;
    }

    ASMV(
        "mov %%cr3, %0"
        : "=r" (Result->TopLevel)
        :
        : "memory"
    );
}

VOID
HalWriteVas(MMU_VAS *Vas)
{
    if (Vas == NULL) {
        return;
    }

    ASMV(
        "mov %0, %%cr3"
        :
        : "r" (Vas->TopLevel)
        : "memory"
    );
}
