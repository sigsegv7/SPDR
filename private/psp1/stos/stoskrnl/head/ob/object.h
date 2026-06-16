/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: System object management
 * Author:      Chloe M.
 */

#ifndef _OB_OBJECT_H_
#define _OB_OBJECT_H_ 1

#include <se/token.h>
#include <stdef.h>

/* Max object name size in bytes (inclusive of '\0') */
#define OB_NAMESZ 32

/*
 * Valid object types
 *
 * @OB_TYPE_NONE: This object has no associated type
 * @OB_TYPE_DIR:  This object is a directory
 */
typedef enum {
    OB_TYPE_NONE,
    OB_TYPE_DIR
} OB_TYPE;

/*
 * System object descriptor
 *
 * @Type:       Object type
 * @Name:       Name of object
 * @RefCnt:     Object reference count
 * @Data:       Object backing data
 * @SecToken:   Security token
 */
typedef struct {
   OB_TYPE Type;
   CHAR Name[OB_NAMESZ];
   ULONG RefCnt;
   VOID *Data;
   SECURITY_DESCRIPTOR SecToken;
} ST_OBJECT;

/*
 * Represents an object directory object
 *
 * @Object: Object backed by this entry
 * @Next:   Next directory entry
 */
typedef struct _OB_DIRECTORY_ENTRY {
    ST_OBJECT *Object;
    struct _OB_DIRECTORY_ENTRY *Next;
} OB_DIRECTORY_ENTRY;

/*
 * Represents an object directory
 *
 * @EntryCount: Number of entries in this
 * @First:      First directory entry
 */
typedef struct {
    USIZE EntryCount;
    OB_DIRECTORY_ENTRY *First;
} OB_DIRECTORY;

#endif  /* !_OB_OBJECT_H_ */
