/*
 * File     :   rtc.h
 * Made by  :   Mukta Darekar
 * Date     :   2nd April 2021
 * Brief    :   defines related to rtc
 */

#ifndef _RTC_H_
#define _RTC_H_

void init_rtc();

void display_date_string(char *str);

void display_time_string(char *strhr, char *strmin, char *strsec);

void get_timestamp(uint8_t *str);

#endif  //_RTC_H_
