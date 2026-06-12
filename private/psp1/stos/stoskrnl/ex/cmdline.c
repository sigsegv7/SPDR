/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Command line parser
 * Author:      Chloe M.
 */

#include <drivers/bootvid/fbio.h>
#include <ex/cmdline.h>
#include <ke/bpal.h>
#include <string.h>

#define KEY_BOOTCONS "bootcons"
#define VALUE_TRUE "true"
#define VALUE_FALSE "false"

/*
 * Enable or disable the boot console
 *
 * @CmdValue: Command value
 */
static VOID
CmdSetBootCons(CHAR *CmdValue)
{
    if (CmdValue == NULL) {
        return;
    }

    if (RtlMemCmp(CmdValue, VALUE_TRUE, sizeof(VALUE_TRUE)) == 0) {
        BootVidInitCons(NULL);
    }
}

/*
 * TODO: Handle ';' seperator
 */
VOID
CmdLineParse(const CHAR *CmdLine)
{
    CHAR KeyBuf[128];
    CHAR ValBuf[128];
    USHORT KeyBufLen = 0;
    USHORT ValBufLen = 0;
    BOOL ParseVal = false;
    const CHAR *Head;

    if (CmdLine == NULL) {
        return;
    }

    Head = CmdLine;
    while (*Head != '\0') {
        if (*Head == '=') {
            ParseVal = true;
            ++Head;
            continue;
        }

        if (!ParseVal && KeyBufLen < sizeof(KeyBuf) - 1) {
            KeyBuf[KeyBufLen++] = *Head++;
            continue;
        }

        if (ParseVal && ValBufLen < sizeof(ValBuf) - 1) {
            ValBuf[ValBufLen++] = *Head++;
            continue;
        }

        /* Handle overflows */
        if (!ParseVal && KeyBufLen >= sizeof(KeyBuf) - 1)
            return;
        if (ParseVal && ValBufLen >= sizeof(ValBuf) - 1)
            return;

        ++Head;
    }

    KeyBuf[KeyBufLen] = '\0';
    ValBuf[ValBufLen] = '\0';

    switch (KeyBuf[0]) {
    case 'b':
        if (RtlMemCmp(KeyBuf, KEY_BOOTCONS, sizeof(KEY_BOOTCONS)) == 0) {
            CmdSetBootCons(ValBuf);
        }

        break;
    }
}

VOID
ExCmdLineInit(VOID)
{
    KE_BPAL_HANDLE BpalHandle;
    ST_STATUS Status;

    Status = KeBpalGet(&BpalHandle);
    if (Status != STATUS_SUCCESS) {
        return;
    }

    CmdLineParse(BpalHandle.CommandLine);
}
