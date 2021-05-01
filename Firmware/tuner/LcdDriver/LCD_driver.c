/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   LCD_driver.c
 * Author   :   Mukta
 * Date     :   04/12/2021
 * Brief    :   graphic display functions
 * Reference:   https://github.com/adafruit/TFTLCD-Library
 *******************************************************************************/

#include <ti/grlib/grlib.h>
#include "LCD_driver.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LCD_240x320.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left

char my_font[TOTAL_CHAR][8] = MY_FONT;

uint8_t Lcd_Orientation;
uint16_t Lcd_ScreenWidth, Lcd_ScreenHeigth;

//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the ST7735 display controller on the panel,
//! preparing it to display data.
//!
//! \return None.
//
//*****************************************************************************
void LCD_Init(void)
{
    LCD_PortInit();
    LCD_SpiInit();

    // chip select
    GPIO_setOutputLowOnPin(LCD_CS_PORT, LCD_CS_PIN);

    GPIO_setOutputLowOnPin(LCD_RST_PORT, LCD_RST_PIN);
    LCD_delay(50);
    GPIO_setOutputHighOnPin(LCD_RST_PORT, LCD_RST_PIN);
    LCD_delay(120);

    LCD_writeCommand(ILI9341_SWRESET);
    LCD_delay(150);

    LCD_writeCommand(0xEF);
    LCD_writeData(0x03);
    LCD_writeData(0x00);
    LCD_delay(150);
    LCD_writeData(0x02);
    
    LCD_writeCommand(0xCF);
    LCD_writeData(0x00);
    LCD_writeData(0x41);
    LCD_delay(150);
    LCD_writeData(0x30);
    
    LCD_writeCommand(0xED);
    LCD_writeData(0x64);
    LCD_writeData(0x03);
    LCD_writeData(0x12);
    LCD_writeData(0x01);
    LCD_delay(150);
    
    LCD_writeCommand(0xE8);
    LCD_writeData(0x05);
    LCD_delay(150);
    LCD_writeData(0x00);
    LCD_writeData(0x78);
    
    LCD_writeCommand(0xCB);
    LCD_writeData(0x39);
    LCD_writeData(0x2C);
    LCD_writeData(0x00);
    LCD_writeData(0x34);
    LCD_writeData(0x02);
    
    LCD_writeCommand(0xF7);
    LCD_writeData(0x20);
    
    LCD_writeCommand(0xEA);
    LCD_writeData(0x00);
    LCD_writeData(0x00);
    
    // Power control VRH[5:0]
    LCD_writeCommand(ILI9341_PWCTR1);
    LCD_writeData(0x23);
    
    // Power control SAP[2:0];BT[3:0]
    LCD_writeCommand(ILI9341_PWCTR2);
    LCD_writeData(0x10);
    
    // VCM control
    LCD_writeCommand(ILI9341_VMCTR1);
    LCD_writeData(0x3e);
    LCD_writeData(0x28);

    // VCM control2
    LCD_writeCommand(ILI9341_VMCTR2);
    LCD_writeData(0x06);
    LCD_delay(150);
    
    // Memory Access Control
    LCD_writeCommand(ILI9341_MADCTL);
    LCD_writeData(0x48);
    
    // Vertical scroll zero
    LCD_writeCommand(ILI9341_VSCRSADD);
    LCD_writeData(0x00);

    LCD_writeCommand(ILI9341_PIXFMT);
    LCD_writeData(0x55);
    
    LCD_writeCommand(ILI9341_FRMCTR1);
    LCD_writeData(0x00);
    LCD_writeData(0x18);
    
    // Display Function Control
    LCD_writeCommand(ILI9341_DFUNCTR);
    LCD_writeData(0x08);
    LCD_writeData(0x02);
    LCD_delay(150);
    LCD_writeData(0x27);
    
    // 3Gamma Function Disable
    LCD_writeCommand(0xF2);
    LCD_writeData(0x00);
    
    // Gamma curve selected
    LCD_writeCommand(ILI9341_GAMMASET);
    LCD_writeData(0x01);
    
    // Gamma set
    LCD_writeCommand(ILI9341_GMCTRP1);
    LCD_writeData(0x0F);
    LCD_writeData(0x31);
    LCD_writeData(0x2B);
    LCD_writeData(0x0C);
    LCD_writeData(0x0E);
    LCD_writeData(0x08);
    LCD_writeData(0x4E);
    LCD_writeData(0x71);
    LCD_delay(150);
    LCD_writeData(0x37);
    LCD_writeData(0x07);
    LCD_writeData(0x10);
    LCD_writeData(0x03);
    LCD_writeData(0x0E);
    LCD_writeData(0x09);
    LCD_writeData(0x00);
    
    // Gamma set
    LCD_writeCommand(ILI9341_GMCTRN1);
    LCD_writeData(0x00);
    LCD_writeData(0x0E);
    LCD_writeData(0x14);
    LCD_writeData(0x03);
    LCD_writeData(0x11);
    LCD_writeData(0x07);
    LCD_writeData(0x31);
    LCD_writeData(0x41);
    LCD_delay(150);
    LCD_writeData(0x48);
    LCD_writeData(0x08);
    LCD_writeData(0x0F);
    LCD_writeData(0x0C);
    LCD_writeData(0x31);
    LCD_writeData(0x36);
    LCD_writeData(0x0F);
    
    // Exit Sleep
    LCD_writeCommand(ILI9341_SLPOUT);
    LCD_writeData(0x00);
    LCD_delay(150);
    
    // Display on
    LCD_writeCommand(ILI9341_DISPON);
    LCD_writeData(0x00);
    LCD_delay(150);
    
    // End of list

    LCD_SetOrientation(LCD_ORIENTATION_UP);

    LCD_SetDrawFrame(0, 0, 239, 319);

    LCD_writeCommand(ILI9341_RAMWR);
    int i, j;
    LCD_PixelDraw(0, 0, 0);
    //ILI9341_WHITE
    for (j = 0; j < 40; j++)
    {
        for (i = 0; i < 240; i++)
        {
            LCD_PixelDraw(i, j, 0);
        }
    }
    //ILI9341_YELLOW
    for (j = 40; j < 80; j++)
    {
        for (i = 0; i < 240; i++)
        {
            LCD_PixelDraw(i, j, 0x001F);
        }
    }
    //ILI9341_CYAN
    for (j = 80; j < 120; j++)
    {
        for (i = 0; i < 240; i++)
        {
            LCD_PixelDraw(i, j, 0xF800);
        }
    }
    //ILI9341_GREEN
    for (j = 120; j < 160; j++)
    {
        for (i = 0; i < 240; i++)
        {
            LCD_PixelDraw(i, j, 0xF81F);
        }
    }
    //ILI9341_MAGENTA
    for (j = 160; j < 200; j++)
    {
        for (i = 0; i < 240; i++)
        {
            LCD_PixelDraw(i, j, 0x07E0);
        }
    }
    //ILI9341_RED
    for (j = 200; j < 240; j++)
    {
        for (i = 0; i < 240; i++)
        {
            LCD_PixelDraw(i, j, 0x07FF);
        }
    }
    //ILI9341_BLUE
    for (j = 240; j < 280; j++)
    {
        for (i = 0; i < 240; i++)
        {
            LCD_PixelDraw(i, j, 0xFFE0);
        }
    }
    //ILI9341_BLACK
    for (j = 280; j < 320; j++)
    {
        for (i = 0; i < 240; i++)
        {
            LCD_PixelDraw(i, j, 0xFFFF);
        }
    }

    LCD_delay(10);
    LCD_writeCommand(ILI9341_DISPON);
}


