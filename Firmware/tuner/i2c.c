/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP432 CODE EXAMPLE DISCLAIMER
 *
 * MSP432 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see http://www.ti.com/tool/mspdriverlib for an API functional
 * library & https://dev.ti.com/pinmux/ for a GUI approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP432P401 Demo  - eUSCI_B0 I2C Master RX multiple bytes from MSP432 Slave
//
//  Description: This demo connects two MSP432's via the I2C bus. The master
//  reads 5 bytes from the slave. This is the MASTER CODE. The data from the slave
//  transmitter begins at 0 and increments with each transfer.
//  The USCI_B0 RX interrupt is used to know when new data has been received.
//
//    *****used with "msp432p401x_euscib0_i2c_11.c"****
//
//                                /|\  /|\
//               MSP432P401      10k  10k     MSP432P401
//                   slave         |    |        master
//             -----------------   |    |   -----------------
//            |     P1.6/UCB0SDA|<-|----|->|P1.6/UCB0SDA     |
//            |                 |  |       |                 |
//            |                 |  |       |                 |
//            |     P1.7/UCB0SCL|<-|------>|P1.7/UCB0SCL     |
//            |                 |          |             P1.0|--> LED
//
//   William Goh
//   Texas Instruments Inc.
//   June 2016 (updated) | June 2014 (created)
//   Built with CCSv6.1, IAR, Keil, GCC
//******************************************************************************
/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   i2c.c
 * Author   :   Mukta
 * Date     :   04/12/2021
 * Modifications    :   modified Interrupt handler as per requirement,
 *                      made it bidirectional communication
 *                      Also added few error handling interrupts
 *******************************************************************************/
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <stdint.h>
#include "i2c.h"

//For time and date total 7 register and 1 of register pointer
#define MAX_REG     8

// Pointer to RX data, and RX data buffer
volatile uint8_t RXData[MAX_REG] = {0};
volatile uint8_t RXDataPointer;

// TX data buffer and counter
volatile uint8_t TXData[MAX_REG]= {0};
volatile uint8_t TXByteCtr=255;
volatile uint8_t state=0;            //1=read time in process, 0=ready for next read time call

//used to change from write to read commands in case of writing start location and then reading from that
volatile uint8_t ChangeMode=0;       //1=MSP in RX mode, 0=MSP in TX mode

/*
 * Function     :   void init_i2c(void)
 * Brief        :   initializes I2C for RTC IC and sets SCL of 100KHz
 */
void init_i2c(void)
{
    // Configure GPIO
    P6->SEL0 |= BIT4 | BIT5;                // I2C pins

    // Initialize data variable
    RXDataPointer = 0;

    // Configure USCI_B0 for I2C mode
    EUSCI_B1->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Software reset enabled
    EUSCI_B1->CTLW0 = EUSCI_A_CTLW0_SWRST | // Remain eUSCI in reset mode
            EUSCI_B_CTLW0_MODE_3 |          // I2C mode
            EUSCI_B_CTLW0_MST |             // Master mode
            EUSCI_B_CTLW0_SYNC |            // Sync mode
            EUSCI_B_CTLW0_SSEL__SMCLK;      // SMCLK
    EUSCI_B1->CTLW1 |= EUSCI_B_CTLW1_ASTP_2;// Automatic stop generated
                                            // after EUSCI_B0->TBCNT is reached
    EUSCI_B1->BRW = 480;                     // baudrate = SMCLK / 30 = 100kHz
    EUSCI_B1->TBCNT = 0x0008;               // number of bytes to be received
    EUSCI_B1->I2CSA = 0x0068;               // Slave address
    EUSCI_B1->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;// Release eUSCI from reset

    EUSCI_B1->IE |= EUSCI_A_IE_RXIE |       // Enable receive interrupt
            EUSCI_B_IE_NACKIE |             // Enable NACK interrupt
            EUSCI_B_IE_BCNTIE;              // Enable byte counter interrupt


    // Enable eUSCIB0 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIB1_IRQn) & 31);

    ChangeMode=1;
}

/*
 * Function     :   void EUSCIB1_IRQHandler(void)
 * Brief        :   I2C interrupt service routine
 */
