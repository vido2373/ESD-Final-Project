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
P 5600 3300
F 0 "Op-Amp" H 5700 3200 50  0000 L CNN
F 1 "MCP6231-E/P" H 5600 3100 50  0000 L CNN
F 2 "" H 5600 3000 50  0001 C CNN
F 3 "" H 5600 3300 50  0001 C CNN
	1    5600 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 607D1EE4
P 5500 3600
F 0 "#PWR?" H 5500 3350 50  0001 C CNN
F 1 "GND" H 5505 3427 50  0000 C CNN
F 2 "" H 5500 3600 50  0001 C CNN
F 3 "" H 5500 3600 50  0001 C CNN
	1    5500 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D443D
P 4900 3650
F 0 "R" H 4750 3700 50  0000 L CNN
F 1 "47kΩ" H 4650 3600 50  0000 L CNN
F 2 "" V 4940 3640 50  0001 C CNN
F 3 "~" H 4900 3650 50  0001 C CNN
	1    4900 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D4437
P 4900 2950
F 0 "R" H 4750 3000 50  0000 L CNN
F 1 "47kΩ" H 4650 2900 50  0000 L CNN
F 2 "" V 4940 2940 50  0001 C CNN
F 3 "~" H 4900 2950 50  0001 C CNN
	1    4900 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607D5469
P 5500 2700
F 0 "R" V 5295 2700 50  0000 C CNN
F 1 "1MΩ" V 5386 2700 50  0000 C CNN
F 2 "" V 5540 2690 50  0001 C CNN
F 3 "~" H 5500 2700 50  0001 C CNN
	1    5500 2700
	0    1    1    0   
$EndComp
$Comp
L Device:C C
U 1 1 607D6315
P 4300 3400
F 0 "C" V 4050 3400 50  0000 C CNN
F 1 "1uF" V 4150 3400 50  0000 C CNN
F 2 "" H 4338 3250 50  0001 C CNN
F 3 "~" H 4300 3400 50  0001 C CNN
	1    4300 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R
U 1 1 607D2F84
P 4600 3400
F 0 "R" V 4400 3400 50  0000 C CNN
F 1 "1kΩ" V 4500 3400 50  0000 C CNN
F 2 "" V 4640 3390 50  0001 C CNN
F 3 "~" H 4600 3400 50  0001 C CNN
	1    4600 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R
U 1 1 607D2956
P 4000 3250
F 0 "R" H 4068 3296 50  0000 L CNN
F 1 "2kΩ" H 4068 3205 50  0000 L CNN
F 2 "" V 4040 3240 50  0001 C CNN
F 3 "~" H 4000 3250 50  0001 C CNN
	1    4000 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:Microphone MK
U 1 1 607D13BF
P 3850 3600
F 0 "MK" H 3600 3650 50  0000 L CNN
F 1 "CMA-4544PF-W" H 3100 3500 50  0000 L CNN
F 2 "" V 3850 3700 50  0001 C CNN
F 3 "~" V 3850 3700 50  0001 C CNN
	1    3850 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R
U 1 1 607EA2D2
P 5500 2400
F 0 "R" V 5295 2400 50  0000 C CNN
F 1 "1MΩ" V 5386 2400 50  0000 C CNN
F 2 "" V 5540 2390 50  0001 C CNN
F 3 "~" H 5500 2400 50  0001 C CNN
	1    5500 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 3400 4000 3400
Wire Wire Line
	4000 3400 4150 3400
Connection ~ 4000 3400
Wire Wire Line
	4750 3400 5050 3400
Wire Wire Line
	4900 3100 4900 3200
Wire Wire Line
	5900 3300 6150 3300
Wire Wire Line
	6150 3300 6150 2550
Wire Wire Line
	6150 2550 5650 2550
Wire Wire Line
	5650 2550 5650 2700
Wire Wire Line
	5650 2400 5650 2550
Connection ~ 5650 2550
Wire Wire Line
	5350 2700 5350 2550
Wire Wire Line
	5350 2550 5050 2550
Connection ~ 5350 2550
Wire Wire Line
	5350 2550 5350 2400
Connection ~ 5050 3400
Wire Wire Line
	5050 3400 5300 3400
$Comp
L power:GND #PWR?
U 1 1 607ECE2C
P 4900 3800
F 0 "#PWR?" H 4900 3550 50  0001 C CNN
F 1 "GND" H 4905 3627 50  0000 C CNN
F 2 "" H 4900 3800 50  0001 C CNN
F 3 "" H 4900 3800 50  0001 C CNN
	1    4900 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 607ED134
P 3850 3800
F 0 "#PWR?" H 3850 3550 50  0001 C CNN
F 1 "GND" H 3855 3627 50  0000 C CNN
F 2 "" H 3850 3800 50  0001 C CNN
F 3 "" H 3850 3800 50  0001 C CNN
	1    3850 3800
	1    0    0    -1  
$EndComp
Connection ~ 4900 3200
Wire Wire Line
	4900 3200 4900 3500
$Comp
L MSP432:MSP432P401R MCU
U 1 1 60818468
P 7150 3250
F 0 "MCU" H 7150 1327 50  0000 C CNN
F 1 "MSP432P401R" H 7150 1236 50  0000 C CNN
F 2 "" H 7150 4450 50  0001 C CNN
F 3 "" H 7150 4450 50  0001 C CNN
	1    7150 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3000 6300 3000
Wire Wire Line
	6300 3000 6300 3300
Wire Wire Line
	6300 3300 6150 3300
Connection ~ 6150 3300
Wire Wire Line
	6550 2500 6300 2500
Wire Wire Line
	6300 2500 6300 2800
Wire Wire Line
	6300 2800 5500 2800
Wire Wire Line
	5500 2800 5500 3000
Connection ~ 5500 2800
Wire Wire Line
	4900 2800 4000 2800
Wire Wire Line
	4000 2800 4000 3100
Connection ~ 4900 2800
Wire Wire Line
	4900 2800 5500 2800
Text Label 5500 2900 0    50   ~ 0
+3.3V
Text Label 4650 2800 0    50   ~ 0
+3.3V
Text Label 6300 3000 0    50   ~ 0
ADC_In
Text Label 5900 3300 0    50   ~ 0
V_Out
Text Label 4000 3100 0    50   ~ 0
+3.3V
Text Label 5100 3200 0    50   ~ 0
1.65V
Wire Wire Line
	4900 3200 5300 3200
Wire Wire Line
	5050 2550 5050 3400
Text Label 5150 3400 0    50   ~ 0
V_In
$EndSCHEMATC
