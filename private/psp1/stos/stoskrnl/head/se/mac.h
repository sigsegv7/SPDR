/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Mandatory access control
 * Author:      Chloe M.
 */

#ifndef _SE_MAC_H_
#define _SE_MAC_H_ 1

#include <stdef.h>

/* MAC_DESCRIPTOR.PidClip values */
#define MAC_PID_CLIP_NONE  -1

/*
 * Valid Mandatory Access Control levels
 *
 * @MAC_LEVEL_GLOBAL:       Global to everyone [unless clipped, then global per-thread]
 * @MAC_LEVEL_LIMITED:      Limited access only
 * @MAC_LEVEL_RESTRICTED:   Restricted access only
 * @MAC_LEVEL_SECRET:       Secret; highest level
 */
typedef enum {
    MAC_LEVEL_GLOBAL,
    MAC_LEVEL_LIMITED,
    MAC_LEVEL_RESTRICTED,
    MAC_LEVEL_SECRET
} MAC_LEVEL;

/*
 * Mandatory Access Control descriptor
 *
 * @PidClip:        PID resource is clipped to (no other PID can access)
 * @AccessLevel:    Levels above or equal can access
 */
typedef struct {
    LONG PidClip;
    MAC_LEVEL AccessLevel;
} MAC_DESCRIPTOR;

#endif  /* !_SE_MAC_H_ */
