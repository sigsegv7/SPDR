/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: HAL serial interface
 * Author:      Chloe M.
 */

#ifndef _HAL_SERIAL_H_
#define _HAL_SERIAL_H_ 1

#include <stapi/status.h>

/*
 * Initialize the serial driver
 */
ST_STATUS HalSerialInit(VOID);

/*
 * Transmit data over serial
 *
 * @Data:   Data to transmit
 * @Length: Length of data to transmit
 */
VOID HalSerialWrite(const CHAR *Data, USIZE Length);

#endif  /* !_HAL_SERIAL_H_ */
