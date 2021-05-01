/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   main.c
 * Author   :   Mukta & Vishnu
 * Date     :   04/12/2021
 * Brief    :   main function and display functions used inside main
 *******************************************************************************/

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <arm_math.h>
#include <arm_const_structs.h>
#include <math.h>

/* Standard Includes */
#include <stdio.h>
#include <float.h>

/* Project Includes */
#include "LcdDriver/LCD_driver.h"
#include "rtc.h"
#include "i2c.h"
#include "clock_and_timer.h"
#include "switch.h"
#include "audio_processing.h"
#include "tuning.h"
#include "tx_queue.h"
#include "uart_driver.h"

/* Macro definitions */
#define TONE_X_POS      178
#define TONE_Y_POS      144
#define SHARP_X_POS     (TONE_X_POS+50)
#define SHARP_Y_POS     TONE_Y_POS
#define OCTV_X_POS      SHARP_X_POS
#define OCTV_Y_POS      (TONE_Y_POS-32)
#define FREQ_X_POS      90
#define FREQ_Y_POS      144
#define ERR_X_POS       90
#define ERR_Y_POS       112
#define MODE_X_POS       172
#define MODE_Y_POS       176

/*Global Variables*/
char date_ascii[]="04-21-2021";
char hr_ascii[]="05:";
char min_ascii[]="05:";
char sec_ascii[]="05";

//Logging variables
uint8_t notes_log[8][3];
uint8_t notes_time_log[8][21];
uint8_t notes_log_index = 0;

//For displaying notes
typedef enum {
    C1      = 32,
    C_SHARP = 34,
    D1      = 36,
    D_SHARP = 38,
    E1      = 41,
    F1      = 43,
    F_SHARP = 46,
    G1      = 49,
    G_SHARP = 51,
    A1      = 55,
    A_SHARP = 58,
    B1      = 61,
    NO_NOTE = 0
} out_note_t;

/* Function Prototypes */
void display_parameters(int32_t freq, out_note_t note, uint32_t octv, float err);
void start_LCD(void);
void uart_command_processing();
void init_peripherals(void);

/*
 * Function     :   int main(void)
 * Brief        :   main function loop
 *                  get tone (ADC) -> display updated parameters -> check UART command -> repeat
 */
int main(void)
{
    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    /* Initialize all peripherals */
    init_peripherals();

    int32_t frequency;
    uint32_t octave;
    float error;
    note_t out_note;

    while(1)
    {
        get_frequency_from_samples(&frequency); //does fft to get frequency

        get_tuning_data(frequency, &out_note, &octave, &error); //gets note, tune of note, and octave from frequency

        //As frequency is accurate up till 128Hz so make note and octave zero below that
        if (frequency < 128) {
            out_note = 0;
            octave = 0;
        }

        //Update display with changed parameters only
        display_date_string(date_ascii);
        display_time_string(hr_ascii, min_ascii, sec_ascii);
        display_parameters(frequency, (out_note_t)out_note, octave, error);

        //Update bar graph and trace as per octave and frequency
        if (out_note > 0) {
            /* Draw frequency bin graph */
            for (int i=0; i<300; i++) {
                LCD_DrawTrace(ILI9341_INV_RED, frequency);
            }
            LCD_DrawGraph(frequency);
        }

        //Check for UART commands and reply on terminal respectively
        uart_command_processing();
    }
}

/*
 * Function     :   void init_peripherals(void)
 * Brief        :   initialization of all peripherals used
 */
void init_peripherals(void)
{
    /* Set the core voltage level to VCORE1 */
        MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set 2 flash wait states for Flash bank 0 and 1*/
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* start clock at 48MHz */
    CLK_Init();

    /* Internal RTC initialization */
    init_rtc();

    /* I2C driver for External RTC initialization */
    init_i2c();

    // Enable global interrupt
    __enable_irq();

    // Time and Date settings
    __delay_cycles(100);
    read_time();            //read from external RTC IC
    __delay_cycles(10000);
    set_int_rtc();          //set internal RTC time and date as per external RTC

    /* Initializes display */
    LCD_Init();
    start_LCD();

    //push-button init
    init_switch();
    // initialize UART
    uart_init();

    //Print start message on terminal
    while (tx_length()) {
        if (get_uart_transmit_ready()) {
            uint8_t tx_byte;
            tx_dequeue(&tx_byte, 1);
            uart_transmit(tx_byte);
        }
    }
    tx_enqueue("Press 'l' to print log: \r\n", 26);
    tx_enqueue("Press 'i' to print info: \r\n", 27);
    while (tx_length()) {
        if (get_uart_transmit_ready()) {
            uint8_t tx_byte;
            tx_dequeue(&tx_byte, 1);
            uart_transmit(tx_byte);
        }
    }

    //Audio scanning initialization
    NVIC->ISER[1] |= 1 << ((PORT4_IRQn) & 31);
    init_hanning_window();
    init_audio_peripherals();
}

