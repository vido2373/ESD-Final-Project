/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   tuning.c
 * Author   :   Vishnu Dodballapur
 * Date     :   04/16/2021
 *******************************************************************************/

#include "tuning.h"
#include <stdint.h>
#include <float.h>

//frequencies of notes from C1 to B1
#define NUM_NOTES (12)

#define C1 (32.70)
#define C_SHARP (34.65)
#define D1 (36.71)
#define D_SHARP (38.89)
#define E1 (41.20)
#define F1 (43.65)
#define F_SHARP (46.25)
#define G1 (49.00)
#define G_SHARP (51.91)
#define A1 (55.0)
#define A_SHARP (58.27)
#define B1 (61.74)

//array to hold frequencies of notes from C1 to B1
static note_t notes[NUM_NOTES] = {
    C1, C_SHARP, D1, D_SHARP, E1, F1,
    F_SHARP, G1, G_SHARP, A1, A_SHARP, B1,
};

/*
 * Function     :   void get_tuning_data(int32_t frequency, note_t* out_note, uint32_t* octave, float* error)
 * Brief        :   Gets tuning data based on the frequency
 * Inputs       :   frequency - current tone frequency
 *                  out_note - Tone detected
 *                  octave - base octave of current detected tone
 *                  error - +/- difference in detected frequency from expected tone frequency
 */
void get_tuning_data(int32_t frequency, note_t* out_note, uint32_t* octave, float* error) {
    uint32_t base_octave;
    float min_err = FLT_MAX;
    float calc_err;
    int i;

    //get previous power of 2 to determine the base_octave of the note
    base_octave = (uint32_t)(frequency/ C1);
    base_octave = base_octave | (base_octave >> 1);
    base_octave = base_octave | (base_octave >> 2);
    base_octave = base_octave | (base_octave >> 4);
    base_octave = base_octave | (base_octave >> 8);
    base_octave = base_octave | (base_octave >> 16);
    base_octave = base_octave - (base_octave >> 1);

    //find note being played by finding lowest error
    for (i = 0; i < NUM_NOTES; i++) {
        calc_err = ((frequency) / notes[i]) - base_octave;
        if (fabs(calc_err) < fabs(min_err)) {
            min_err = calc_err;
            *out_note = notes[i];
        }
    }

    //handle upper edge case (i.e. 129 Hz rounds up to 130 Hz)
    calc_err = ((frequency) / C1) - (base_octave << 1);
    if (fabs(calc_err) < fabs(min_err)) {
        min_err = calc_err;
        *out_note = C1;
        base_octave = base_octave << 1;
    }

    *error = min_err;
    *octave = base_octave;
}


