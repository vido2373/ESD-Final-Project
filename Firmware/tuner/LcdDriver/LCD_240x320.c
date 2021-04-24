
//*****************************************************************************
//
//
//*****************************************************************************

#include "LCD_240x320.h"
#include <ti/grlib/grlib.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>

void LCD_PortInit(void)
{
    // LCD_SCK
    GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_SCK_PORT, LCD_SCK_PIN, GPIO_PRIMARY_MODULE_FUNCTION);
    // LCD_MOSI
    GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_MOSI_PORT, LCD_MOSI_PIN, GPIO_PRIMARY_MODULE_FUNCTION);
    // LCD_RST
    GPIO_setAsOutputPin(LCD_RST_PORT, LCD_RST_PIN);
    // LCD_RS
    GPIO_setAsOutputPin(LCD_DC_PORT, LCD_DC_PIN);
    // LCD_CS
    GPIO_setAsOutputPin(LCD_CS_PORT, LCD_CS_PIN);
}

void LCD_SpiInit(void)
{
    eUSCI_SPI_MasterConfig config =
        {
            EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
            LCD_SYSTEM_CLOCK_SPEED,
            LCD_SPI_CLOCK_SPEED,
            EUSCI_B_SPI_MSB_FIRST,
            EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
            EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
            EUSCI_B_SPI_3PIN
        };
    SPI_initMaster(LCD_EUSCI_BASE, &config);
    SPI_enableModule(LCD_EUSCI_BASE);

    GPIO_setOutputLowOnPin(LCD_CS_PORT, LCD_CS_PIN);

    GPIO_setOutputHighOnPin(LCD_DC_PORT, LCD_DC_PIN);
}


//*****************************************************************************
//
// Writes a command to the CFAF128128B-0145T.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void LCD_writeCommand(uint8_t command)
{
    // Set to command mode
    GPIO_setOutputLowOnPin(LCD_DC_PORT, LCD_DC_PIN);

    // USCI_B0 Busy? //
    while (UCB0STATW & UCBUSY);

    // Transmit data
    UCB0TXBUF = command;

    // USCI_B0 Busy? //
    while (UCB0STATW & UCBUSY);

    // Set back to data mode
    GPIO_setOutputHighOnPin(LCD_DC_PORT, LCD_DC_PIN);
}


//*****************************************************************************
//
// Writes a data to the CFAF128128B-0145T.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void LCD_writeData(uint8_t data)
{
    // USCI_B0 Busy? //
    while (UCB0STATW & UCBUSY);

    // Transmit data
    UCB0TXBUF = data;

    // USCI_B0 Busy? //
    while (UCB0STATW & UCBUSY);
}

//*****************************************************************************
//
//! Provides a small delay.
//!
//! \param ui32Count is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a delay by executing a simple
//! 3 instruction cycle loop a given number of times.  It is written in
//! assembly to keep the loop instruction count consistent across tool chains.
//!
//! It is important to note that this function does NOT provide an accurate
//! timing mechanism.  Although the delay loop is 3 instruction cycles long,
//! the execution time of the loop will vary dramatically depending upon the
//! application's interrupt environment (the loop will be interrupted unless
//! run with interrupts disabled and this is generally an unwise thing to do)
//! and also the current system clock rate and flash timings (wait states and
//! the operation of the prefetch buffer affect the timing).
//!
//! For best accuracy, a system timer should be used with code either polling
//! for a particular timer value being exceeded or processing the timer
//! interrupt to determine when a particular time period has elapsed.
//!
//! \return None.
//
//*****************************************************************************
#if defined( __ICCARM__ ) || defined(DOXYGEN)
void
SysCtlDelay(uint32_t ui32Count)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(codered) || defined( __GNUC__ ) || defined(sourcerygxx)
void __attribute__((naked))
SysCtlDelay(uint32_t ui32Count)
{
    __asm("    subs    r0, #1\n"
          "    bne     SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined( __CC_ARM )
__asm void
SysCtlDelay(uint32_t ui32Count)
{
    subs    r0, #1;
    bne     SysCtlDelay;
    bx      lr;
}
#endif
