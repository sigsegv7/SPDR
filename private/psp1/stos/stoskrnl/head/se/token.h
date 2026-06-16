/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Security descriptor / token
 * Author:      Chloe M.
 */

#ifndef _SE_TOKEN_H_
#define _SE_TOKEN_H_ 1

#include <stdef.h>

/* SECURITY_DESCRIPTOR.AccessLimit values */
#define SE_ACCESS_NO_LIMIT  0
#define SE_ACCESS_DUB_LIMIT 2

/*
 * Represents the various possible types of a security
 * token / descriptor.
 *
 * @TOKEN_UNLOCKED:  Resource is unlocked, no associated token type
 * @TOKEN_MAC:       Mandatory access control
 */
typedef enum {
    TOKEN_UNLOCKED,
    TOKEN_MAC
} TOKEN_TYPE;

/*
 * A security descriptor (aka token) describes the access rights of a
 * specific resource.
 *
 * @Type:           Security descriptor / token type
 * @AccessLimit:    Maximum accesses before resource is locked
 * @AccessCount:    Number of accesses made to resource
 * @Data:           Security model specific data
 */
typedef struct {
    TOKEN_TYPE Type;
    USHORT AccessLimit;
    USHORT AccessCount;
    VOID *Data;
} SECURITY_DESCRIPTOR;

#endif  /* !_SE_TOKEN_H_ */
