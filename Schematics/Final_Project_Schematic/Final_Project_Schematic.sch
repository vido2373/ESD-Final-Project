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
P 4308 2483
F 0 "Op-Amp" H 4408 2383 50  0000 L CNN
F 1 "MCP6231-E/P" H 4308 2283 50  0000 L CNN
F 2 "" H 4308 2183 50  0001 C CNN
F 3 "" H 4308 2483 50  0001 C CNN
	1    4308 2483
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 607D1EE4
P 4208 2783
F 0 "#PWR?" H 4208 2533 50  0001 C CNN
F 1 "GND" H 4213 2610 50  0000 C CNN
F 2 "" H 4208 2783 50  0001 C CNN
F 3 "" H 4208 2783 50  0001 C CNN
	1    4208 2783
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D443D
P 3608 2833
F 0 "R" H 3458 2883 50  0000 L CNN
F 1 "47kΩ" H 3358 2783 50  0000 L CNN
F 2 "" V 3648 2823 50  0001 C CNN
F 3 "~" H 3608 2833 50  0001 C CNN
	1    3608 2833
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D4437
P 3608 2133
F 0 "R" H 3458 2183 50  0000 L CNN
F 1 "47kΩ" H 3358 2083 50  0000 L CNN
F 2 "" V 3648 2123 50  0001 C CNN
F 3 "~" H 3608 2133 50  0001 C CNN
	1    3608 2133
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D5469
P 4208 1883
F 0 "R" V 4003 1883 50  0000 C CNN
F 1 "1MΩ" V 4094 1883 50  0000 C CNN
F 2 "" V 4248 1873 50  0001 C CNN
F 3 "~" H 4208 1883 50  0001 C CNN
	1    4208 1883
	0    1    1    0   
$EndComp
$Comp
L Device:C C
U 1 1 607D6315
P 3008 2583
F 0 "C" V 2758 2583 50  0000 C CNN
F 1 "1uF" V 2858 2583 50  0000 C CNN
F 2 "" H 3046 2433 50  0001 C CNN
F 3 "~" H 3008 2583 50  0001 C CNN
	1    3008 2583
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R
U 1 1 607D2F84
P 3308 2583
F 0 "R" V 3108 2583 50  0000 C CNN
F 1 "1kΩ" V 3208 2583 50  0000 C CNN
F 2 "" V 3348 2573 50  0001 C CNN
F 3 "~" H 3308 2583 50  0001 C CNN
	1    3308 2583
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R
U 1 1 607D2956
P 2708 2433
F 0 "R" H 2776 2479 50  0000 L CNN
F 1 "2kΩ" H 2776 2388 50  0000 L CNN
F 2 "" V 2748 2423 50  0001 C CNN
F 3 "~" H 2708 2433 50  0001 C CNN
	1    2708 2433
	1    0    0    -1  
$EndComp
$Comp
L Device:Microphone MK
U 1 1 607D13BF
P 2558 2783
F 0 "MK" H 2308 2833 50  0000 L CNN
F 1 "CMA-4544PF-W" H 1808 2683 50  0000 L CNN
F 2 "" V 2558 2883 50  0001 C CNN
F 3 "~" V 2558 2883 50  0001 C CNN
	1    2558 2783
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607EA2D2
P 4208 1583
F 0 "R" V 4003 1583 50  0000 C CNN
F 1 "1MΩ" V 4094 1583 50  0000 C CNN
F 2 "" V 4248 1573 50  0001 C CNN
F 3 "~" H 4208 1583 50  0001 C CNN
	1    4208 1583
	0    1    1    0   
$EndComp
Wire Wire Line
	2558 2583 2708 2583
Wire Wire Line
	2708 2583 2858 2583
Connection ~ 2708 2583
Wire Wire Line
	3458 2583 3758 2583
Wire Wire Line
	3608 2283 3608 2383
Wire Wire Line
	4608 2483 4858 2483
Wire Wire Line
	4858 2483 4858 1733
Wire Wire Line
	4858 1733 4358 1733
Wire Wire Line
	4358 1733 4358 1883
Wire Wire Line
	4358 1583 4358 1733
Connection ~ 4358 1733
Wire Wire Line
	4058 1883 4058 1733
Wire Wire Line
	4058 1733 3758 1733
Connection ~ 4058 1733
Wire Wire Line
	4058 1733 4058 1583
Connection ~ 3758 2583
Wire Wire Line
	3758 2583 4008 2583
