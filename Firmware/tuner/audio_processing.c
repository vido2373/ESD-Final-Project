/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   LCD_240x320.h
 * Date     :   04/16/2021
 * Reference:   Code taken from boostxl_edumkii_microphonefft_msp432p401r_MSP_EXP432P401R_nortos_ccs project in SDK
 * Modifications    :   implemented ADC in bare metal
 *                      performed frequency calculation from FFT output
 *******************************************************************************/

#include "audio_processing.h"
#include "clock_and_timer.h"
#include <stdint.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <arm_math.h>
#include <arm_const_structs.h>
#include <math.h>

#define SMCLK_FREQUENCY     48000000
#define SAMPLE_FREQUENCY    4096
#define SAMPLE_LENGTH (1024)

/* ------------------------------------------------------------------
 * Global variables for FFT
 * ------------------------------------------------------------------- */
static uint32_t fftSize = SAMPLE_LENGTH;
static uint32_t ifftFlag = 0;
static uint32_t doBitReverse = 1;
static volatile arm_status status;


/* DMA Control Table */
#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_ALIGN(MSP_EXP432P401RLP_DMAControlTable, 8192)
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=2048
#elif defined(__GNUC__)
__attribute__ ((aligned (2048)))
#elif defined(__CC_ARM)
__align(2048)
#endif
static DMA_ControlTable MSP_EXP432P401RLP_DMAControlTable[32];

/* FFT data/processing buffers*/
static float hann[SAMPLE_LENGTH];
static int16_t data_array1[SAMPLE_LENGTH];
static int16_t data_array2[SAMPLE_LENGTH];
static int16_t data_input[SAMPLE_LENGTH * 2];
static int16_t data_output[SAMPLE_LENGTH];

static volatile int switch_data = 0;

/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfig =
{
    TIMER_A_CLOCKSOURCE_SMCLK,
    TIMER_A_CLOCKSOURCE_DIVIDER_1,
    (SMCLK_FREQUENCY / SAMPLE_FREQUENCY),
    TIMER_A_CAPTURECOMPARE_REGISTER_1,
    TIMER_A_OUTPUTMODE_SET_RESET,
    (SMCLK_FREQUENCY / SAMPLE_FREQUENCY) / 2
};


/*
 * Function     :   void init_audio_peripherals(void)
 * Brief        :   Initializes the TPM, ADC, and DMA
 */
void init_audio_peripherals(void) {
    //CLK_Init();
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

    //student written code//
    ADC14->CTL0 &= ~ADC14_CTL0_ENC; //disable adc
    ADC14->CTL0 |= ADC14_CTL0_ON | ADC14_CTL0_SSEL__MCLK; //turn on ADC14 and route MCLK (48 MHz) to it
    ADC14->CTL0 |= ADC_TRIGGER_SOURCE1; //ADC triggers off of Timer0
    ADC14->CTL1 &= ~(ADC_MAPINTCH3 | ADC_MAPINTCH2 | ADC_MAPINTCH1 | ADC_MAPINTCH0
                        | ADC_TEMPSENSEMAP | ADC_BATTMAP);

    P4->SEL0 |= BIT3; //Set Pin 4.3 as ADC input
    P4->SEL1 |= BIT3;

    ADC14->CTL1 |= (0 << ADC14_CTL1_CSTARTADD_OFS); //set destination to ADC_MEM0
    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_2; //set repeat-single-channel mode

    ADC14->MCTL[0] |= ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_10; //set ADC to use channel 10, default ref voltage

    ADC14->CTL1 |= ADC14_CTL1_DF; //set output to be signed binary

    /* Configuring DMA module
     * Code taken from boostxl_edumkii_microphonefft_msp432p401r_MSP_EXP432P401R_nortos_ccs project in SDK */
    DMA_enableModule();
    DMA_setControlBase(MSP_EXP432P401RLP_DMAControlTable);

    DMA_disableChannelAttribute(DMA_CH7_ADC14,
                                UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                UDMA_ATTR_HIGH_PRIORITY |
                                UDMA_ATTR_REQMASK);

    /* Setting Control Indexes. In this case we will set the source of the
     * DMA transfer to ADC14 Memory 0
     *  and the destination to the
     * destination data array. */
    MAP_DMA_setChannelControl(
        UDMA_PRI_SELECT | DMA_CH7_ADC14,
        UDMA_SIZE_16 | UDMA_SRC_INC_NONE |
        UDMA_DST_INC_16 | UDMA_ARB_1);
    MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
                               UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
                               data_array1, SAMPLE_LENGTH);

    MAP_DMA_setChannelControl(
        UDMA_ALT_SELECT | DMA_CH7_ADC14,
        UDMA_SIZE_16 | UDMA_SRC_INC_NONE |
        UDMA_DST_INC_16 | UDMA_ARB_1);
    MAP_DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC14,
                               UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
                               data_array2, SAMPLE_LENGTH);

    /* Assigning/Enabling Interrupts */
    MAP_DMA_assignInterrupt(DMA_INT1, 7);
    MAP_Interrupt_enableInterrupt(INT_DMA_INT1);
    MAP_DMA_assignChannel(DMA_CH7_ADC14);
    MAP_DMA_clearInterruptFlag(7);
    MAP_Interrupt_enableMaster();

    /* Now that the DMA is primed and setup, enabling the channels. The ADC14
     * hardware should take over and transfer/receive all bytes */
    MAP_DMA_enableChannel(7);
    //MAP_ADC14_enableConversion();
    //student code
    ADC14->CTL0 |= ADC14_CTL0_ENC; //enable adc
}

