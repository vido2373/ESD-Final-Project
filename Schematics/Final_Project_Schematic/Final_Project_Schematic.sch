EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Amplifier_Operational:OP1177AR Op-Amp
U 1 1 607D08F5
P 7317 2914
F 0 "Op-Amp" H 7417 2814 50  0000 L CNN
F 1 "MCP6231-E/P" H 7317 2714 50  0000 L CNN
F 2 "" H 7317 2614 50  0001 C CNN
F 3 "" H 7317 2914 50  0001 C CNN
	1    7317 2914
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 607D1EE4
P 7217 3214
F 0 "#PWR?" H 7217 2964 50  0001 C CNN
F 1 "GND" H 7222 3041 50  0000 C CNN
F 2 "" H 7217 3214 50  0001 C CNN
F 3 "" H 7217 3214 50  0001 C CNN
	1    7217 3214
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D443D
P 6617 3264
F 0 "R" H 6467 3314 50  0000 L CNN
F 1 "47kΩ" H 6367 3214 50  0000 L CNN
F 2 "" V 6657 3254 50  0001 C CNN
F 3 "~" H 6617 3264 50  0001 C CNN
	1    6617 3264
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D4437
P 6617 2564
F 0 "R" H 6467 2614 50  0000 L CNN
F 1 "47kΩ" H 6367 2514 50  0000 L CNN
F 2 "" V 6657 2554 50  0001 C CNN
F 3 "~" H 6617 2564 50  0001 C CNN
	1    6617 2564
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D5469
P 7217 2314
F 0 "R" V 7012 2314 50  0000 C CNN
F 1 "1MΩ" V 7103 2314 50  0000 C CNN
F 2 "" V 7257 2304 50  0001 C CNN
F 3 "~" H 7217 2314 50  0001 C CNN
	1    7217 2314
	0    1    1    0   
$EndComp
$Comp
L Device:C C
U 1 1 607D6315
P 6017 3014
F 0 "C" V 5767 3014 50  0000 C CNN
F 1 "1uF" V 5867 3014 50  0000 C CNN
F 2 "" H 6055 2864 50  0001 C CNN
F 3 "~" H 6017 3014 50  0001 C CNN
	1    6017 3014
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R
U 1 1 607D2F84
P 6317 3014
F 0 "R" V 6117 3014 50  0000 C CNN
F 1 "1kΩ" V 6217 3014 50  0000 C CNN
F 2 "" V 6357 3004 50  0001 C CNN
F 3 "~" H 6317 3014 50  0001 C CNN
	1    6317 3014
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R
U 1 1 607D2956
P 5717 2864
F 0 "R" H 5785 2910 50  0000 L CNN
F 1 "2kΩ" H 5785 2819 50  0000 L CNN
F 2 "" V 5757 2854 50  0001 C CNN
F 3 "~" H 5717 2864 50  0001 C CNN
	1    5717 2864
	1    0    0    -1  
$EndComp
$Comp
L Device:Microphone MK
U 1 1 607D13BF
P 5567 3214
F 0 "MK" H 5317 3264 50  0000 L CNN
F 1 "CMA-4544PF-W" H 4817 3114 50  0000 L CNN
F 2 "" V 5567 3314 50  0001 C CNN
F 3 "~" V 5567 3314 50  0001 C CNN
	1    5567 3214
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607EA2D2
P 7217 2014
F 0 "R" V 7012 2014 50  0000 C CNN
F 1 "1MΩ" V 7103 2014 50  0000 C CNN
F 2 "" V 7257 2004 50  0001 C CNN
F 3 "~" H 7217 2014 50  0001 C CNN
	1    7217 2014
	0    1    1    0   
$EndComp
Wire Wire Line
	5567 3014 5717 3014
Wire Wire Line
	5717 3014 5867 3014
Connection ~ 5717 3014
Wire Wire Line
	6467 3014 6767 3014
