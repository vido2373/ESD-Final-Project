//******************************************************************************
//  MSP432P401 Demo - RTC in real time clock mode
//
//  Description: This program demonstrates the RTC mode by triggering the event
//  interrupt RTC_C_CTL0_TEVIFG event, which triggers every minute change.
//  P1.0 toggles every minute to indicate this interrupt. After configuring
//  the RTC, device goes into LPM3 and waits for the RTC interrupts.
//  Notice that RTC starting second is set to be 45, so after starting the program
//  the first RTC interrupt should trigger after ~15 seconds. Consequent interrupts
//  should occur every minute.
//  This code requires an external LFXT1 crystal for RTC accuracy.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 3MHz
//
//                MSP432P401x
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//            |            P1.0 |--> Toggles every minute
//            |                 |
//
//
//   Kathryn Adamsky
//   Texas Instruments Inc.
//   Oct 2016 (updated) | November 2013 (created)
//   Built with CCSv6.1, IAR, Keil, GCC
//******************************************************************************
/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   rtc.c
 * Author   :   Mukta
 * Date     :   04/12/2021
 * Reference:   msp432p401x_rtc_01/02
 * Modifications    :   modified as per requirement, removed interrupts
 *******************************************************************************/

/* Includes */
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "LcdDriver/LCD_driver.h"

/* Macro definitions */
#define DATE_X_POS      51
#define DATE_Y_POS      224
#define HR_X_POS        254
#define HR_Y_POS        224
#define MIN_X_POS       (HR_X_POS+18)
#define MIN_Y_POS       (HR_Y_POS)
#define SEC_X_POS       (MIN_X_POS+18)
#define SEC_Y_POS       (MIN_Y_POS)

/*
 * Function     :   void init_rtc()
 * Brief        :   initializes internal RTC
 */
void init_rtc()
{

    CS->KEY = CS_KEY_VAL ;                  // Unlock CS module for register access

       CS->CTL2 |= CS_CTL2_LFXT_EN;            // LFXT on

       // Loop until XT1, XT2 & DCO fault flag is cleared
       do
       {
          // Clear XT2,XT1,DCO fault flags
          CS->CLRIFG |= CS_CLRIFG_CLR_DCOR_OPNIFG | CS_CLRIFG_CLR_HFXTIFG |
                  CS_CLRIFG_CLR_LFXTIFG | CS_CLRIFG_CLR_FCNTLFIFG;
          SYSCTL->NMI_CTLSTAT &= ~ SYSCTL_NMI_CTLSTAT_CS_SRC;
       } while ((SYSCTL->NMI_CTLSTAT | SYSCTL_NMI_CTLSTAT_CS_FLG)
               && (CS->IFG & CS_IFG_LFXTIFG)); // Test oscillator fault flag

       // Select ACLK as LFXTCLK
       CS->CTL1 &= ~(CS_CTL1_SELB);
       CS->KEY = 0;                               // Lock CS module from unintended accesses

       // Configure RTC

    // Unlock RTC key protected registers
    // RTC enable, BCD mode, RTC hold
    // enable RTC read ready interrupt
    // enable RTC time event interrupt
    // set time event interrupt to trigger when minute changes
    RTC_C->CTL0 = RTC_C_KEY;
    RTC_C->CTL13 = RTC_C_CTL13_HOLD |
            RTC_C_CTL13_MODE |
            RTC_C_CTL13_BCD;

    RTC_C->YEAR = 0x2021;                   // Year = 0x2021
    RTC_C->DATE = (0x4 << RTC_C_DATE_MON_OFS) | // Month = 0x04 = April
            (0x01 | RTC_C_DATE_DAY_OFS);    // Day = 0x01 = 1st
    RTC_C->TIM1 = (0x04 << RTC_C_TIM1_DOW_OFS) | // Day of week = 0x04 = Thursday
            (0x10 << RTC_C_TIM1_HOUR_OFS);  // Hour = 0x10
    RTC_C->TIM0 = (0x32 << RTC_C_TIM0_MIN_OFS) | // Minute = 0x32
            (0x45 << RTC_C_TIM0_SEC_OFS);   // Seconds = 0x45

    // Start RTC calendar mode
    RTC_C->CTL13 = RTC_C->CTL13 & ~(RTC_C_CTL13_HOLD);

    // Lock the RTC registers
    RTC_C->CTL0 = RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK);

}

/*
 * Function     :   void display_date_string(char *str)
 * Brief        :   to display date read from internal RTC on LCD
 */
