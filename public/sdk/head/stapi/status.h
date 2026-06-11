/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Status code definitions
 * Author:      Chloe M.
 */

#ifndef _STAPI_STATUS_H_
#define _STAPI_STATUS_H_ 1

#include <stdef.h>

/*
 * All routines returning a status code must have their
 * return type as this.
 */
typedef ULONG ST_STATUS;

/* Valid status codes */
#define STATUS_SUCCESS       0       /* Success! :3 */
#define STATUS_FAILURE       1       /* Failure :(  */
#define STATUS_NOT_FOUND     2       /* Resource not found */
#define STATUS_NO_MEMORY     3       /* Out of memory */
#define STATUS_INVALID_PARAM 4       /* Invalid parameter */
#define STATUS_IO_ERROR      5       /* I/O error */
#define STATUS_NO_DEV        6       /* No such device */
#define STATUS_NAME_TOO_LONG 7       /* Name is too long */
#define STATUS_NOT_DIRECTORY 8       /* File is not a directory */
#define STATUS_TIMED_OUT     9       /* Operation timed out */
#define STATUS_NOT_EXEC      10      /* Not executable */

#endif  /* !_STAPI_STATUS_H_ */
