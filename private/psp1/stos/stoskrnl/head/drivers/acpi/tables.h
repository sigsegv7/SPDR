/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: ACPI definitions
 * Author:      Chloe M.
 */

#ifndef _ACPI_TABLES_H_
#define _ACPI_TABLES_H_ 1

#include <stdef.h>

/* MADT APIC header types */
#define APIC_TYPE_LOCAL_APIC            0
#define APIC_TYPE_IO_APIC               1
#define APIC_TYPE_INTERRUPT_OVERRIDE    2

#define OEMID_SIZE 6

typedef struct PACKED {
    CHAR Signature[4];
    ULONG Length;
    UCHAR Revision;
    UCHAR Checksum;
    CHAR Oemid[OEMID_SIZE];
    CHAR OemTableId[8];
    ULONG OemRevision;
    ULONG CreatorId;
    ULONG CreatorRevision;
} ACPI_HEADER;

typedef struct PACKED {
    UQUAD Signature;
    UCHAR Checksum;
    CHAR Oemid[OEMID_SIZE];
    UCHAR Revision;
    ULONG RsdtAddr;

    /* Reserved if revision < 2 */
    ULONG Length;
    UQUAD XsdtAddr;
    UCHAR ExtChecksum;
    UCHAR Reserved[3];
} ACPI_RSDP;

/*
 * XSDT or RSDT depending on the revision within the
 * header
 */
typedef struct PACKED {
    ACPI_HEADER Header;
    ULONG Tables[];
} ACPI_ROOT_SDT;

typedef struct PACKED {
    ACPI_HEADER Header;
    ULONG LapicAddr;
    ULONG Flags;
} ACPI_MADT;

typedef struct PACKED {
    UCHAR Type;
    UCHAR Length;
} ACPI_APIC_HEADER;

typedef struct PACKED {
    ACPI_APIC_HEADER Header;
    UCHAR ProcessorId;
    UCHAR ApicId;
    ULONG Flags;
} ACPI_LOCAL_APIC;

typedef struct PACKED {
    UCHAR AddressSpaceId;
    UCHAR RegisterBitWidth;
    UCHAR RegisterBitOffset;
    UCHAR Reserved;
    ULONG AddressLow;
    ULONG AddressHigh;
} ACPI_GAS;

#define ACPI_GAS_ADDRESS(GAS_P) \
    (((UQUAD)(GAS_P)->AddressHigh << 32) | ((GAS_P)->AddressLow))

/*
 * ACPI Address Space ID definitions for GAS
 *
 * See section 5.2.3.2 of the ACPI software programming
 * manual.
 *
 * XXX: 0x0B->0x7E is reserved as well as 0x80->0xBF
 *      and 0xC0->0xFF is OEM defined. Values other than
 *      the ones specified below are either garbage or
 *      OEM specific values.
 */
#define ACPI_GAS_SYSMEM   0x00      /* System memory space */
#define ACPI_GAS_SYSIO    0x01      /* System I/O space */
#define ACPI_GAS_PCICONF  0x02      /* PCI configuration space */
#define ACPI_GAS_EC       0x03      /* Embedded controller */
#define ACPI_GAS_SMBUS    0x04      /* System management bus */
#define ACPI_GAS_CMOS     0x05      /* System CMOS */
#define ACPI_GAS_PCIBAR   0x06      /* PCI BAR target */
#define ACPI_GAS_IPMI     0x07      /* IPMI (sensor monitoring) */
#define ACPI_GAS_GPIO     0x08      /* General Purpose I/O */
#define ACPI_GAS_GSBUS    0x09      /* GenericSerialBus */
#define ACPI_GAS_PLATCOM  0x0A      /* Platform Communications Channel */

/*
 * ACPI address size definitions for GAS
 *
 * See section 5.2.3.2 of the ACPI software programming
 * manual.
 */
#define ACPI_GAS_UNDEF  0   /* Undefined (legacy reasons) */
#define ACPI_GAS_BYTE   1   /* Byte access */
#define ACPI_GAS_WORD   2   /* Word access */
#define ACPI_GAS_DWORD  3   /* Dword access */
#define ACPI_GAS_QWORD  4   /* Qword access */

typedef struct PACKED {
    ACPI_HEADER Header;
    UCHAR HardwareRevId;
    UCHAR ComparatorCount   : 5;
    UCHAR CounterSize       : 1;
    UCHAR Reserved          : 1;
    UCHAR LegacyReplacement : 1;
    USHORT PciVendorId;
    ACPI_GAS Gas;
    UCHAR HpetNumber;
    USHORT MinimumTick;
    UCHAR PageProtection;
} ACPI_HPET;

#endif  /* _ACPI_TABLES_H_ */
