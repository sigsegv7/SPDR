/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: System object management
 * Author:      Chloe M.
 */

#include <ob/object.h>
#include <ex/trace.h>
#include <ke/knot.h>

#define DTRACE(Fmt, ...) \
    TRACE("[ OB ]: " Fmt, ##__VA_ARGS__)

static ST_OBJECT *RootDirectory;

VOID
ObManagerInit(void)
{
    ST_STATUS Status;

    Status = ObDirectoryNew("/", &RootDirectory);
    if (Status != STATUS_SUCCESS) {
        KeKnot("failed to initialize object manager");
    }

    DTRACE("root mounted at '/'\n");
}
