/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Interrupt management interface
 * Author:      Chloe M.
 */

#include <hal/intr.h>
#include <hal/kpcr.h>
#include <machine/intr.h>
#include <machine/idt.h>
#include <ke/knot.h>
#include <stdef.h>

/*
 * List of registered interrupt handlers
 */
static INTR_HANDLER HandlerList[256];

UCHAR
HalRegisterIntr(INTR_HANDLER *Handler)
{
    INTR_HANDLER *HandlerEntry;
    UCHAR VectorStart;
    UCHAR Vector;

    if (Handler == NULL) {
        return 0;
    }

    /*
     * There are 16 interrupt vectors per priority, we need to scan
     * the list of handlers and see if any vector for the desired
     * priority is available.
     */
    VectorStart = MAX(Handler->Priority << IPL_SHIFT, 0x20);
    for (Vector = VectorStart; Vector < VectorStart + 16; ++Vector) {
        /* List of vectors we are to skip */
        switch (Vector) {
        case VECTOR_SYSCALL:
        case VECTOR_SCHED:
            continue;
        }

        HandlerEntry = &HandlerList[Vector];
        if (HandlerEntry->Present == 0) {
            *HandlerEntry = *Handler;
            HandlerEntry->Present = 1;

            MdIdtSetEntry(
                Vector,
                Handler->ServiceRoutine,
                IDT_INT_GATE,
                0
            );

            return Vector;
        }
    }

    /* Resources have been saturated */
    return 0;
}

UCHAR
HalRaiseIrql(UCHAR Irql)
{
    KPCR *Self;
    UCHAR OldIrql;

    if ((Self = HalKpcrSelf()) == NULL) {
        return IRQL_NONE;
    }

    if (Irql < Self->Irql) {
        KeKnot("IRQL_NOT_GREATER_THAN_OR_EQUAL\n");
    }

    OldIrql = Self->Irql;
    ASMV(
        "mov %0, %%rax\n"
        "mov %%rax, %%cr8"
        :
        : "r" ((UQUAD)Irql)
        : "rax", "memory"
    );

    Self->Irql = Irql;
    return OldIrql;
}

UCHAR
HalLowerIrql(UCHAR Irql)
{
    KPCR *Self;
    UCHAR OldIrql;

    if ((Self = HalKpcrSelf()) == NULL) {
        return IRQL_NONE;
    }

    if (Irql > Self->Irql) {
        KeKnot("IRQL_NOT_LESS_THAN_OR_EQUAL\n");
    }

    OldIrql = Self->Irql;
    ASMV(
        "mov %0, %%rax\n"
        "mov %%rax, %%cr8"
        :
        : "r" ((UQUAD)Irql)
        : "rax", "memory"
    );

    Self->Irql = Irql;
    return OldIrql;
}
