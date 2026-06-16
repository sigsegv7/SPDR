/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: System object management
 * Author:      Chloe M.
 */

#ifndef _OB_OBJECT_H_
#define _OB_OBJECT_H_ 1

#include <stapi/status.h>
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
 * @Last:       Last directory entry
 */
typedef struct {
    USIZE EntryCount;
    OB_DIRECTORY_ENTRY *First;
    OB_DIRECTORY_ENTRY *Last;
} OB_DIRECTORY;

/*
 * Create a new system object
 *
 * @Name:   Name of object
 * @Type:   Type of object
 * @Result: Object result is written here
 */
ST_STATUS ObObjectCreate(
    const CHAR *Name, OB_TYPE Type,
    VOID *Data, ST_OBJECT **Result
);

/*
 * Lock an object with a security descriptor
 *
 * @Object:     Object to lock
 * @SecType:    Security descriptor type [must match, added security]
 * @SecDesc:    Security descriptor to lock with
 */
ST_STATUS ObObjectLock(
    ST_OBJECT *Object, TOKEN_TYPE SecType,
    SECURITY_DESCRIPTOR *SecDesc
);

/*
 * Create a new directory object
 *
 * @Name: Name of directory object
 * @Result: Result is written here
 */
ST_STATUS ObDirectoryNew(const CHAR *Name, ST_OBJECT **Result);

/*
 * Append an object to an object directory
 *
 * @Directory: Directory object to append to
 * @Object:    Object to append
 */
ST_STATUS ObDirectoryAppend(ST_OBJECT *Directory, ST_OBJECT *Object);

/*
 * Look up a directory entry by name
 *
 * @Directory: Parent directory
 * @Name:      Name of object to lookup
 * @Result:    Result is written here
 */
ST_STATUS ObDirectoryLookup(ST_OBJECT *Directory, const CHAR *Name, ST_OBJECT **Result);

/*
 * Initialize the object manager
 */
VOID ObManagerInit(void);

#endif  /* !_OB_OBJECT_H_ */