Wire Wire Line
	6617 2714 6617 2814
Wire Wire Line
	7617 2914 7867 2914
Wire Wire Line
	7867 2914 7867 2164
Wire Wire Line
	7867 2164 7367 2164
Wire Wire Line
	7367 2164 7367 2314
Wire Wire Line
	7367 2014 7367 2164
Connection ~ 7367 2164
Wire Wire Line
	7067 2314 7067 2164
Wire Wire Line
	7067 2164 6767 2164
Connection ~ 7067 2164
Wire Wire Line
	7067 2164 7067 2014
Connection ~ 6767 3014
Wire Wire Line
	6767 3014 7017 3014
$Comp
L power:GND #PWR?
U 1 1 607ECE2C
P 6617 3414
F 0 "#PWR?" H 6617 3164 50  0001 C CNN
F 1 "GND" H 6622 3241 50  0000 C CNN
F 2 "" H 6617 3414 50  0001 C CNN
F 3 "" H 6617 3414 50  0001 C CNN
	1    6617 3414
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 607ED134
P 5567 3414
F 0 "#PWR?" H 5567 3164 50  0001 C CNN
F 1 "GND" H 5572 3241 50  0000 C CNN
F 2 "" H 5567 3414 50  0001 C CNN
F 3 "" H 5567 3414 50  0001 C CNN
	1    5567 3414
	1    0    0    -1  
$EndComp
Connection ~ 6617 2814
Wire Wire Line
	6617 2814 6617 3114
$Comp
L Final_Project_Schematic-rescue:MSP432P401R-MSP432 MCU
U 1 1 60818468
P 8860 3164
F 0 "MCU" H 8860 1241 50  0000 C CNN
F 1 "MSP432P401R" H 8860 1150 50  0000 C CNN
F 2 "" H 8860 4364 50  0001 C CNN
F 3 "" H 8860 4364 50  0001 C CNN
	1    8860 3164
	1    0    0    -1  
$EndComp
Connection ~ 7867 2914
Wire Wire Line
	7217 2414 7217 2614
Connection ~ 7217 2414
Wire Wire Line
	6617 2414 5717 2414
Wire Wire Line
	5717 2414 5717 2714
Connection ~ 6617 2414
Wire Wire Line
	6617 2414 7217 2414
Text Label 7217 2514 0    50   ~ 0
+3.3V
Text Label 6367 2414 0    50   ~ 0
+3.3V
Text Label 8010 2914 0    50   ~ 0
ADC_In
Text Label 7617 2914 0    50   ~ 0
V_Out
Text Label 5717 2714 0    50   ~ 0
+3.3V
Text Label 6817 2814 0    50   ~ 0
1.65V
Wire Wire Line
	6617 2814 7017 2814
Wire Wire Line
	6767 2164 6767 3014
Text Label 6867 3014 0    50   ~ 0
V_In
$Comp
L Switch:SW_Push SW?
U 1 1 6085F419
P 4459 6324
F 0 "SW?" H 4459 6609 50  0000 C CNN
F 1 "SW_Push" H 4459 6518 50  0000 C CNN
F 2 "" H 4459 6524 50  0001 C CNN
F 3 "~" H 4459 6524 50  0001 C CNN
	1    4459 6324
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 60861752
P 5121 6552
F 0 "R?" H 4971 6602 50  0000 L CNN
F 1 "47kΩ" H 4871 6502 50  0000 L CNN
F 2 "" V 5161 6542 50  0001 C CNN
F 3 "~" H 5121 6552 50  0001 C CNN
	1    5121 6552
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60861758
P 5121 6702
F 0 "#PWR?" H 5121 6452 50  0001 C CNN
F 1 "GND" H 5126 6529 50  0000 C CNN
F 2 "" H 5121 6702 50  0001 C CNN
F 3 "" H 5121 6702 50  0001 C CNN
	1    5121 6702
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 6086255F
P 3999 6197
F 0 "R?" H 3849 6247 50  0000 L CNN
F 1 "47kΩ" H 3749 6147 50  0000 L CNN
F 2 "" V 4039 6187 50  0001 C CNN
F 3 "~" H 3999 6197 50  0001 C CNN
	1    3999 6197
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6086355F
P 5782 6577
F 0 "C?" V 5532 6577 50  0000 C CNN
F 1 "1uF" V 5632 6577 50  0000 C CNN
F 2 "" H 5820 6427 50  0001 C CNN
F 3 "~" H 5782 6577 50  0001 C CNN
	1    5782 6577
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 60863AED
P 5380 6518
F 0 "D?" V 5426 6438 50  0000 R CNN
F 1 "1N4148" V 5335 6438 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5380 6343 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5380 6518 50  0001 C CNN
	1    5380 6518
	0    -1   -1   0   
