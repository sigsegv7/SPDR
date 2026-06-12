/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel knot handler
 * Author:      Chloe M.
 */

#include <drivers/bootvid/fbio.h>
#include <hal/prim.h>
#include <ex/trace.h>
#include <stdef.h>

/* Globals */
static CHAR KnotBuf[256];
static va_list Ap;
static BOOTCONS_ATTR KnotAttr = {
    .Background = 0x000080,
    .Foreground = 0xFFFFFF
};

static CHAR KnotMessage[] = {
    "SystemPaw DR has ran into a wittle issue and the kernel pilot kitty\n"
    "has suspended the CPU to prevent damage to your machine.\n\n"
    "Press and hold the power button until the screen blanks.\n"
};

NO_RETURN VOID
KiKnot(const CHAR *Fmt, ...)
{
    va_start(Ap, Fmt);
    FmtPrintf(KnotBuf, sizeof(KnotBuf), Fmt, Ap);
    BootVidInitCons(&KnotAttr);

    TRACE("---- Ah!~ fuck, I've been knotted~ @.@ ----\n");
    TRACE(KnotMessage);
    TRACE("knot: %s", KnotBuf);

    for (;;) {
        MdCpuSuspend();
    }
}
