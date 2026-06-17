/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: ACPI driver
 * Author:      Chloe M.
 */

#ifndef _ACPI_ACPI_H_
#define _ACPI_ACPI_H_ 1

#include <stdef.h>

/*
 * Initialize ACPI
 */
VOID AcpiInit(VOID);

/*
 * Query an ACPI structure
 *
 * @Signature: Signature to query for
 *
 * Returns the virtual structure base on success, otherwise
 * NULL on failure.
 */
VOID *AcpiQuery(const CHAR *Signature);

#endif  /* !_ACPI_ACPI_H_ */
