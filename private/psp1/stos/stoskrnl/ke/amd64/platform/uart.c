/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: serial interface
 * Author:      Chloe M.
 */

#include <hal/serial.h>
#include <machine/pio.h>
#include <stdef.h>

/* Channel port numbers */
#define UART_COM1 0x3F8
#define UART_COM2 0x2F8
#define UART_COM3 0x3E8
#define UART_COM4 0x2E8
#define UART_COM5 0x5F8
#define UART_COM6 0x4F8
#define UART_COM7 0x5E8
#define UART_COM8 0x4E8

/* Register offsets */
#define UART_REG(OFFSET) (UART_COM1 + OFFSET)
#define UART_REG_FCR UART_REG(2) /* FIFO Control Register */
#define UART_REG_LCR UART_REG(3) /* Line Control Register */
#define UART_REG_MCR UART_REG(4) /* MODEM Control Register */
#define UART_REG_LSR UART_REG(5) /* Line Status Register */
#define UART_REG_MSR UART_REG(6) /* MODEM Status Register */
#define UART_REG_SR  UART_REG(7) /* Scratch Register */

/* Registers when LCR.DLAB=0 */
#define UART_REG_RBR UART_REG(0) /* Receiver Buffer Register */
#define UART_REG_THR UART_REG(0) /* Transmitter Holding Register */
#define UART_REG_IER UART_REG(1) /* Interrupt Enable Register */

/* Registers when LCR.DLAB=1 */
#define UART_REG_DLL UART_REG(0) /* Divisor Latch Low */
#define UART_REG_DLH UART_REG(1) /* Divisor Latch High */

#define UART_LCR_WLS0 BIT(0) /* Word Length Select Bit 0 */
#define UART_LCR_WLS1 BIT(1) /* Word Length Select Bit 1 */
#define UART_LCR_DLAB BIT(7) /* Divisor Latch Access Bit*/

#define UART_MCR_DTR  BIT(0) /* Data Terminal Ready*/
#define UART_MCR_LOOP BIT(4) /* Loop */

#define UART_LSR_THRE BIT(5) /* Transmitter Holding Register */

#define UART_DIVISOR(RATE) (115200 / RATE)

static inline BOOL
UartTxEmpty(VOID)
{
    return ISSET(UART_REG_LSR, UART_LSR_THRE) != 0;
}

VOID
HalSerialWrite(const CHAR *Data, USIZE Length)
{
    if (Data == NULL) {
        return;
    }

    while (!UartTxEmpty()) {
        ASMV("pause");
    }

    for (USIZE Index = 0; Index < Length; ++Index) {
        MdOutb(UART_REG_THR, Data[Index]);
    }
}

ST_STATUS
HalSerialInit(VOID)
{
    /* Disable interrupts */
    MdOutb(UART_REG_IER, 0x00);

    /* Set DLAB to set baud rate */
    MdOutb(UART_REG_LCR, UART_LCR_DLAB);

    /* Set speed to 57600 baud */
    MdOutb(UART_REG_DLL, UART_DIVISOR(57600));
    MdOutb(UART_REG_IER, 0x00);

    /* Set word size to 8 bits and clear DLAB */
    MdOutb(UART_REG_LCR, UART_LCR_WLS0 | UART_LCR_WLS1);

    /* Disable FIFOs for now... (TODO: Use them) */
    MdOutb(UART_REG_FCR, 0x00);

    /* Test chip in loopback mode */
    MdOutb(UART_REG_MCR, UART_MCR_LOOP);
    MdOutb(UART_REG_THR, 0xF0);
    if (MdInb(UART_REG_RBR != 0xF0))
        return -1;

    /*
     * Mark the data terminal ready and clear
     * loopback mode.
     */
    MdOutb(UART_REG_MCR, UART_MCR_DTR);
    return 0;
}
