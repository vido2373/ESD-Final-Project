/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   switch.h
 * Author   :   Vishnu Dodballapur
 * Date     :   04/2/2021
 * Brief    :   defines related to push button switch
 *******************************************************************************/

#ifndef _SWITCH_H_
#define _SWITCH_H_

#include <stdint.h>

/*
 * Function     :   void init_switch(void)
 * Brief        :   Initializes push button for falling-edge interrupt detection
 */
void init_switch(void);
/*
 * Function     :   uint8_t get_output_mode(void)
 * Brief        :   Returns the output mode of the tuner
 * Return       :   1 if pitch mode, 0 if tuner mode
 */
uint8_t get_output_mode(void);

#endif  //_SWITCH_H_