$Comp
L power:GND #PWR?
U 1 1 607ECE2C
P 3608 2983
F 0 "#PWR?" H 3608 2733 50  0001 C CNN
F 1 "GND" H 3613 2810 50  0000 C CNN
F 2 "" H 3608 2983 50  0001 C CNN
F 3 "" H 3608 2983 50  0001 C CNN
	1    3608 2983
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 607ED134
P 2558 2983
F 0 "#PWR?" H 2558 2733 50  0001 C CNN
F 1 "GND" H 2563 2810 50  0000 C CNN
F 2 "" H 2558 2983 50  0001 C CNN
F 3 "" H 2558 2983 50  0001 C CNN
	1    2558 2983
	1    0    0    -1  
$EndComp
Connection ~ 3608 2383
Wire Wire Line
	3608 2383 3608 2683
$Comp
L Final_Project_Schematic-rescue:MSP432P401R-MSP432 MCU
U 1 1 60818468
P 5851 2733
F 0 "MCU" H 5851 810 50  0000 C CNN
F 1 "MSP432P401R" H 5851 719 50  0000 C CNN
F 2 "" H 5851 3933 50  0001 C CNN
F 3 "" H 5851 3933 50  0001 C CNN
	1    5851 2733
	1    0    0    -1  
$EndComp
Connection ~ 4858 2483
Wire Wire Line
	4208 1983 4208 2183
Connection ~ 4208 1983
Wire Wire Line
	3608 1983 2708 1983
Wire Wire Line
	2708 1983 2708 2283
Connection ~ 3608 1983
Wire Wire Line
	3608 1983 4208 1983
Text Label 4208 2083 0    50   ~ 0
+3.3V
Text Label 3358 1983 0    50   ~ 0
+3.3V
Text Label 5001 2483 0    50   ~ 0
ADC_In
Text Label 4608 2483 0    50   ~ 0
V_Out
Text Label 2708 2283 0    50   ~ 0
+3.3V
Text Label 3808 2383 0    50   ~ 0
1.65V
Wire Wire Line
	3608 2383 4008 2383
Wire Wire Line
	3758 1733 3758 2583
Text Label 3858 2583 0    50   ~ 0
V_In
$Comp
L Switch:SW_Push SW1
U 1 1 6085F419
P 2693 5369
F 0 "SW1" H 2693 5654 50  0000 C CNN
F 1 "SW_Push" H 2693 5563 50  0000 C CNN
F 2 "" H 2693 5569 50  0001 C CNN
F 3 "~" H 2693 5569 50  0001 C CNN
	1    2693 5369
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R4
U 1 1 60861752
P 3142 5369
F 0 "R4" V 3050 5370 50  0000 L CNN
F 1 "10kΩ" V 2978 5347 50  0000 L CNN
F 2 "" V 3182 5359 50  0001 C CNN
F 3 "~" H 3142 5369 50  0001 C CNN
	1    3142 5369
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60861758
P 3492 5669
F 0 "#PWR?" H 3492 5419 50  0001 C CNN
F 1 "GND" H 3497 5496 50  0000 C CNN
F 2 "" H 3492 5669 50  0001 C CNN
F 3 "" H 3492 5669 50  0001 C CNN
	1    3492 5669
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R3
U 1 1 6086255F
P 2291 5218
F 0 "R3" H 2141 5268 50  0000 L CNN
F 1 "10kΩ" H 2041 5168 50  0000 L CNN
F 2 "" V 2331 5208 50  0001 C CNN
F 3 "~" H 2291 5218 50  0001 C CNN
	1    2291 5218
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 6086355F
P 3492 5519
F 0 "C4" H 3660 5526 50  0000 C CNN
F 1 "0.1uF" H 3681 5435 50  0000 C CNN
F 2 "" H 3530 5369 50  0001 C CNN
F 3 "~" H 3492 5519 50  0001 C CNN
	1    3492 5519
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D1
U 1 1 60863AED
P 3141 5269
F 0 "D1" H 3226 5177 50  0000 R CNN
F 1 "1N4148" H 3305 5098 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3141 5094 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3141 5269 50  0001 C CNN
	1    3141 5269
	-1   0    0    1   