void EUSCIB1_IRQHandler(void)
{
    if (EUSCI_B1->IFG & EUSCI_B_IFG_NACKIFG)
    {
        EUSCI_B1->IFG &= ~ EUSCI_B_IFG_NACKIFG;

        // I2C start condition
        EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
    }
    if (EUSCI_B1->IFG & EUSCI_B_IFG_RXIFG0)
    {
        EUSCI_B1->IFG &= ~ EUSCI_B_IFG_RXIFG0;

        // Get RX data
        RXData[RXDataPointer++] = EUSCI_B1->RXBUF;

        if (RXDataPointer > sizeof(RXData))
        {
            //start from 0th location of buffer on overflow
            RXDataPointer = 0;
            //change state to read time
            state=0;
        }
    }
    if (EUSCI_B1->IFG & EUSCI_B_IFG_BCNTIFG)
    {
        EUSCI_B1->IFG &= ~ EUSCI_B_IFG_BCNTIFG;
        //start from 0th location of buffer on byte count overflow
        RXDataPointer = 0;
        //change state to read time
        state=0;
    }
    if (EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0)
    {
        EUSCI_B1->IFG &= ~EUSCI_B_IFG_TXIFG0;

        // Check TX byte counter
        if (TXByteCtr)
        {
            // Load TX buffer
            EUSCI_B1->TXBUF = (TXData[7-(TXByteCtr-1)] & 0x00FF);
            // Decrement TX byte counter
            TXByteCtr--;
        }
        else if(ChangeMode)
        {
            // I2C start condition
            EUSCI_B1->CTLW0 &= ~EUSCI_B_CTLW0_TR;

            // I2C start condition
            EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
        }
    }
    if (EUSCI_B1->IFG & EUSCI_B_IFG_STPIFG)
    {
        // Clear USCI_B0 TX int flag
        EUSCI_B1->IFG &= ~EUSCI_B_IFG_STPIFG;

        // Clear USCI_B0 TX int flag
        EUSCI_B1->IFG &= ~EUSCI_B_IFG_TXIFG;

        ChangeMode=1;
        // Wake up on exit from ISR
        //SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
    }
    if (EUSCI_B1->IFG & EUSCI_B_IFG_BIT9IFG)
    {
        // Clear USCI_B0 TX int flag
        EUSCI_B1->IFG &= ~EUSCI_B_IFG_BIT9IFG;
    }
}

/*
 * Function     :   void set_time()
 * Brief        :   can be used to set time in DS1337 as per requirement
 *                  used only once while setting initial real time in DS1337
 *                  then removed from main loop
 */
void set_time()
{
    //time settings
    TXByteCtr = MAX_REG;
    TXData[0]=0;        //Write pointer
    TXData[1]=0x50;     //seconds = 50
    TXData[2]=0x11;     //min = 11
    TXData[3]=0x15;     //hours = 3pm
    TXData[4]=0x05;     //day = friday
    TXData[5]=0x23;     //date = 23rd
    TXData[6]=0x04;     //month = april
    TXData[7]=0x21;     //year = 2021

    // I2C TX condition
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TR;

    EUSCI_B1->IE |= EUSCI_A_IE_TXIE;       // Enable TX interrupt

    // I2C start condition
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;
}

/*
 * Function     :   void read_time()
 * Brief        :   First sends device address and location pointer
 *                  then starts reading
 */
void read_time()
{
    //skip if reading is in process
    if(state)
        return;

    //transmit 1 byte of location pointer = 0x00
    TXByteCtr = 1;
    TXData[0]=0;
    TXData[1]=0;
    TXData[2]=0;
    TXData[3]=0;
    TXData[4]=0;
    TXData[5]=0;
    TXData[6]=0;
    TXData[7]=0;

    // I2C start condition
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TR;

    EUSCI_B1->IE |= EUSCI_A_IE_TXIE;       // Enable TX interrupt

    // I2C start condition
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

    //Start read operation
    state=1;
}

/*
 * Function     :   void set_int_rtc()
 * Brief        :   setting up internal RTC
 */
void set_int_rtc()
{
    while(state);

    RTC_C->CTL0 = RTC_C_KEY;

    RTC_C->YEAR = (0x20 << 8) | RXData[6];                   // Year = 0x2021
    RTC_C->DATE = (RXData[5] << RTC_C_DATE_MON_OFS) | // Month = 0x04 = April
            (RXData[4] | RTC_C_DATE_DAY_OFS);    // Day = 0x01 = 1st
    RTC_C->TIM1 = (RXData[3] << RTC_C_TIM1_DOW_OFS) | // Day of week = 0x04 = Thursday
            (RXData[2] << RTC_C_TIM1_HOUR_OFS);  // Hour = 0x10
    RTC_C->TIM0 = (RXData[1] << RTC_C_TIM0_MIN_OFS) | // Minute = 0x32
            (RXData[0] << RTC_C_TIM0_SEC_OFS);   // Seconds = 0x45

    // Lock the RTC registers
    RTC_C->CTL0 = RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK);
}
