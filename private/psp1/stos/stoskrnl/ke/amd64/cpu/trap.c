/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Trap handling
 * Author:      Chloe M.
 */

#include <machine/trap.h>
#include <ke/knot.h>
#include <stdef.h>

/* Used to convert trap codes to strings */
static const char *TrapTab[] = {
    [TRAP_DIVERR] = "divide error",
    [TRAP_DBG]    = "debug exception",
    [TRAP_NMI]    = "non-maskable interrupt",
    [TRAP_BP]     = "breakpoint",
    [TRAP_OF]     = "overflow",
    [TRAP_BR]     = "bound range exceeded",
    [TRAP_UD]     = "undefined opcode",
    [TRAP_NM]     = "no math coprocessor",
    [TRAP_DF]     = "double fault",
    [TRAP_CPR]    = "reserved exception",
    [TRAP_TS]     = "invalid TSS",
    [TRAP_NP]     = "segment not present",
    [TRAP_SS]     = "stack segment fault",
    [TRAP_GP]     = "general protection fault",
    [TRAP_PF]     = "page fault"
};


VOID
MdTrapDispatch(TRAP_FRAME *Frame)
{
    if (Frame == NULL) {
        return;
    }

    if (Frame->Vector >= NELEM(TrapTab)) {
        KeKnot("Fatal unknown vector %x\n", Frame->Vector);
    }

    KeKnot("Fatal %s\n", TrapTab[Frame->Vector]);
}
