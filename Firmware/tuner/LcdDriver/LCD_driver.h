/* --COPYRIGHT--,BSD
 * Copyright (c) 2015, Texas Instruments Incorporated
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
 * --/COPYRIGHT--*/
//*****************************************************************************
//
// Crystalfontz128x128.h - Prototypes for the display driver for the Crystalfontz
//                         128x128 display with ST7735 controller.
//
//*****************************************************************************

#ifndef __CRYSTALFONTZLCD_H__
#define __CRYSTALFONTZLCD_H__


#include <stdint.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>


#define LCD_ORIENTATION_UP    0
#define LCD_ORIENTATION_LEFT  1
#define LCD_ORIENTATION_DOWN  2
#define LCD_ORIENTATION_RIGHT 3

// LCD Screen Dimensions
#define ILI9341_TFTWIDTH 240  ///< ILI9341 max TFT width
#define ILI9341_TFTHEIGHT 320 ///< ILI9341 max TFT height

#define ILI9341_NOP 0x00     ///< No-op register
#define ILI9341_SWRESET 0x01 ///< Software reset register
#define ILI9341_RDDID 0x04   ///< Read display identification information
#define ILI9341_RDDST 0x09   ///< Read Display Status

#define ILI9341_SLPIN 0x10  ///< Enter Sleep Mode
#define ILI9341_SLPOUT 0x11 ///< Sleep Out
#define ILI9341_PTLON 0x12  ///< Partial Mode ON
#define ILI9341_NORON 0x13  ///< Normal Display Mode ON

#define ILI9341_RDMODE 0x0A     ///< Read Display Power Mode
#define ILI9341_RDMADCTL 0x0B   ///< Read Display MADCTL
#define ILI9341_RDPIXFMT 0x0C   ///< Read Display Pixel Format
#define ILI9341_RDIMGFMT 0x0D   ///< Read Display Image Format
#define ILI9341_RDSELFDIAG 0x0F ///< Read Display Self-Diagnostic Result

#define ILI9341_INVOFF 0x20   ///< Display Inversion OFF
#define ILI9341_INVON 0x21    ///< Display Inversion ON
#define ILI9341_GAMMASET 0x26 ///< Gamma Set
#define ILI9341_DISPOFF 0x28  ///< Display OFF
#define ILI9341_DISPON 0x29   ///< Display ON

#define ILI9341_CASET 0x2A ///< Column Address Set
#define ILI9341_PASET 0x2B ///< Page Address Set
#define ILI9341_RAMWR 0x2C ///< Memory Write
#define ILI9341_RAMRD 0x2E ///< Memory Read

#define ILI9341_PTLAR 0x30    ///< Partial Area
#define ILI9341_VSCRDEF 0x33  ///< Vertical Scrolling Definition
#define ILI9341_MADCTL 0x36   ///< Memory Access Control
#define ILI9341_VSCRSADD 0x37 ///< Vertical Scrolling Start Address
#define ILI9341_PIXFMT 0x3A   ///< COLMOD: Pixel Format Set

#define ILI9341_FRMCTR1                                                        \
  0xB1 ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_FRMCTR2 0xB2 ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRMCTR3                                                        \
  0xB3 ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVCTR 0xB4  ///< Display Inversion Control
#define ILI9341_DFUNCTR 0xB6 ///< Display Function Control

#define ILI9341_PWCTR1 0xC0 ///< Power Control 1
#define ILI9341_PWCTR2 0xC1 ///< Power Control 2
#define ILI9341_PWCTR3 0xC2 ///< Power Control 3
#define ILI9341_PWCTR4 0xC3 ///< Power Control 4
#define ILI9341_PWCTR5 0xC4 ///< Power Control 5
#define ILI9341_VMCTR1 0xC5 ///< VCOM Control 1
#define ILI9341_VMCTR2 0xC7 ///< VCOM Control 2

#define ILI9341_RDID1 0xDA ///< Read ID 1
#define ILI9341_RDID2 0xDB ///< Read ID 2
#define ILI9341_RDID3 0xDC ///< Read ID 3
#define ILI9341_RDID4 0xDD ///< Read ID 4

#define ILI9341_GMCTRP1 0xE0 ///< Positive Gamma Correction
#define ILI9341_GMCTRN1 0xE1 ///< Negative Gamma Correction
//#define ILI9341_PWCTR6     0xFC

