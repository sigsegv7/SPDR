/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel knot handler
 * Author:      Chloe M.
 */

#include <stdef.h>
#include <ex/trace.h>

/* Globals */
static CHAR KnotBuf[256];
static va_list Ap;

NO_RETURN VOID
KiKnot(const CHAR *Fmt, ...)
{
    va_start(Ap, Fmt);
    FmtPrintf(KnotBuf, sizeof(KnotBuf), Fmt, Ap);

    TRACE("\033[31;40m*******************************************\n");
    TRACE("ah!~ fuck, i've been knotted~ @.@\n");
    TRACE("knot: %s", KnotBuf);
    for (;;);
}