/*
 * Function     :   void uart_command_processing()
 * Brief        :   UART command processing function
 */
void uart_command_processing()
{
    //Logging
    if (get_uart_received()) {
        clear_uart_received();
        uint8_t get_log = get_uart_byte();
        if (get_log == 'l') {
            int j = (notes_log_index) & 0x7;
            tx_enqueue("Last 8 notes played (least to most recent): \r\n", 46);
            while (1) {
                tx_enqueue(notes_time_log[j], strlen((char *)notes_time_log[j]));
                tx_enqueue(notes_log[j], strlen((char *)notes_log[j]));
                tx_enqueue("\r\n", 2);
                while (tx_length()) {
                    if (get_uart_transmit_ready()) {
                        uint8_t tx_byte;
                        tx_dequeue(&tx_byte, 1);
                        uart_transmit(tx_byte);
                    }
                }
                j = (j + 1) & 0x07;
                if (j == notes_log_index) {
                    break;
                }
            }

            tx_enqueue("Press 'l' to print log: \r\n", 26);
            tx_enqueue("Press 'i' to print info: \r\n", 27);
            while (tx_length()) {
                if (get_uart_transmit_ready()) {
                    uint8_t tx_byte;
                    tx_dequeue(&tx_byte, 1);
                    uart_transmit(tx_byte);
                }
            }
        }
        if (get_log == 'i') {
            tx_enqueue("Device: Embedded Tuner\r\n", 24);
            tx_enqueue("Function: Detects and displays musical notes\r\n", 46);
            while (tx_length()) {
                if (get_uart_transmit_ready()) {
                    uint8_t tx_byte;
                    tx_dequeue(&tx_byte, 1);
                    uart_transmit(tx_byte);
                }
            }
            tx_enqueue("Modes: Pitch(gives note) and Tune(gives error in note)\r\n", 56);
            tx_enqueue("Press Button to toggle mode\r\n", 29);
            while (tx_length()) {
                if (get_uart_transmit_ready()) {
                    uint8_t tx_byte;
                    tx_dequeue(&tx_byte, 1);
                    uart_transmit(tx_byte);
                }
            }
            tx_enqueue("Press 'l' to print log: \r\n", 26);
            tx_enqueue("Press 'i' to print info: \r\n", 27);
            while (tx_length()) {
                if (get_uart_transmit_ready()) {
                    uint8_t tx_byte;
                    tx_dequeue(&tx_byte, 1);
                    uart_transmit(tx_byte);
                }
            }
        }
    }
}

/*
 * Function     :   void start_LCD(void)
 * Brief        :   initialization of LCD to Embedded tuner display page
 * Page Look    :    --------------------------------------
 *                   |   Date:               Time:        |
 *                   |       Embedded Tuner               |
 *                   |       Mode: Tuner             bar  |
 *                   |   Freq:        Tone Sharp     gr-  |
 *                   |   Err :        Tone Octv      aph  |
 *                   |                                    |
 *                   |   Frequency square waveform        |
 *                   |                                    |
 *                   --------------------------------------
 */
void start_LCD(void)
{
    LCD_SetBackground(0x00);

    LCD_LineDraw(5, 234, 5, ~(ILI9341_BLACK), 1);
    LCD_LineDraw(5, 234, 314, ~(ILI9341_BLACK), 1);
    LCD_LineDraw(5, 314, 5, ~(ILI9341_BLACK), 0);
    LCD_LineDraw(5, 314, 234, ~(ILI9341_BLACK), 0);

    LCD_StringWrite(15, 224, ~(ILI9341_NAVY), 1, "DATE:");
    display_date_string(date_ascii);
    LCD_StringWrite(218, 224, ~(ILI9341_NAVY), 1, "TIME:");
    display_time_string(hr_ascii, min_ascii, sec_ascii);

    LCD_StringWrite(76, 208, ~(ILI9341_BLUE), 2, "EMBEDDED TUNER");
    LCD_StringWrite(100, 176, ~(ILI9341_OLIVE), 2, "MODE: TUNER");

    LCD_StringWrite(30, 144, (ILI9341_INV_ORANGE), 2, "FREQ:");
    LCD_StringWrite(30, 112, ~(ILI9341_DARKGREY), 2, "ERR:");
}

