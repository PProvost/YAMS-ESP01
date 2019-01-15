EESchema Schematic File Version 4
LIBS:YAMS - Yet Another Motion Sensor-cache
EELAYER 26 0
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
L sensors:PIR_Motion_Sensor PIR1
U 1 1 5C33B1C0
P 3900 2800
F 0 "PIR1" H 4278 3197 60  0000 L CNN
F 1 "PIR_Motion_Sensor" H 4278 3091 60  0000 L CNN
F 2 "Sensors:PIR_Motion_Sensor_Horiz" H 3900 3600 60  0001 C CNN
F 3 "" H 3900 3600 60  0000 C CNN
	1    3900 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5C33B26B
P 3500 2900
F 0 "#PWR01" H 3500 2650 50  0001 C CNN
F 1 "GND" H 3505 2727 50  0000 C CNN
F 2 "" H 3500 2900 50  0001 C CNN
F 3 "" H 3500 2900 50  0001 C CNN
	1    3500 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 5C33B337
P 3900 3300
F 0 "R1" H 3968 3346 50  0000 L CNN
F 1 "220R" H 3968 3255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3940 3290 50  0001 C CNN
F 3 "~" H 3900 3300 50  0001 C CNN
	1    3900 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5C33B3D4
P 3900 4000
F 0 "C1" H 4015 4046 50  0000 L CNN
F 1 "100nF" H 4015 3955 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_Tantal_D5.0mm_P2.50mm" H 3938 3850 50  0001 C CNN
F 3 "~" H 3900 4000 50  0001 C CNN
	1    3900 4000
	1    0    0    -1  
$EndComp
$Comp
L ESP8266:ESP-01v090 U1
U 1 1 5C33B45C
P 6550 3300
F 0 "U1" H 6550 3815 50  0000 C CNN
F 1 "ESP-01v090" H 6550 3724 50  0000 C CNN
F 2 "ESP8266:ESP-01" H 6550 3300 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 6550 3300 50  0001 C CNN
	1    6550 3300
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 5C33B4F7
P 4300 2900
F 0 "#PWR04" H 4300 2750 50  0001 C CNN
F 1 "+3V3" H 4315 3073 50  0000 C CNN
F 2 "" H 4300 2900 50  0001 C CNN
F 3 "" H 4300 2900 50  0001 C CNN
	1    4300 2900
	1    0    0    1   
$EndComp
Wire Wire Line
	3900 2800 3900 3150
Wire Wire Line
	3900 3450 3900 3700
Wire Wire Line
	5600 3250 4750 3250
Wire Wire Line
	4750 3250 4750 3700
Wire Wire Line
	4750 3700 3900 3700
Connection ~ 3900 3700
Wire Wire Line
	3900 3700 3900 3850
$Comp
L power:GND #PWR02
U 1 1 5C33B567
P 3900 4450
F 0 "#PWR02" H 3900 4200 50  0001 C CNN
F 1 "GND" H 3905 4277 50  0000 C CNN
F 2 "" H 3900 4450 50  0001 C CNN
F 3 "" H 3900 4450 50  0001 C CNN
	1    3900 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4150 3900 4450
$Comp
L power:GND #PWR07
U 1 1 5C33B6C1
P 7700 3150
F 0 "#PWR07" H 7700 2900 50  0001 C CNN
F 1 "GND" H 7705 2977 50  0000 C CNN
F 2 "" H 7700 3150 50  0001 C CNN
F 3 "" H 7700 3150 50  0001 C CNN
	1    7700 3150
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR03
U 1 1 5C33B98F
P 5300 3450
F 0 "#PWR03" H 5300 3300 50  0001 C CNN
F 1 "+3V3" H 5315 3623 50  0000 C CNN
F 2 "" H 5300 3450 50  0001 C CNN
F 3 "" H 5300 3450 50  0001 C CNN
	1    5300 3450
	0    -1   1    0   
$EndComp
$Comp
L Regulator_Linear:MCP1700-3302E_TO92 U2
U 1 1 5C33BB3C
P 6650 1500
F 0 "U2" H 6650 1350 50  0000 C CNN
F 1 "MCP1700-3302E_TO92" H 6650 1259 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 6650 1300 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001826C.pdf" H 6650 1500 50  0001 C CNN
	1    6650 1500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5C33BE69
