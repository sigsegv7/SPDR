/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: System object management
 * Author:      Chloe M.
 */

#include <ob/object.h>
#include <ex/pool.h>
#include <stdef.h>
#include <string.h>

#define OBJECT_POOL_TAG 'OB'

/*
 * Allocate a new directory entry
 *
 * @Object: Object to assign to directory entry
 */
static OB_DIRECTORY_ENTRY *
DirEntryAlloc(ST_OBJECT *Object)
{
    OB_DIRECTORY_ENTRY *DirEnt;

    DirEnt = ExAllocatePoolWithTag(
        NON_PAGED_POOL,
        sizeof(*DirEnt),
        OBJECT_POOL_TAG
    );

    if (DirEnt == NULL) {
        return NULL;
    }

    RtlMemSet(DirEnt, 0, sizeof(*DirEnt));
    DirEnt->Object = Object;
    return DirEnt;
}

/*
 * Copy a name to an object
 *
 * @Name:   Name of object to assign
 * @Object: Object to be assigned name
 */
static ST_STATUS
ObjectCopyName(const CHAR *Name, ST_OBJECT *Object)
{
    USIZE NameLen;

    if (Name == NULL || Object == NULL) {
        return STATUS_INVALID_PARAM;
    }

    NameLen = RtlStrLen(Name);
    if (NameLen >= OB_NAMESZ - 1) {
        return STATUS_NAME_TOO_LONG;
    }

    RtlMemCpy(Object->Name, Name, NameLen);
    Object->Name[NameLen] = '\0';
    return STATUS_SUCCESS;
}

ST_STATUS
ObObjectCreate(const CHAR *Name, OB_TYPE Type, VOID *Data, ST_OBJECT **Result)
{
    ST_OBJECT *Object;
    ST_STATUS Status;

    if (Name == NULL || Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    Object = ExAllocatePoolWithTag(
        NON_PAGED_POOL,
        sizeof(*Object),
        OBJECT_POOL_TAG
    );

    if (Object == NULL) {
        return STATUS_NO_MEMORY;
    }

    RtlMemSet(Object, 0, sizeof(*Object));
    Object->RefCnt = 1;
    Object->Type = Type;
    Object->Data = Data;

    /* TODO: Free on failure here */
    Status = ObjectCopyName(Name, Object);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    *Result = Object;
    return STATUS_SUCCESS;
}

ST_STATUS
ObObjectLock(ST_OBJECT *Object, TOKEN_TYPE SecType, SECURITY_DESCRIPTOR *SecDesc)
{
    if (Object == NULL || SecDesc == NULL)  {
        return STATUS_INVALID_PARAM;
    }

    if (SecDesc->Type != SecType) {
        return STATUS_INVALID_PARAM;
    }

    Object->SecToken = *SecDesc;
    return STATUS_SUCCESS;
}

ST_STATUS
ObDirectoryNew(const CHAR *Name, ST_OBJECT **Result)
{
    ST_STATUS Status;
    OB_DIRECTORY *Directory;

    if (Name == NULL || Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    Directory = ExAllocatePoolWithTag(
        NON_PAGED_POOL,
        sizeof(*Directory),
        OBJECT_POOL_TAG
    );

    if (Directory == NULL) {
        return STATUS_NO_MEMORY;
    }

    RtlMemSet(Directory, 0, sizeof(*Directory));
    Status = ObObjectCreate(Name, OB_TYPE_DIR, Directory, Result);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    return STATUS_SUCCESS;
}

ST_STATUS
ObDirectoryAppend(ST_OBJECT *Directory, ST_OBJECT *Object)
{
    OB_DIRECTORY *DirObject;
    OB_DIRECTORY_ENTRY *DirEnt, *LastEnt;

    if (Directory == NULL || Object == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (Directory->Type != OB_TYPE_DIR) {
        return STATUS_NOT_DIRECTORY;
    }

    DirObject = Directory->Data;
    if (DirObject == NULL) {
        return STATUS_IO_ERROR;
    }

    DirEnt = DirEntryAlloc(Object);
    if (DirEnt == NULL) {
        return STATUS_NO_MEMORY;
    }

    if (DirObject->First == NULL || DirObject->Last == NULL) {
        DirObject->First = DirEnt;
        DirObject->Last = DirEnt;
    } else {
        LastEnt = DirObject->Last;
        LastEnt->Next = DirEnt;
        DirObject->Last = DirEnt;
    }

    ++DirObject->EntryCount;
    return STATUS_SUCCESS;
}

ST_STATUS
ObDirectoryLookup(ST_OBJECT *Directory, const CHAR *Name, ST_OBJECT **Result)
{
    ST_OBJECT *Object;
    OB_DIRECTORY *DirObject;
    OB_DIRECTORY_ENTRY *DirEnt;
    USIZE NameLen;

    if (Directory == NULL || Name == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (Directory->Type != OB_TYPE_DIR) {
        return STATUS_NOT_DIRECTORY;
    }

    DirObject = Directory->Data;
    if (DirObject == NULL) {
        return STATUS_IO_ERROR;
    }

    DirEnt = DirObject->First;
    NameLen = RtlStrLen(Name);

    while (DirEnt != NULL) {
        Object = DirEnt->Object;
        if (Object == NULL) {
            return STATUS_IO_ERROR;
        }

        if (RtlMemCmp(Object->Name, (CHAR *)Name, NameLen) == 0) {
            *Result = Object;
            return STATUS_SUCCESS;
        }

        DirEnt = DirEnt->Next;
    }

    return STATUS_NOT_FOUND;
}