$EndComp
$Comp
L Final_Project_Schematic-rescue:DS1337-Timer_RTC RTC
U 1 1 60869574
P 3488 3970
F 0 "RTC" H 3257 4419 50  0000 C CNN
F 1 "DS1337" H 3253 4326 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 3488 3470 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DS1307.pdf" H 3488 3770 50  0001 C CNN
	1    3488 3970
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 6086A80B
P 4491 3720
F 0 "R2" H 4340 3805 50  0000 L CNN
F 1 "4.7kΩ" H 4227 3718 50  0000 L CNN
F 2 "" V 4531 3710 50  0001 C CNN
F 3 "~" H 4491 3720 50  0001 C CNN
	1    4491 3720
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 6086AF74
P 4192 3620
F 0 "R1" H 4042 3670 50  0000 L CNN
F 1 "4.7kΩ" H 3921 3585 50  0000 L CNN
F 2 "" V 4232 3610 50  0001 C CNN
F 3 "~" H 4192 3620 50  0001 C CNN
	1    4192 3620
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 6086C37F
P 2592 3720
F 0 "C3" H 2415 3729 50  0000 C CNN
F 1 "0.1uF" H 2470 3614 50  0000 C CNN
F 2 "" H 2630 3570 50  0001 C CNN
F 3 "~" H 2592 3720 50  0001 C CNN
	1    2592 3720
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6086CA15
P 4091 4519
F 0 "C1" H 3849 4613 50  0000 C CNN
F 1 "33pF" H 3845 4504 50  0000 C CNN
F 2 "" H 4129 4369 50  0001 C CNN
F 3 "~" H 4091 4519 50  0001 C CNN
	1    4091 4519
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 6086CFA1
P 4789 4519
F 0 "C2" H 4540 4566 50  0000 C CNN
F 1 "33pF" H 4551 4469 50  0000 C CNN
F 2 "" H 4827 4369 50  0001 C CNN
F 3 "~" H 4789 4519 50  0001 C CNN
	1    4789 4519
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal 32.768KHz
U 1 1 6086D7B6
P 4391 4220
F 0 "32.768KHz" V 4601 4229 50  0000 C CNN
F 1 "Crystal" V 4596 3868 50  0000 C CNN
F 2 "" H 4391 4220 50  0001 C CNN
F 3 "~" H 4391 4220 50  0001 C CNN
	1    4391 4220
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4208 1983 5251 1983
Wire Wire Line
	4858 2483 5251 2483
$Comp
L Final_Project_Schematic-rescue:Signal_In-power SW_IN
U 1 1 608872AC
P 5094 2383
F 0 "SW_IN" H 4935 2470 61  0000 L CNN
F 1 "Signal_In" H 5278 2346 61  0001 L CNN
F 2 "" H 5101 2472 61  0001 C CNN
F 3 "" H 5101 2472 61  0001 C CNN
	1    5094 2383
	1    0    0    -1  
$EndComp
Wire Wire Line
	5253 2783 5251 2783
Connection ~ 5251 2783
Wire Wire Line
	5251 2783 4728 2783
Wire Wire Line
	5251 2883 4824 2883
Wire Wire Line
	3987 3770 3988 3770
Wire Wire Line
	4728 3770 4728 2783
Connection ~ 3988 3770
Wire Wire Line
	3988 3770 4192 3770
Wire Wire Line
	3986 3870 3988 3870
Wire Wire Line
	4824 3870 4824 2883
Connection ~ 3988 3870
Wire Wire Line
	3988 3870 4491 3870
$Comp
L power:GND #PWR?
U 1 1 6086A51C
P 3488 4768
F 0 "#PWR?" H 3488 4518 50  0001 C CNN
F 1 "GND" H 3493 4595 50  0000 C CNN
F 2 "" H 3488 4768 50  0001 C CNN
F 3 "" H 3488 4768 50  0001 C CNN
	1    3488 4768
	1    0    0    -1  
$EndComp
Wire Wire Line
	3488 4369 3488 4370
Connection ~ 3488 4370
Connection ~ 3488 4768
Wire Wire Line
	3488 4768 3488 4770
Wire Wire Line
	4789 4669 4091 4669
Wire Wire Line
	3488 4370 3488 4669
Connection ~ 3488 4669
Wire Wire Line
	3488 4669 3488 4768
Connection ~ 4091 4669
Wire Wire Line
	4091 4669 3488 4669
Wire Wire Line
	4091 4170 3988 4170
Wire Wire Line
	4391 4370 4091 4370
Wire Wire Line
	4091 4170 4091 4369
Connection ~ 4091 4369
Wire Wire Line
	4091 4369 4091 4370
Wire Wire Line
	3987 4070 3988 4070
Wire Wire Line
	4391 4070 4789 4070
Wire Wire Line
	4789 4070 4789 4369
Connection ~ 4391 4070
Connection ~ 3988 4070
Wire Wire Line
	3988 4070 4391 4070
$Comp
L Device:Battery_Cell Vbatt
U 1 1 60871B1F
P 1692 3772
F 0 "Vbatt" H 1810 3868 50  0000 L CNN
F 1 "3V coin cell" H 1810 3777 50  0000 L CNN
F 2 "" V 1692 3832 50  0001 C CNN
F 3 "~" V 1692 3832 50  0001 C CNN
	1    1692 3772
	1    0    0    -1  
