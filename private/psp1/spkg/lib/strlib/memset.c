/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: RtlMemSet() implementation
 * Author:      Chloe M.
 */

#include <string.h>

#ifndef __x86_64__
#error "64-bit only"
#else
#define WORD_SHIFT 3
#endif  /* !__x86_64__ */

VOID *
RtlMemSet(VOID *Buffer, LONG SetValue, USIZE Length)
{
    USIZE WordCount;
    USIZE *WordBuffer;
    CHAR *ByteBuffer = (CHAR *)Buffer;
    USIZE Index;

    if (Buffer == NULL || Length == 0) {
        return NULL;
    }

    /* How many words can this fit? */
    WordCount = Length / sizeof(USIZE);
    WordBuffer = (USIZE *)Buffer;

    /* Fill as many words as we can */
    for (Index = 0; Index < WordCount; ++Index) {
        WordBuffer[Index] = SetValue;
    }

    /* Fill the rest */
    Index <<= WORD_SHIFT;
    for (; Index < Length; ++Index) {
        ByteBuffer[Index] = SetValue;
    }

    return Buffer;
}
