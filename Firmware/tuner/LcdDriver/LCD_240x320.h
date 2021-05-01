/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   LCD_240x320.h
 * Date     :   04/12/2021
 * Brief    :   display SPI communication API functions used for updating LCD
 * Reference:   Code taken from boostxl_edumkii_microphonefft_msp432p401r_MSP_EXP432P401R_nortos_ccs project in SDK
 *******************************************************************************/

#ifndef __HAL_MSP_EXP432P401R_CRYSTALFONTZLCD_H_
#define __HAL_MSP_EXP432P401R_CRYSTALFONTZLCD_H_


#include <stdint.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
//*****************************************************************************
//
// User Configuration for the LCD Driver
//
//*****************************************************************************

// System clock speed (in Hz)
#define LCD_SYSTEM_CLOCK_SPEED                 48000000
// SPI clock speed (in Hz)
#define LCD_SPI_CLOCK_SPEED                    16000000

// Ports from MSP432 connected to LCD
#define LCD_SCK_PORT          GPIO_PORT_P1
#define LCD_SCK_PIN_FUNCTION  GPIO_PRIMARY_MODULE_FUNCTION
#define LCD_MOSI_PORT         GPIO_PORT_P1
#define LCD_MOSI_PIN_FUNCTION GPIO_PRIMARY_MODULE_FUNCTION
#define LCD_RST_PORT          GPIO_PORT_P5
#define LCD_CS_PORT           GPIO_PORT_P5
#define LCD_DC_PORT           GPIO_PORT_P3

// Pins from MSP432 connected to LCD
#define LCD_SCK_PIN           GPIO_PIN5
#define LCD_MOSI_PIN          GPIO_PIN6
#define LCD_RST_PIN           GPIO_PIN7
#define LCD_CS_PIN            GPIO_PIN0
#define LCD_DC_PIN            GPIO_PIN7

// Definition of USCI base address to be used for SPI communication
#define LCD_EUSCI_BASE        EUSCI_B0_BASE

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************
extern void LCD_writeCommand(uint8_t command);
extern void LCD_writeData(uint8_t data);
extern void LCD_PortInit(void);
extern void LCD_SpiInit(void);

// Custom __delay_cycles() for non CCS Compiler
#if !defined( __TI_ARM__ )
#undef __delay_cycles
#define __delay_cycles(x)     SysCtlDelay(x)
void SysCtlDelay(uint32_t);
#endif

#define LCD_delay(x)      __delay_cycles(x * 48)

#endif /* HAL_MSP_EXP432P401R_CRYSTALFONTZ128X128_ST7735_H_ */