P 6350 1800
F 0 "#PWR06" H 6350 1550 50  0001 C CNN
F 1 "GND" H 6355 1627 50  0000 C CNN
F 2 "" H 6350 1800 50  0001 C CNN
F 3 "" H 6350 1800 50  0001 C CNN
	1    6350 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1800 7300 1800
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5C33E231
P 8200 1700
F 0 "J1" H 8350 1600 50  0000 C CNN
F 1 "Power" H 8400 1700 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 8200 1700 50  0001 C CNN
F 3 "~" H 8200 1700 50  0001 C CNN
	1    8200 1700
	1    0    0    1   
$EndComp
Wire Wire Line
	6950 1500 7300 1500
$Comp
L Device:CP1 C3
U 1 1 5C33EB16
P 7300 1650
F 0 "C3" H 7415 1696 50  0000 L CNN
F 1 "1uF" H 7415 1605 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 7300 1650 50  0001 C CNN
F 3 "~" H 7300 1650 50  0001 C CNN
	1    7300 1650
	1    0    0    1   
$EndComp
$Comp
L Device:CP1 C2
U 1 1 5C33EB85
P 6000 1650
F 0 "C2" H 6115 1696 50  0000 L CNN
F 1 "1uF" H 6115 1605 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 6000 1650 50  0001 C CNN
F 3 "~" H 6000 1650 50  0001 C CNN
	1    6000 1650
	1    0    0    1   
$EndComp
Wire Wire Line
	6650 1800 6350 1800
Connection ~ 6650 1800
Wire Wire Line
	6350 1500 6000 1500
Connection ~ 6350 1800
Wire Wire Line
	6350 1800 6000 1800
$Comp
L power:+3V3 #PWR05
U 1 1 5C33F437
P 6000 1500
F 0 "#PWR05" H 6000 1350 50  0001 C CNN
F 1 "+3V3" H 6015 1673 50  0000 C CNN
F 2 "" H 6000 1500 50  0001 C CNN
F 3 "" H 6000 1500 50  0001 C CNN
	1    6000 1500
	1    0    0    -1  
$EndComp
Connection ~ 6000 1500
Wire Wire Line
	7300 1500 8000 1500
Wire Wire Line
	8000 1500 8000 1600
Connection ~ 7300 1500
Wire Wire Line
	7300 1800 8000 1800
Wire Wire Line
	8000 1800 8000 1700
Connection ~ 7300 1800
Wire Wire Line
	3500 2900 3800 2900
Wire Wire Line
	3800 2900 3800 2800
Wire Wire Line
	4300 2900 4000 2900
Wire Wire Line
	4000 2900 4000 2800
Wire Wire Line
	5300 3450 5600 3450
Wire Wire Line
	7500 3150 7700 3150
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5C342840
P 9150 2450
F 0 "J2" H 9230 2492 50  0000 L CNN
F 1 "TTL-Serial" H 9230 2401 50  0000 L CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x03_P2.00mm_Vertical" H 9150 2450 50  0001 C CNN
F 3 "~" H 9150 2450 50  0001 C CNN
	1    9150 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5C3430D9
P 8700 2350
F 0 "#PWR08" H 8700 2100 50  0001 C CNN
F 1 "GND" V 8705 2222 50  0000 R CNN
F 2 "" H 8700 2350 50  0001 C CNN
F 3 "" H 8700 2350 50  0001 C CNN
	1    8700 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	5600 2450 5600 3150
Wire Wire Line
	8950 2550 8950 3450
Wire Wire Line
	8950 2350 8700 2350
Wire Wire Line
	7500 3450 8950 3450
Wire Wire Line
	5600 2450 8950 2450
$Comp
L Device:R_US R2
U 1 1 5C352348
P 8050 3350
F 0 "R2" H 8118 3396 50  0000 L CNN
F 1 "3K3" H 8118 3305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8090 3340 50  0001 C CNN
F 3 "~" H 8050 3350 50  0001 C CNN
	1    8050 3350
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR09
U 1 1 5C352580
P 8350 3350
F 0 "#PWR09" H 8350 3200 50  0001 C CNN
F 1 "+3V3" H 8365 3523 50  0000 C CNN
F 2 "" H 8350 3350 50  0001 C CNN
F 3 "" H 8350 3350 50  0001 C CNN
	1    8350 3350
	0    1    -1   0   
$EndComp
Wire Wire Line
	7500 3350 7900 3350
Wire Wire Line
	8200 3350 8350 3350
$EndSCHEMATC