$EndComp
$Comp
L Timer_RTC:DS1337 RTC
U 1 1 60869574
P 6049 4523
F 0 "RTC" H 6052 5104 50  0000 C CNN
F 1 "DS1337" H 6052 5013 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6049 4023 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DS1307.pdf" H 6049 4323 50  0001 C CNN
	1    6049 4523
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 6086A80B
P 1122 3894
F 0 "R?" H 972 3944 50  0000 L CNN
F 1 "47kΩ" H 872 3844 50  0000 L CNN
F 2 "" V 1162 3884 50  0001 C CNN
F 3 "~" H 1122 3894 50  0001 C CNN
	1    1122 3894
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 6086AF74
P 868 3877
F 0 "R?" H 718 3927 50  0000 L CNN
F 1 "47kΩ" H 618 3827 50  0000 L CNN
F 2 "" V 908 3867 50  0001 C CNN
F 3 "~" H 868 3877 50  0001 C CNN
	1    868  3877
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6086C37F
P 2757 3854
F 0 "C?" V 2507 3854 50  0000 C CNN
F 1 "1uF" V 2607 3854 50  0000 C CNN
F 2 "" H 2795 3704 50  0001 C CNN
F 3 "~" H 2757 3854 50  0001 C CNN
	1    2757 3854
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6086CA15
P 868 4877
F 0 "C?" V 618 4877 50  0000 C CNN
F 1 "1uF" V 718 4877 50  0000 C CNN
F 2 "" H 906 4727 50  0001 C CNN
F 3 "~" H 868 4877 50  0001 C CNN
	1    868  4877
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6086CFA1
P 1243 4871
F 0 "C?" V 993 4871 50  0000 C CNN
F 1 "1uF" V 1093 4871 50  0000 C CNN
F 2 "" H 1281 4721 50  0001 C CNN
F 3 "~" H 1243 4871 50  0001 C CNN
	1    1243 4871
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y?
U 1 1 6086D7B6
P 1066 4451
F 0 "Y?" H 1066 4719 50  0000 C CNN
F 1 "Crystal" H 1066 4628 50  0000 C CNN
F 2 "" H 1066 4451 50  0001 C CNN
F 3 "~" H 1066 4451 50  0001 C CNN
	1    1066 4451
	1    0    0    -1  
$EndComp
Wire Wire Line
	7217 2414 8260 2414
Wire Wire Line
	7867 2914 8260 2914
$Comp
L power:Signal_In SW_IN
U 1 1 608872AC
P 8103 2814
F 0 "SW_IN" H 7944 2901 61  0000 L CNN
F 1 "Signal_In" H 8287 2777 61  0001 L CNN
F 2 "" H 8110 2903 61  0001 C CNN
F 3 "" H 8110 2903 61  0001 C CNN
	1    8103 2814
	1    0    0    -1  
$EndComp
Wire Wire Line
	8262 3214 8260 3214
Connection ~ 8260 3214
Wire Wire Line
	8260 3214 7737 3214
Wire Wire Line
	8260 3314 7833 3314
$EndSCHEMATC