/*
 * Function     :   void init_hanning_window(void)
 * Brief        :   Initializes Hanning window for windowing samples
 */
void init_hanning_window(void) {
    int n;
    for(n = 0; n < SAMPLE_LENGTH; n++)
    {
        hann[n] = 0.5f - 0.5f * cosf((2 * PI * n) / (SAMPLE_LENGTH - 1));
    }
}

/*
 * Function     :   void get_frequency_from_samples(int32_t* frequency)
 * Brief        :   Performs windowing and FFT on sample buffer, and gets the frequency
 * Inputs       :   frequency - frequency of signal stored in sample buffer
 */
void get_frequency_from_samples(int32_t* frequency) {
    /* Code taken from boostxl_edumkii_microphonefft_msp432p401r_MSP_EXP432P401R_nortos_ccs project in SDK */
    MAP_PCM_gotoLPM0();

    int i = 0;

    /* Computer real FFT using the completed data buffer */
    if(switch_data & 1)
    {
        for(i = 0; i < SAMPLE_LENGTH; i++)
        {
            data_array1[i] = (int16_t)(hann[i] * data_array1[i]);
        }
        arm_rfft_instance_q15 instance;
        status = arm_rfft_init_q15(&instance, fftSize, ifftFlag,
                                   doBitReverse);

        arm_rfft_q15(&instance, data_array1, data_input);
    }
    else
    {
        for(i = 0; i < SAMPLE_LENGTH; i++)
        {
            data_array2[i] = (int16_t)(hann[i] * data_array2[i]);
        }
        arm_rfft_instance_q15 instance;
        status = arm_rfft_init_q15(&instance, fftSize, ifftFlag,
                                   doBitReverse);

        arm_rfft_q15(&instance, data_array2, data_input);
    }

    /* Calculate magnitude of FFT complex output */
    for(i = 0; i < (SAMPLE_LENGTH * 2); i += 2)
    {
        data_output[i /
                    2] =
            (int32_t)(sqrtf((data_input[i] *
                             data_input[i]) +
                            (data_input[i + 1] * data_input[i + 1])));
    }

    q15_t maxValue;
    uint32_t maxIndex = 0;

    arm_max_q15(data_output, fftSize, &maxValue, &maxIndex);
    //student code
    *frequency = (maxIndex << 2);
}

/*
 * Function     :   void DMA_INT1_IRQHandler(void)
 * Brief        :   DMA IRQ Handler
 *
 * Code taken from boostxl_edumkii_microphonefft_msp432p401r_MSP_EXP432P401R_nortos_ccs project in SDK */
void DMA_INT1_IRQHandler(void)
{
    /* Code taken from boostxl_edumkii_microphonefft_msp432p401r_MSP_EXP432P401R_nortos_ccs project in SDK */
    /* Switch between primary and alternate bufferes with DMA's PingPong mode */
    if(DMA_getChannelAttribute(7) & UDMA_ATTR_ALTSELECT)
    {
        DMA_setChannelControl(
            UDMA_PRI_SELECT | DMA_CH7_ADC14,
            UDMA_SIZE_16 | UDMA_SRC_INC_NONE |
            UDMA_DST_INC_16 | UDMA_ARB_1);
        DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
                               UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
                               data_array1, SAMPLE_LENGTH);
        switch_data = 1;
    }
    else
    {
        DMA_setChannelControl(
            UDMA_ALT_SELECT | DMA_CH7_ADC14,
            UDMA_SIZE_16 | UDMA_SRC_INC_NONE |
            UDMA_DST_INC_16 | UDMA_ARB_1);
        DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC14,
                               UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
                               data_array2, SAMPLE_LENGTH);
        switch_data = 0;
    }
}
