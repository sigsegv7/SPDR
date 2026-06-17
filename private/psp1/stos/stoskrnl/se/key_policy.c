/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Security key policy
 * Author:      Chloe M.
 */

#include <se/token.h>
#include <stdef.h>

ST_STATUS
SeSetKeyPolicy(SECURITY_KEY *Key, TOKEN_TYPE Type)
{
    if (Key == NULL) {
        return STATUS_INVALID_PARAM;
    }

    /* Ensure the policy type is valid */
    switch (Type) {
    case TOKEN_MAC:
        break;
    default:
        return STATUS_INVALID_PARAM;
    }

    Key->Type = Type;
    Key->Rights = 0;
    return STATUS_SUCCESS;
}