/*
 * Function     :   void display_parameters(int32_t freq, out_note_t note, uint32_t octv, float err)
 * Brief        :   updates frequency, Tone, octave, Error on display if changed
 * Inputs       :   freq - current tone frequency
 *                  note - Tone detected
 *                  octv - octave of current detected tone
 *                  err - +/- difference in detected frequency from expected Tone frequency
 */
void display_parameters(int32_t freq, out_note_t note, uint32_t octv, float err)
{
    static int32_t prevfreq=0;
    static out_note_t prevnote=NO_NOTE;
    static uint32_t prevoctv=0;
    static float preverr=0;
    static uint8_t prevmode = 0;


    if (prevoctv != octv)
    {
        prevoctv = octv;

        if (octv & 1)
            LCD_StringWrite(OCTV_X_POS, OCTV_Y_POS, ~(ILI9341_GREEN), 4, "1");
        else if (octv & 2)
            LCD_StringWrite(OCTV_X_POS, OCTV_Y_POS, ~(ILI9341_GREEN), 4, "2");
        else if (octv & 4)
            LCD_StringWrite(OCTV_X_POS, OCTV_Y_POS, ~(ILI9341_GREEN), 4, "3");
        else if (octv & 8)
            LCD_StringWrite(OCTV_X_POS, OCTV_Y_POS, ~(ILI9341_GREEN), 4, "4");
        else if (octv & 16)
            LCD_StringWrite(OCTV_X_POS, OCTV_Y_POS, ~(ILI9341_GREEN), 4, "5");
        else if (octv & 32)
            LCD_StringWrite(OCTV_X_POS, OCTV_Y_POS, ~(ILI9341_GREEN), 4, "6");
        else
            LCD_StringWrite(OCTV_X_POS, OCTV_Y_POS, ~(ILI9341_GREEN), 4, 0);
    }

    if (prevnote != note)
    {
        prevnote = note;
        if(note == C_SHARP || note == D_SHARP || note == F_SHARP || note == G_SHARP || note == A_SHARP)
        {
            LCD_StringWrite(SHARP_X_POS, SHARP_Y_POS, ~(ILI9341_GREEN), 4, "#");
            notes_log[notes_log_index][1] = '#';
            notes_log[notes_log_index][2] = 0;
        }
        else
        {
            LCD_Rectangle(SHARP_X_POS, SHARP_Y_POS-32, SHARP_X_POS+20, SHARP_Y_POS, 0);
            notes_log[notes_log_index][1] = 0;
        }

        switch(note)
        {
            case C_SHARP:
            case C1:
                LCD_StringWrite(TONE_X_POS, TONE_Y_POS, ~(ILI9341_GREEN), 8, "C");
                get_timestamp(&notes_time_log[notes_log_index][0]);
                notes_log[notes_log_index++][0] = 'C';
                notes_log_index &= 0x7;
                break;

            case D_SHARP:
            case D1:
                LCD_StringWrite(TONE_X_POS, TONE_Y_POS, ~(ILI9341_GREEN), 8, "D");
                get_timestamp(&notes_time_log[notes_log_index][0]);
                notes_log[notes_log_index++][0] = 'D';
                notes_log_index &= 0x7;
                break;

            case E1:
                LCD_StringWrite(TONE_X_POS, TONE_Y_POS, ~(ILI9341_GREEN), 8, "E");
                get_timestamp(&notes_time_log[notes_log_index][0]);
                notes_log[notes_log_index++][0] = 'E';
                notes_log_index &= 0x7;
                break;

            case F_SHARP:
            case F1:
                LCD_StringWrite(TONE_X_POS, TONE_Y_POS, ~(ILI9341_GREEN), 8, "F");
                get_timestamp(&notes_time_log[notes_log_index][0]);
                notes_log[notes_log_index++][0] = 'F';
                notes_log_index &= 0x7;
                break;

            case G_SHARP:
            case G1:
                LCD_StringWrite(TONE_X_POS, TONE_Y_POS, ~(ILI9341_GREEN), 8, "G");
                get_timestamp(&notes_time_log[notes_log_index][0]);
                notes_log[notes_log_index++][0] = 'G';
                notes_log_index &= 0x7;
                break;

            case A_SHARP:
            case A1:
                LCD_StringWrite(TONE_X_POS, TONE_Y_POS, ~(ILI9341_GREEN), 8, "A");
                get_timestamp(&notes_time_log[notes_log_index][0]);
                notes_log[notes_log_index++][0] = 'A';
                notes_log_index &= 0x7;
                break;

            case B1:
                LCD_StringWrite(TONE_X_POS, TONE_Y_POS, ~(ILI9341_GREEN), 8, "B");
                get_timestamp(&notes_time_log[notes_log_index][0]);
                notes_log[notes_log_index++][0] = 'B';
                notes_log_index &= 0x7;
                break;

            default:
                LCD_Rectangle(SHARP_X_POS, SHARP_Y_POS-32, SHARP_X_POS+20, SHARP_Y_POS, 0);
                LCD_Rectangle(TONE_X_POS, TONE_Y_POS-64, TONE_X_POS+40, TONE_Y_POS, 0);
                LCD_Rectangle(OCTV_X_POS, OCTV_Y_POS-32, OCTV_X_POS+20, OCTV_Y_POS, 0);
                break;
        }
    }

    if (prevfreq != freq)
    {
        prevfreq = freq;
        char freqstr[7]={0}, i=0;
        int16_t pos = 0;


        if (prevfreq/1000)
            freqstr[i++] = (char)((prevfreq/1000) + '0');
        else
        {
            pos = 12;
            LCD_Rectangle(FREQ_X_POS, FREQ_Y_POS-16, FREQ_X_POS+10, FREQ_Y_POS, 0);
        }

        prevfreq = prevfreq%1000;

        freqstr[i++] = (char)((prevfreq/100) + '0');

        if((prevfreq/100)==0 && i==1)
        {
            i--;
            LCD_Rectangle(FREQ_X_POS+pos, FREQ_Y_POS-16, FREQ_X_POS+10+pos, FREQ_Y_POS, 0);
            pos = 24;
        }

        prevfreq = prevfreq%100;
        freqstr[i++] = (char)((prevfreq/10) + '0');
        prevfreq = prevfreq%10;
        freqstr[i++] = (char)((prevfreq) + '0');

        freqstr[i++] = 'H';
        freqstr[i] = '\0';

        LCD_StringWrite(FREQ_X_POS+pos, FREQ_Y_POS, (ILI9341_INV_ORANGE), 2, freqstr);
        LCD_StringWrite(FREQ_X_POS+60, FREQ_Y_POS-8, (ILI9341_INV_ORANGE), 1, "Z");

        prevfreq = freq;

    }


    if(get_output_mode()==0)
    {
        if (preverr != err)
        {
            preverr = err;

            if (preverr > 0.05)
            {
                LCD_StringWrite(ERR_X_POS, ERR_Y_POS, ~(ILI9341_BLUE), 2, "SHARP");
            }
            else if (preverr < (-0.05))
            {
                LCD_StringWrite(ERR_X_POS, ERR_Y_POS, ILI9341_INV_RED, 2, "FLAT");
                LCD_Rectangle(ERR_X_POS+48, ERR_Y_POS-16, ERR_X_POS+60, ERR_Y_POS, 0);
            }
            else
            {
                LCD_StringWrite(ERR_X_POS, ERR_Y_POS, ~(ILI9341_GREEN), 2, "TUNED");
            }
        }
    }

    if(get_output_mode())
    {
        if (prevmode != get_output_mode())
        {
            prevmode = get_output_mode();

            LCD_StringWrite(MODE_X_POS, MODE_Y_POS, ~(ILI9341_OLIVE), 2, "PITCH");
            LCD_StringWrite(ERR_X_POS - 60, ERR_Y_POS, ~(ILI9341_DARKGREY), 2, "          ");
        }
    }
    else
    {
        if (prevmode != get_output_mode())
        {
            prevmode = get_output_mode();

            LCD_StringWrite(MODE_X_POS, MODE_Y_POS, ~(ILI9341_OLIVE), 2, "TUNER");
            LCD_StringWrite(ERR_X_POS - 60, ERR_Y_POS, ~(ILI9341_DARKGREY), 2, "ERR:");
        }
    }
}