// Color definitions
#define ILI9341_BLACK 0x0000       ///<   0,   0,   0
#define ILI9341_NAVY 0x001C        ///<   0,   0, 123
#define ILI9341_DARKGREEN 0x03E0   ///<   0, 125,   0
#define ILI9341_DARKCYAN 0x03EF    ///<   0, 125, 123
#define ILI9341_MAROON 0x7800      ///< 123,   0,   0
#define ILI9341_PURPLE 0x780F      ///< 123,   0, 123
#define ILI9341_OLIVE 0x7BE0       ///< 123, 125,   0
#define ILI9341_LIGHTGREY 0xC618   ///< 198, 195, 198
#define ILI9341_DARKGREY 0x7BEF    ///< 123, 125, 123
#define ILI9341_BLUE 0x001F        ///<   0,   0, 255
#define ILI9341_GREEN 0x07E0       ///<   0, 255,   0
#define ILI9341_CYANGREEN 0x07FA        ///<   0, 255, 255
#define ILI9341_CYANBLUE 0x071F    ///<   0, 125, 123
#define ILI9341_CYAN    0x07FF        ///<   0, 255, 255
#define ILI9341_RED     0xF800         ///< 255,   0,   0
#define ILI9341_MAGENTA 0xF81F     ///< 255,   0, 255
#define ILI9341_YELLOW 0xFFE0      ///< 255, 255,   0
#define ILI9341_WHITE 0xFFFF       ///< 255, 255, 255
#define ILI9341_ORANGEYELLOW 0xEE00      ///< 255, 165,   0
#define ILI9341_ORANGE 0x0FD20      ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xBF80 ///< 173, 255,  41
#define ILI9341_PINK 0xFC18        ///< 255, 130, 198

extern uint8_t Lcd_Orientation;
extern uint16_t Lcd_ScreenWidth, Lcd_ScreenHeigth;
extern uint8_t Lcd_PenSolid, Lcd_FontSolid, Lcd_FlagRead;
extern uint16_t Lcd_TouchTrim;

#define TOTAL_CHAR        43

#define SEMICOLON   36
#define FULLSTOP    37
#define DINVCOMMA   38
#define POUND       39
#define EQUALTO     40
#define DASH        41
#define SPACE       42

// 0,1,2,3,4,5,6,7,8,9, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, :,.,",#,=,-,' '
#define MY_FONT {   {0x0E, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0E, 0x00}, \
                    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00}, \
                    {0x04, 0x0A, 0x11, 0x02, 0x04, 0x08, 0x1F, 0x00}, \
                    {0x0E, 0x01, 0x01, 0x02, 0x01, 0x01, 0x0E, 0x00}, \
                    {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02, 0x00}, \
                    {0x1F, 0x10, 0x10, 0x1E, 0x01, 0x01, 0x1E, 0x00}, \
                    {0x01, 0x02, 0x04, 0x0C, 0x12, 0x09, 0x06, 0x00}, \
                    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x00}, \
                    {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00}, \
                    {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x11, 0x0E, 0x00}, \
                    {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00}, \
                    {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E, 0x00}, \
                    {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E, 0x00}, \
                    {0x1C, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1C, 0x00}, \
                    {0x1F, 0x10, 0x10, 0x1C, 0x10, 0x10, 0x1F, 0x00}, \
                    {0x1F, 0x10, 0x10, 0x1C, 0x10, 0x10, 0x10, 0x00}, \
                    {0x07, 0x08, 0x10, 0x13, 0x11, 0x09, 0x07, 0x00}, \
                    {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00}, \
                    {0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00}, \
                    {0x0E, 0x02, 0x02, 0x02, 0x02, 0x0A, 0x04, 0x00}, \
                    {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11, 0x00}, \
                    {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00}, \
                    {0x11, 0x11, 0x1B, 0x15, 0x11, 0x11, 0x11, 0x00}, \
                    {0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x00}, \
                    {0x04, 0x0A, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00}, \
                    {0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10, 0x00}, \
                    {0x04, 0x0A, 0x11, 0x11, 0x15, 0x0A, 0x05, 0x00}, \
                    {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11, 0x00}, \
                    {0x0E, 0x11, 0x08, 0x04, 0x02, 0x11, 0x0E, 0x00}, \
                    {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00}, \
                    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00}, \
                    {0x11, 0x11, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x00}, \
                    {0x11, 0x11, 0x11, 0x15, 0x1B, 0x11, 0x11, 0x00}, \
                    {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00}, \
                    {0x11, 0x11, 0x0A, 0x0A, 0x04, 0x04, 0x04, 0x00}, \
                    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F, 0x00}, \
                    {0x00, 0x06, 0x06, 0x00, 0x00, 0x06, 0x06, 0x00}, \
                    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00}, \
                    {0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00}, \
                    {0x05, 0x1F, 0x0A, 0x0A, 0x1F, 0x14, 0x00, 0x00}, \
                    {0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00, 0x00}, \
                    {0x00, 0x00, 0x00, 0x0E, 0x0E, 0x00, 0x00, 0x00}, \
                    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, \
};

extern void LCD_Init(void);

extern void LCD_SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

extern void LCD_SetOrientation(uint8_t orientation);

extern void LCD_PixelDraw(int16_t lX, int16_t lY, uint16_t ulValue);

void LCD_SetBackground(uint16_t ulValue);

void LCD_LineDraw(int16_t startp, int16_t endp, int16_t constp, uint16_t ulValue, bool dir);

void LCD_StringWrite(int16_t lx, int16_t ly, uint16_t ulValue, uint8_t fontsize, char *str);

void LCD_DrawTrace(uint16_t ulValue, int32_t freq);

void LCD_DrawGraph(int32_t freq);

void LCD_Rectangle(int16_t lx, int16_t ly, int16_t lx1, int16_t ly1, uint16_t ulValue);

#endif /* __CRYSTALFONTZLCD_H__ */
