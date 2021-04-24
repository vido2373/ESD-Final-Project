/*
 * audio_processing.h
 *
 *  Created on: Apr 16, 2021
 *      Author: vishn
 */

#ifndef AUDIO_PROCESSING_H_
#define AUDIO_PROCESSING_H_

#include <stdint.h>

void init_audio_peripherals(void);
void init_hanning_window(void);
void get_frequency_from_samples(int32_t* frequency);



#endif /* AUDIO_PROCESSING_H_ */
