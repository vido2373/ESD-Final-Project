/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   LCD_240x320.h
 * Date     :   04/16/2021
 * Brief    :   Perform audio processing on waveform read into MCU
 * Reference:   Code taken from boostxl_edumkii_microphonefft_msp432p401r_MSP_EXP432P401R_nortos_ccs project in SDK
 *******************************************************************************/

#ifndef AUDIO_PROCESSING_H_
#define AUDIO_PROCESSING_H_

#include <stdint.h>

/*
 * Function     :   void init_audio_peripherals(void)
 * Brief        :   Initializes the TPM, ADC, and DMA
 */
void init_audio_peripherals(void);
/*
 * Function     :   void init_hanning_window(void)
 * Brief        :   Initializes Hanning window for windowing samples
 */
void init_hanning_window(void);
/*
 * Function     :   void DMA_INT1_IRQHandler(void)
 * Brief        :   DMA IRQ Handler
 *
 */
void get_frequency_from_samples(int32_t* frequency);



#endif /* AUDIO_PROCESSING_H_ */
