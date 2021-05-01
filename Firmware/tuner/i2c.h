/*************************************************************
 * File     :   i2c.h
 * Made by  :   Mukta Darekar
 * Date     :   2nd April 2021
 * Brief    :   defines related to i2c 
 *************************************************************/

#ifndef _I2C_H_
#define _I2C_H_

/*
 * Function     :   void init_i2c(void)
 * Brief        :   initializes I2C for RTC IC and sets SCL of 100KHz
 */
void init_i2c(void);
/*
 * Function     :   void set_time()
 * Brief        :   can be used to set time in DS1337 as per requirement
 *                  used only once while setting initial real time in DS1337
 *                  then removed from main loop
 */
void set_time();
/*
 * Function     :   void read_time()
 * Brief        :   First sends device address and location pointer
 *                  then starts reading
 */
void read_time();
/*
 * Function     :   void set_int_rtc()
 * Brief        :   setting up internal RTC
 */
void set_int_rtc();

#endif  //_I2C_H_
