/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   tuning.h
 * Author   :   Vishnu Dodballapur
 * Date     :   04/16/2021
 * Brief    :   defines related to tuning
 *******************************************************************************/

#ifndef TUNING_H_
#define TUNING_H_

#include <stdint.h>
#include <stdlib.h>

//note_t: holds frequency of note
typedef float note_t;

/*
 * Function     :   void get_tuning_data(int32_t frequency, note_t* out_note, uint32_t* octave, float* error)
 * Brief        :   Gets tuning data based on the frequency
 * Inputs       :   frequency - current tone frequency
 *                  out_note - Tone detected
 *                  octave - base octave of current detected tone
 *                  error - +/- difference in detected frequency from expected tone frequency
 */
void get_tuning_data(int32_t frequency, note_t* out_note, uint32_t* octave, float* error);


#endif /* TUNING_H_ */
