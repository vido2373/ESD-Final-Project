/*
 * tuning.h
 *
 *  Created on: Apr 16, 2021
 *      Author: vishn
 */

#ifndef TUNING_H_
#define TUNING_H_

#include <stdint.h>
#include <stdlib.h>

typedef float note_t;

void get_tuning_data(int32_t frequency, note_t* out_note, uint32_t* octave, float* error);



#endif /* TUNING_H_ */