void display_date_string(char *str)
{
    static uint16_t prevdate =0;

    if (prevdate == RTC_C->DATE)
        return;

    prevdate = RTC_C->DATE;

    str[0] = ((RTC_C->DATE & 0xF000)>>12) + '0';    //Month MSD
    str[1] = ((RTC_C->DATE & 0x0F00)>>8) + '0';    //Month LSD

    str[2] = '-';    //dash in between

    str[3] = ((RTC_C->DATE & 0x00F0)>>4) + '0';    //Date MSD
    str[4] = ((RTC_C->DATE & 0x000F)) + '0';    //Date LSD

    str[5] = '-';    //dash in between

    str[6] = ((RTC_C->YEAR & 0xF000)>>12) + '0';    //Year MSD
    str[7] = ((RTC_C->YEAR & 0x0F00)>>8) + '0';    //Century LSD
    str[8] = ((RTC_C->YEAR & 0x00F0)>>4) + '0';    //Decade
    str[9] = ((RTC_C->YEAR & 0x000F)) + '0';    //Year LSD

    str[10] = '\0';    //end of string

    LCD_StringWrite(DATE_X_POS, DATE_Y_POS, ~(ILI9341_NAVY), 1, str);

}

/*
 * Function     :   void display_time_string(char *strhr, char *strmin, char *strsec)
 * Brief        :   to display time read from internal RTC on LCD
 */
void display_time_string(char *strhr, char *strmin, char *strsec)
{
    static uint8_t prevsec = 0, prevmin = 0, prevhr = 0;

    if (prevsec == (RTC_C->TIM0 & 0x00FF))
        return;

    prevsec = (uint8_t)(RTC_C->TIM0 & 0x00FF);

    strsec[0] = ((RTC_C->TIM0 & 0x00F0)>>4) + '0';    //Sec MSD
    strsec[1] = ((RTC_C->TIM0 & 0x000F)) + '0';    //Sec LSD

    strsec[2] = '\0';    //end of string

    LCD_StringWrite(SEC_X_POS, SEC_Y_POS, ~(ILI9341_NAVY), 1, strsec);


    if (prevmin == ((RTC_C->TIM0 & 0xFF00)>>8))
        return;
    prevmin = (uint8_t)((RTC_C->TIM0 & 0xFF00)>>8);

    strmin[0] = ((RTC_C->TIM0 & 0xF000)>>12) + '0';    //Min MSD
    strmin[1] = ((RTC_C->TIM0 & 0x0F00)>>8) + '0';    //Min LSD

    strmin[2] = ':';    //dash in between

    strmin[3] = '\0';    //end of string

    LCD_StringWrite(MIN_X_POS, MIN_Y_POS, ~(ILI9341_NAVY), 1, strmin);


    if (prevhr == (RTC_C->TIM1 & 0x00FF))
        return;
    prevhr = (uint8_t)(RTC_C->TIM1 & 0x00FF);

    strhr[0] = ((RTC_C->TIM1 & 0x00F0)>>4) + '0';    //Hour MSD
    strhr[1] = ((RTC_C->TIM1 & 0x000F)) + '0';    //Hour LSD

    strhr[2] = ':';    //dash in between

    strhr[3] = '\0';    //end of string

    LCD_StringWrite(HR_X_POS, HR_Y_POS, ~(ILI9341_NAVY), 1, strhr);

}

/*
 * Function     :   void get_timestamp(uint8_t *str)
 * Brief        :   to get time and date for logging purpose
 */
void get_timestamp(uint8_t *str)
{
    str[0] = ((RTC_C->DATE & 0xF000)>>12) + '0';    //Month MSD
    str[1] = ((RTC_C->DATE & 0x0F00)>>8) + '0';    //Month LSD

    str[2] = '-';    //dash in between

    str[3] = ((RTC_C->DATE & 0x00F0)>>4) + '0';    //Date MSD
    str[4] = ((RTC_C->DATE & 0x000F)) + '0';    //Date LSD

    str[5] = '-';    //dash in between

    str[6] = ((RTC_C->YEAR & 0xF000)>>12) + '0';    //Year MSD
    str[7] = ((RTC_C->YEAR & 0x0F00)>>8) + '0';    //Century LSD
    str[8] = ((RTC_C->YEAR & 0x00F0)>>4) + '0';    //Decade
    str[9] = ((RTC_C->YEAR & 0x000F)) + '0';    //Year LSD

    str[10] = ' ';    //space in between

    str[11] = ((RTC_C->TIM1 & 0x00F0)>>4) + '0';    //Hour MSD
    str[12] = ((RTC_C->TIM1 & 0x000F)) + '0';    //Hour LSD

    str[13] = ':';    //dash in between

    str[14] = ((RTC_C->TIM0 & 0xF000)>>12) + '0';    //Min MSD
    str[15] = ((RTC_C->TIM0 & 0x0F00)>>8) + '0';    //Min LSD

    str[16] = ':';    //dash in between

    str[17] = ((RTC_C->TIM0 & 0x00F0)>>4) + '0';    //Sec MSD
    str[18] = ((RTC_C->TIM0 & 0x000F)) + '0';    //Sec LSD

    str[19] = ' ';    //space in between

    str[20] = '\0';   //end of string
}
