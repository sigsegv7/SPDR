/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Machine specific knot logic
 * Author:      Chloe M.
 */

#include <hal/knot.h>
#include <machine/frame.h>
#include <ex/trace.h>
#include <stdef.h>

extern TRAP_FRAME gCoreSnapshot;

VOID
HalKnotDumpFrame(void)
{
    TRACE(
        "RAX : %p - RBX : %p\n",
        gCoreSnapshot.Rax,
        gCoreSnapshot.Rbx
    );

    TRACE(
        "RCX : %p - RDX : %p\n",
        gCoreSnapshot.Rcx,
        gCoreSnapshot.Rdx
    );

    TRACE(
        "RDX : %p - RSI : %p\n",
        gCoreSnapshot.Rdx,
        gCoreSnapshot.Rsi
    );

    TRACE(
        "RDI : %p - RBP : %p\n",
        gCoreSnapshot.Rdi,
        gCoreSnapshot.Rbp
    );

    TRACE(
        "R8  : %p - R9  : %p\n",
        gCoreSnapshot.R8,
        gCoreSnapshot.R9
    );

    TRACE(
        "R10 : %p - R11 : %p\n",
        gCoreSnapshot.R10,
        gCoreSnapshot.R11
    );

    TRACE(
        "R12 : %p - R13 : %p\n",
        gCoreSnapshot.R12,
        gCoreSnapshot.R13
    );

    TRACE(
        "R14 : %p - R15 : %p\n",
        gCoreSnapshot.R14,
        gCoreSnapshot.R15
    );
}