//*****************************************************************************
//
//! draws the border on the page
//!
//! \return None.
//
//*****************************************************************************
void LCD_SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    LCD_writeCommand(ILI9341_CASET);
    LCD_writeData((uint8_t)(x0 >> 8));
    LCD_writeData((uint8_t)(x0));
    LCD_writeData((uint8_t)(x1 >> 8));
    LCD_writeData((uint8_t)(x1));

    LCD_writeCommand(ILI9341_PASET);
    LCD_writeData((uint8_t)(y0 >> 8));
    LCD_writeData((uint8_t)(y0));
    LCD_writeData((uint8_t)(y1 >> 8));
    LCD_writeData((uint8_t)(y1));
}


//*****************************************************************************
//
//! Sets the LCD Orientation.
//!
//! \param orientation is the desired orientation for the LCD. Valid values are:
//!           - \b LCD_ORIENTATION_UP,
//!           - \b LCD_ORIENTATION_LEFT,
//!           - \b LCD_ORIENTATION_DOWN,
//!           - \b LCD_ORIENTATION_RIGHT,
//!
//! This function sets the orientation of the LCD
//!
//! \return None.
//
//*****************************************************************************
void LCD_SetOrientation(uint8_t orientation)
{
    Lcd_Orientation = orientation;
    LCD_writeCommand(ILI9341_MADCTL);
    switch (Lcd_Orientation) {
        case LCD_ORIENTATION_UP:
            LCD_writeData(MADCTL_MX | MADCTL_BGR);
            Lcd_ScreenWidth = ILI9341_TFTWIDTH;
            Lcd_ScreenHeigth = ILI9341_TFTHEIGHT;
            break;
        case LCD_ORIENTATION_LEFT:
            LCD_writeData(MADCTL_MV | MADCTL_BGR);
            Lcd_ScreenWidth = ILI9341_TFTHEIGHT;
            Lcd_ScreenHeigth = ILI9341_TFTWIDTH;
            break;
        case LCD_ORIENTATION_DOWN:
            LCD_writeData(MADCTL_MY | MADCTL_BGR);
            Lcd_ScreenWidth = ILI9341_TFTWIDTH;
            Lcd_ScreenHeigth = ILI9341_TFTHEIGHT;
            break;
        case LCD_ORIENTATION_RIGHT:
            LCD_writeData(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
            Lcd_ScreenWidth = ILI9341_TFTHEIGHT;
            Lcd_ScreenHeigth = ILI9341_TFTWIDTH;
            break;
    }
}

//*****************************************************************************
//
//! Draws a pixel on the screen.
//!
//! \param pDisplay is a pointer to the driver-specific data for this
//! display driver.
//! \param lX is the X coordinate of the pixel.
//! \param lY is the Y coordinate of the pixel.
//! \param ulValue is the color of the pixel.
//!
//! This function sets the given pixel to a particular color.  The coordinates
//! of the pixel are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void LCD_PixelDraw(int16_t lX, int16_t lY, uint16_t ulValue)
{
    LCD_SetDrawFrame(lX,lY,lX,lY);

    // Write the pixel value.
    LCD_writeCommand(ILI9341_RAMWR);
    LCD_writeData(ulValue>>8);
    LCD_writeData(ulValue);
}
//*****************************************************************************
//
//! Draws a line on the screen.
//!
//! \param startp is the X/y coordinate of the start point of line.
//! \param endp is the X/Y coordinate of the end point of line.
//! \param constp is the X/Y coordinate of the line which remains constant.
//! \param ulValue is the color of the pixel.
//! \param dir is the direction of line - 1:Vertical, 0:Horizontal.
//!
//! This function sets the given pixels in a line to a particular color.
//! The coordinates of the pixel are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void LCD_LineDraw(int16_t startp, int16_t endp, int16_t constp, uint16_t ulValue, bool dir)
{
    if (dir)
    {   //vertical line
        for(int16_t i=startp; i<endp; i++)
        {
            LCD_PixelDraw(i, constp, ulValue);
        }
    }
    else
    {   //horizontal line
        for(int16_t i=startp; i<endp; i++)
        {
            LCD_PixelDraw(constp, i, ulValue);
        }
    }
}
//*****************************************************************************
//
//! Writes a character or string on the screen.
//!
//! \param lx is the X coordinate of the start point of Character, top left.
//! \param ly is the Y coordinate of the start point of Character, top left.
//! \param fontsize is size of character to be displayed
//!                     1- 5x8 pixels, 2- 10x16pixels ... so on
//! \param ulValue is the color of the pixel.
//! \param str is the string of character to be written.
//!
//! \return None.
//
//*****************************************************************************
void LCD_StringWrite(int16_t lx, int16_t ly, uint16_t ulValue, uint8_t fontsize, char *str)
{
    char size = strlen(str);
    char val =0;

    for (char k=0; k<size; k++)
    {
        if(str[k] >= '0' && str[k] <= '9')
            val = str[k] - '0';
        else if(str[k] >= 'A' && str[k] <= 'Z')
            val = str[k] - 'A' + 10;
        else if(str[k] == ':')
            val = SEMICOLON;
        else if(str[k] == '.')
            val = FULLSTOP;
        else if(str[k] == '"')
            val = DINVCOMMA;
        else if(str[k] == '#')
            val = POUND;
        else if(str[k] == '=')
            val = EQUALTO;
        else if(str[k] == '-')
            val = DASH;
        else if(str[k] == ' ')
            val = SPACE;

        for(int j=0; j<(8*fontsize); j++)
        {
            for (int i=0; i<(5*fontsize); i++)
            {
                if (my_font[val][j/fontsize] & (1<<(4-(i/fontsize))))
                    LCD_PixelDraw(ly-j, (lx+i), ulValue);
                else
                    LCD_PixelDraw((ly-j), (lx+i), 0);
            }
        }
        lx += (6*fontsize);
    }
}
//*****************************************************************************
//
//! Draws trace of given frequency in fixed bottom place of screen.
//!
//! \param ulValue is the color of the pixel.
//! \param freq is the frequency of which waveform needs to be generated.
//!
//! \return None.
//
//*****************************************************************************
void LCD_DrawTrace(uint16_t ulValue, int32_t freq)
{
    //Graph 1=10,10 2=10,70 3=309,70 4=309,10
    static int16_t val=0, place=10;

    //As accurate frequency range is between 128Hz to 2KHz
    int16_t period = (int16_t)(28000/freq);
    int16_t halfperiod = period>>1;

    LCD_LineDraw(9, 74, place, 0, 1);

    if(val < halfperiod)
        LCD_PixelDraw(70, place, ulValue);
    else if (val == halfperiod)
        LCD_LineDraw(10, 70, place, ulValue, 1);
    else if (val == period)
        LCD_LineDraw(10, 70, place, ulValue, 1);
    else
        LCD_PixelDraw(10, place, ulValue);

    val++;
    if (val > (int16_t)period)
        val=0;

    place++;
    if (place > 309)
        place=10;
}
//*****************************************************************************
//
//! Draws bar graph indicating octave strength
//!
//! \param freq is the frequency depending on which bar graph is generated.
//!
//! \return None.
//
//*****************************************************************************
void LCD_DrawGraph(int32_t freq)
{
    //Graph 1=280,100 2=280,200 3=300,200 4=300,100

    int16_t period = (int16_t)(freq-100);
    if(period < 0)
        period = 0;
    period /= 20;

    LCD_Rectangle(280, 100, 300, 205, 0);

    uint16_t color_table[11]={ILI9341_RED, ILI9341_ORANGE, ILI9341_ORANGEYELLOW,
                              ILI9341_YELLOW, ILI9341_GREENYELLOW, ILI9341_GREEN,
                              ILI9341_CYANGREEN, ILI9341_CYAN, ILI9341_CYANBLUE,
                              ILI9341_BLUE, ILI9341_NAVY
    };

    for (int16_t i=0; i<=period; i++)
        LCD_LineDraw(280, 300, 100+i, ~(color_table[i/10]), 0);
}
//*****************************************************************************
//
//! Set background color of the screen.
//!
//! \param ulValue is the color of the pixel.
//!
//! This function sets the background color of the whole screen.
//!
//! \return None.
//
//*****************************************************************************
void LCD_SetBackground(uint16_t ulValue)
{
    LCD_PixelDraw(0, 0, 0);
        for (int16_t j = 0; j < 320; j++)
        {
            for (int16_t i = 0; i < 240; i++)
            {
                LCD_PixelDraw(i, j, ulValue);
            }
        }
}
//*****************************************************************************
//
//! Updates rectangle area of screen with given color.
//!
//! \param ulValue is the color of the pixel.
//!
//! \return None.
//
//*****************************************************************************
void LCD_Rectangle(int16_t lx, int16_t ly, int16_t lx1, int16_t ly1, uint16_t ulValue)
{
    LCD_PixelDraw(ly, lx, ulValue);
        for (int16_t j = lx; j <= lx1; j++)
        {
            for (int16_t i = ly; i <= ly1; i++)
            {
                LCD_PixelDraw(i, j, ulValue);
            }
        }
}