$EndComp
Wire Wire Line
	3491 3571 3491 3570
Wire Wire Line
	3491 3471 2592 3471
Wire Wire Line
	2592 3471 2592 3570
Connection ~ 3491 3570
Wire Wire Line
	3491 3570 3491 3471
Connection ~ 2592 3570
Wire Wire Line
	2592 3570 2592 3571
Wire Wire Line
	2592 3471 1692 3471
Wire Wire Line
	1692 3471 1692 3572
Connection ~ 2592 3471
$Comp
L power:GND #PWR?
U 1 1 6087AC1F
P 2592 3870
F 0 "#PWR?" H 2592 3620 50  0001 C CNN
F 1 "GND" H 2597 3697 50  0000 C CNN
F 2 "" H 2592 3870 50  0001 C CNN
F 3 "" H 2592 3870 50  0001 C CNN
	1    2592 3870
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6087CB0A
P 1692 3872
F 0 "#PWR?" H 1692 3622 50  0001 C CNN
F 1 "GND" H 1697 3699 50  0000 C CNN
F 2 "" H 1692 3872 50  0001 C CNN
F 3 "" H 1692 3872 50  0001 C CNN
	1    1692 3872
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 6087ECC1
P 5701 1733
F 0 "#PWR?" H 5701 1583 50  0001 C CNN
F 1 "VCC" H 5716 1906 50  0000 C CNN
F 2 "" H 5701 1733 50  0001 C CNN
F 3 "" H 5701 1733 50  0001 C CNN
	1    5701 1733
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6087FD07
P 6692 1736
F 0 "#PWR?" H 6692 1486 50  0001 C CNN
F 1 "GND" H 6697 1563 50  0000 C CNN
F 2 "" H 6692 1736 50  0001 C CNN
F 3 "" H 6692 1736 50  0001 C CNN
	1    6692 1736
	1    0    0    -1  
$EndComp
Wire Wire Line
	6001 1734 6001 1733
Wire Wire Line
	6001 1670 6692 1670
Wire Wire Line
	6692 1670 6692 1736
Connection ~ 6001 1733
Wire Wire Line
	6001 1733 6001 1670
Connection ~ 4192 3770
Wire Wire Line
	4192 3770 4728 3770
Connection ~ 4491 3870
Wire Wire Line
	4491 3870 4824 3870
Wire Wire Line
	3491 3471 4192 3471
Wire Wire Line
	4192 3471 4192 3470
Connection ~ 3491 3471
Wire Wire Line
	4192 3471 4491 3471
Wire Wire Line
	4491 3471 4491 3570
Connection ~ 4192 3471
Wire Wire Line
	2891 5369 2893 5369
Wire Wire Line
	2993 5369 2993 5269
Wire Wire Line
	2993 5269 2991 5269
Connection ~ 2893 5369
Wire Wire Line
	2893 5369 2992 5369
Connection ~ 2992 5369
Wire Wire Line
	2992 5369 2993 5369
Wire Wire Line
	3291 5269 3291 5369
Wire Wire Line
	3291 5369 3292 5369
Connection ~ 3292 5369
Wire Wire Line
	3292 5369 3492 5369
$Comp
L power:+3.3V #PWR?
U 1 1 608A9E3F
P 3691 5369
F 0 "#PWR?" H 3691 5219 50  0001 C CNN
F 1 "+3.3V" H 3706 5542 50  0001 C CNN
F 2 "" H 3691 5369 50  0001 C CNN
F 3 "" H 3691 5369 50  0001 C CNN
	1    3691 5369
	0    1    1    0   
$EndComp
Wire Wire Line
	3492 5369 3691 5369
Connection ~ 3492 5369
Text Label 3800 5399 0    50   ~ 0
SW_IN
Wire Wire Line
	2494 5369 2493 5369
Wire Wire Line
	2291 5369 2291 5368
Connection ~ 2493 5369
Wire Wire Line
	2493 5369 2291 5369
Connection ~ 2291 5368
Wire Wire Line
	2291 5368 2291 5366
$Comp
L power:VCC #PWR?
U 1 1 608B1531
P 2291 5068
F 0 "#PWR?" H 2291 4918 50  0001 C CNN
F 1 "VCC" H 2306 5241 50  0000 C CNN
F 2 "" H 2291 5068 50  0001 C CNN
F 3 "" H 2291 5068 50  0001 C CNN
	1    2291 5068
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 2683 6451 2683
Wire Wire Line
	7094 2683 7094 2601
