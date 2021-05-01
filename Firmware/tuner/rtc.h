/**************************************************************
 * File     :   rtc.h
 * Made by  :   Mukta Darekar
 * Date     :   2nd April 2021
 * Brief    :   defines related to rtc
 **************************************************************/

#ifndef _RTC_H_
#define _RTC_H_


/*
 * Function     :   void init_rtc()
 * Brief        :   initializes internal RTC
 */
void init_rtc();

/*
 * Function     :   void display_date_string(char *str)
 * Brief        :   to display date read from internal RTC on LCD
 */
void display_date_string(char *str);

/*
 * Function     :   void display_time_string(char *strhr, char *strmin, char *strsec)
 * Brief        :   to display time read from internal RTC on LCD
 */
void display_time_string(char *strhr, char *strmin, char *strsec);

/*
 * Function     :   void get_timestamp(uint8_t *str)
 * Brief        :   to get time and date for logging purpose
 */
void get_timestamp(uint8_t *str);

#endif  //_RTC_H_