Connection ~ 6451 2683
Wire Wire Line
	6451 2683 7094 2683
Wire Wire Line
	6450 2283 6451 2283
Wire Wire Line
	7500 2283 7500 2701
Connection ~ 6451 2283
Wire Wire Line
	6451 2283 7500 2283
Wire Wire Line
	6449 4033 6451 4033
Wire Wire Line
	7101 4033 7101 2801
Wire Wire Line
	7101 2801 7801 2801
Connection ~ 6451 4033
Wire Wire Line
	6451 4033 7101 4033
Wire Wire Line
	6448 2483 6451 2483
Wire Wire Line
	7396 2483 7396 2901
Connection ~ 6451 2483
Wire Wire Line
	6451 2483 7396 2483
$Comp
L power:+3.3V #PWR?
U 1 1 608D6DF2
P 5251 2583
F 0 "#PWR?" H 5251 2433 50  0001 C CNN
F 1 "+3.3V" H 5266 2756 50  0001 C CNN
F 2 "" H 5251 2583 50  0001 C CNN
F 3 "" H 5251 2583 50  0001 C CNN
	1    5251 2583
	0    -1   -1   0   
$EndComp
Text Label 5146 2617 2    50   ~ 0
SCK_LCD
$Comp
L Final_Project_Schematic-rescue:Signal_In-power SCK_LCD
U 1 1 608E3577
P 7646 3001
F 0 "SCK_LCD" H 7236 3008 61  0000 L CNN
F 1 "Signal_In" H 7830 2964 61  0001 L CNN
F 2 "" H 7653 3090 61  0001 C CNN
F 3 "" H 7653 3090 61  0001 C CNN
	1    7646 3001
	1    0    0    -1  
$EndComp
Wire Wire Line
	6448 4483 6451 4483
Wire Wire Line
	7500 4483 7500 3101
Connection ~ 6451 4483
Wire Wire Line
	6451 4483 7500 4483
Wire Wire Line
	6692 1670 7602 1670
Wire Wire Line
	7602 1670 7602 2501
Connection ~ 6692 1670
$Comp
L power:VCC #PWR?
U 1 1 608EC862
P 7801 2300
F 0 "#PWR?" H 7801 2150 50  0001 C CNN
F 1 "VCC" H 7816 2473 50  0000 C CNN
F 2 "" H 7801 2300 50  0001 C CNN
F 3 "" H 7801 2300 50  0001 C CNN
	1    7801 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7801 2401 7801 2300
Wire Wire Line
	7801 2299 7800 2299
Connection ~ 7801 2300
Wire Wire Line
	7801 2300 7801 2299
Connection ~ 7801 2501
Wire Wire Line
	7801 2501 7802 2501
Wire Wire Line
	7602 2501 7801 2501
Connection ~ 7801 3101
Wire Wire Line
	7801 3101 7804 3101
Wire Wire Line
	7500 3101 7801 3101
Connection ~ 7801 2901
Wire Wire Line
	7801 2901 7803 2901
Wire Wire Line
	7396 2901 7801 2901
Connection ~ 7801 2701
Wire Wire Line
	7801 2701 7804 2701
Wire Wire Line
	7500 2701 7801 2701
Connection ~ 7801 2601
Wire Wire Line
	7801 2601 7802 2601
Wire Wire Line
	7094 2601 7801 2601
$Comp
L Connector:Conn_01x08_Female J1
U 1 1 608C63EB
P 8001 2701
F 0 "J1" H 7869 2054 50  0000 L CNN
F 1 "LCD connector" H 7798 2173 50  0000 L CNN
F 2 "" H 8001 2701 50  0001 C CNN
F 3 "~" H 8001 2701 50  0001 C CNN
	1    8001 2701
	1    0    0    -1  
$EndComp
Text Notes 8027 2435 0    50   ~ 0
Vcc
Text Notes 8023 2544 0    50   ~ 0
GND
Text Notes 8022 2641 0    50   ~ 0
CS
Text Notes 8021 2737 0    50   ~ 0
Reset\n
Text Notes 8024 2838 0    50   ~ 0
DC
Text Notes 8020 2940 0    50   ~ 0
MOSI
Text Notes 8024 3037 0    50   ~ 0
SCK
Text Notes 8027 3139 0    50   ~ 0
LED\n
Wire Notes Line
	7960 2296 7960 3170
Wire Notes Line
	7960 3170 8371 3170
Wire Notes Line
	8371 2256 7960 2256
Wire Notes Line
	7960 2256 7960 2294
Wire Notes Line
	8371 2256 8371 3170
$EndSCHEMATC
