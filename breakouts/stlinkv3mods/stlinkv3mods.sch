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
L Connector:USB_C_Receptacle J1
U 1 1 5ED4A093
P 2750 3800
F 0 "J1" H 2857 5067 50  0000 C CNN
F 1 "USB_C_Receptacle" H 2857 4976 50  0000 C CNN
F 2 "Connector_USB:USB_C_Receptacle_Palconn_UTC16-G" H 2900 3800 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 2900 3800 50  0001 C CNN
	1    2750 3800
	1    0    0    -1  
$EndComp
$Comp
L stlinkv3mods:STLINK-V3MODS U2
U 1 1 5ED53270
P 6000 3950
F 0 "U2" H 6000 4925 50  0000 C CNN
F 1 "STLINK-V3MODS" H 6000 4834 50  0000 C CNN
F 2 "stlinkv3mods:STLINK-V3MODS" H 5950 5050 50  0001 C CNN
F 3 "" H 5950 5050 50  0001 C CNN
	1    6000 3950
	1    0    0    -1  
$EndComp
NoConn ~ 3350 3800
NoConn ~ 3350 3900
NoConn ~ 3350 4100
NoConn ~ 3350 4200
NoConn ~ 3350 4400
NoConn ~ 3350 4500
NoConn ~ 3350 4700
NoConn ~ 3350 4800
NoConn ~ 3350 5000
NoConn ~ 3350 5100
$Comp
L power:GND #PWR01
U 1 1 5ED5714E
P 2600 5400
F 0 "#PWR01" H 2600 5150 50  0001 C CNN
F 1 "GND" H 2605 5227 50  0000 C CNN
F 2 "" H 2600 5400 50  0001 C CNN
F 3 "" H 2600 5400 50  0001 C CNN
	1    2600 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5400 2600 5400
Connection ~ 2600 5400
Wire Wire Line
	2600 5400 2750 5400
$Comp
L Device:Polyfuse_Small F1
U 1 1 5ED57B63
P 3500 2800
F 0 "F1" V 3295 2800 50  0000 C CNN
F 1 "500mA" V 3386 2800 50  0000 C CNN
F 2 "Fuse:Fuse_1206_3216Metric" H 3550 2600 50  0001 L CNN
F 3 "~" H 3500 2800 50  0001 C CNN
	1    3500 2800
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5ED584D1
P 3700 2700
F 0 "#PWR05" H 3700 2550 50  0001 C CNN
F 1 "+5V" H 3715 2873 50  0000 C CNN
F 2 "" H 3700 2700 50  0001 C CNN
F 3 "" H 3700 2700 50  0001 C CNN
	1    3700 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 2800 3400 2800
Wire Wire Line
	3600 2800 3700 2800
Wire Wire Line
	3700 2800 3700 2700
$Comp
L Device:R_Small R1
U 1 1 5ED58E85
P 3500 3000
F 0 "R1" V 3450 2850 50  0000 C CNN
F 1 "5.1k" V 3450 3200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 3500 3000 50  0001 C CNN
F 3 "~" H 3500 3000 50  0001 C CNN
	1    3500 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5ED5957D
P 3500 3100
F 0 "R2" V 3450 2950 50  0000 C CNN
F 1 "5.1k" V 3450 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 3500 3100 50  0001 C CNN
F 3 "~" H 3500 3100 50  0001 C CNN
	1    3500 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 3000 3400 3000
Wire Wire Line
	3350 3100 3400 3100
$Comp
L power:GND #PWR06
U 1 1 5ED59C9B
P 3850 3100
F 0 "#PWR06" H 3850 2850 50  0001 C CNN
F 1 "GND" H 3855 2927 50  0000 C CNN
F 2 "" H 3850 3100 50  0001 C CNN
F 3 "" H 3850 3100 50  0001 C CNN
	1    3850 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 3100 3850 3100
Wire Wire Line
	3600 3000 3850 3000
Wire Wire Line
	3850 3000 3850 3100
Connection ~ 3850 3100
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5ED5B7E0
P 4250 3400
F 0 "J2" H 4330 3392 50  0000 L CNN
F 1 "USB" H 4330 3301 50  0000 L CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x04_P1.27mm_Vertical" H 4250 3400 50  0001 C CNN
F 3 "~" H 4250 3400 50  0001 C CNN
	1    4250 3400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5ED5D895
P 4000 3250
F 0 "#PWR07" H 4000 3100 50  0001 C CNN
F 1 "+5V" H 4015 3423 50  0000 C CNN
F 2 "" H 4000 3250 50  0001 C CNN
F 3 "" H 4000 3250 50  0001 C CNN
	1    4000 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3250 4000 3300
Wire Wire Line
	4000 3300 4050 3300
Wire Wire Line
	3350 3300 3350 3400
Wire Wire Line
	3350 3500 3350 3600
Wire Wire Line
	3350 3400 4050 3400
Connection ~ 3350 3400
Wire Wire Line
	3350 3500 4050 3500
Connection ~ 3350 3500
$Comp
L power:GND #PWR08
U 1 1 5ED5EB7B
P 4000 3650
F 0 "#PWR08" H 4000 3400 50  0001 C CNN
F 1 "GND" H 4005 3477 50  0000 C CNN
F 2 "" H 4000 3650 50  0001 C CNN
F 3 "" H 4000 3650 50  0001 C CNN
	1    4000 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3650 4000 3600
Wire Wire Line
	4000 3600 4050 3600
$Comp
L Regulator_Linear:AZ1117-3.3 U1
U 1 1 5ED5F8C2
P 3150 1850
F 0 "U1" H 3150 2092 50  0000 C CNN
F 1 "AZ1117CR2-3.3" H 3150 2001 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 3150 2100 50  0001 C CIN
F 3 "https://www.diodes.com/assets/Datasheets/AZ1117.pdf" H 3150 1850 50  0001 C CNN
	1    3150 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5ED608E1
P 3550 1950
F 0 "C2" H 3642 1996 50  0000 L CNN
F 1 "10u" H 3642 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3550 1950 50  0001 C CNN
F 3 "~" H 3550 1950 50  0001 C CNN
	1    3550 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5ED6139F
P 2750 1950
F 0 "C1" H 2658 1904 50  0000 R CNN
F 1 "10u" H 2658 1995 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2750 1950 50  0001 C CNN
F 3 "~" H 2750 1950 50  0001 C CNN
	1    2750 1950
	1    0    0    1   
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 5ED64626
P 2750 1800
F 0 "#PWR02" H 2750 1650 50  0001 C CNN
F 1 "+5V" H 2765 1973 50  0000 C CNN
F 2 "" H 2750 1800 50  0001 C CNN
F 3 "" H 2750 1800 50  0001 C CNN
	1    2750 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 5ED64E38
P 3550 1800
F 0 "#PWR04" H 3550 1650 50  0001 C CNN
F 1 "+3V3" H 3565 1973 50  0000 C CNN
F 2 "" H 3550 1800 50  0001 C CNN
F 3 "" H 3550 1800 50  0001 C CNN
	1    3550 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1800 2750 1850
Wire Wire Line
	2750 1850 2850 1850
Connection ~ 2750 1850
Wire Wire Line
	3550 1800 3550 1850
Wire Wire Line
	3550 1850 3450 1850
Connection ~ 3550 1850
$Comp
L power:GND #PWR03
U 1 1 5ED660F8
P 3150 2150
F 0 "#PWR03" H 3150 1900 50  0001 C CNN
F 1 "GND" H 3155 1977 50  0000 C CNN
F 2 "" H 3150 2150 50  0001 C CNN
F 3 "" H 3150 2150 50  0001 C CNN
	1    3150 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 2050 2750 2150
Wire Wire Line
	2750 2150 3150 2150
Wire Wire Line
	3550 2150 3550 2050
Connection ~ 3150 2150
Wire Wire Line
	3150 2150 3550 2150
$Comp
L power:GND #PWR09
U 1 1 5ED6DA52
P 4850 3900
F 0 "#PWR09" H 4850 3650 50  0001 C CNN
F 1 "GND" V 4855 3772 50  0000 R CNN
F 2 "" H 4850 3900 50  0001 C CNN
F 3 "" H 4850 3900 50  0001 C CNN
	1    4850 3900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5ED6E2F6
P 7200 3500
F 0 "#PWR010" H 7200 3250 50  0001 C CNN
F 1 "GND" V 7205 3372 50  0000 R CNN
F 2 "" H 7200 3500 50  0001 C CNN
F 3 "" H 7200 3500 50  0001 C CNN
	1    7200 3500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5ED6EAC4
P 7200 3700
F 0 "#PWR011" H 7200 3450 50  0001 C CNN
F 1 "GND" V 7205 3572 50  0000 R CNN
F 2 "" H 7200 3700 50  0001 C CNN
F 3 "" H 7200 3700 50  0001 C CNN
	1    7200 3700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5ED6ED50
P 7200 3800
F 0 "#PWR012" H 7200 3550 50  0001 C CNN
F 1 "GND" V 7205 3672 50  0000 R CNN
F 2 "" H 7200 3800 50  0001 C CNN
F 3 "" H 7200 3800 50  0001 C CNN
	1    7200 3800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5ED6EFBA
P 7200 4000
F 0 "#PWR013" H 7200 3750 50  0001 C CNN
F 1 "GND" V 7205 3872 50  0000 R CNN
F 2 "" H 7200 4000 50  0001 C CNN
F 3 "" H 7200 4000 50  0001 C CNN
	1    7200 4000
	0    -1   -1   0   
$EndComp
NoConn ~ 6800 4200
Wire Wire Line
	4850 3900 5200 3900
Wire Wire Line
	6800 3500 7200 3500
Wire Wire Line
	6800 3700 7200 3700
Wire Wire Line
	6800 3800 7200 3800
Wire Wire Line
	6800 4000 7200 4000
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J3
U 1 1 5ED71ADE
P 8350 2900
F 0 "J3" H 8400 3317 50  0000 C CNN
F 1 "JTAG" H 8400 3226 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_2x05_P1.27mm_Vertical_SMD" H 8350 2900 50  0001 C CNN
F 3 "~" H 8350 2900 50  0001 C CNN
	1    8350 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J4
U 1 1 5ED7296F
P 8350 3650
F 0 "J4" H 8400 4067 50  0000 C CNN
F 1 "SWD/VCP" H 8400 3976 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_2x05_P1.27mm_Vertical_SMD" H 8350 3650 50  0001 C CNN
F 3 "~" H 8350 3650 50  0001 C CNN
	1    8350 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J5
U 1 1 5ED73224
P 8350 4400
F 0 "J5" H 8400 4817 50  0000 C CNN
F 1 "SPI/I2C/CAN" H 8400 4726 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_2x05_P1.27mm_Vertical_SMD" H 8350 4400 50  0001 C CNN
F 3 "~" H 8350 4400 50  0001 C CNN
	1    8350 4400
	1    0    0    -1  
$EndComp
Text Label 6800 3400 0    50   ~ 0
T_VCC
Text Label 5200 3600 2    50   ~ 0
GNDDetect
Text Label 5200 3500 2    50   ~ 0
T_JTMS_SWDIO
Text Label 5200 4400 2    50   ~ 0
T_JCLK_SWCLK
Text Label 5200 3700 2    50   ~ 0
T_JTDO_SWO
Text Label 6800 3600 0    50   ~ 0
T_JTDI
Text Label 6800 3300 0    50   ~ 0
T_NRST
Text Label 8150 2700 2    50   ~ 0
T_VCC
Text Label 8150 3100 2    50   ~ 0
GNDDetect
NoConn ~ 8150 3000
$Comp
L power:GND #PWR016
U 1 1 5ED7D9A2
P 8150 2850
F 0 "#PWR016" H 8150 2600 50  0001 C CNN
F 1 "GND" V 8155 2722 50  0000 R CNN
F 2 "" H 8150 2850 50  0001 C CNN
F 3 "" H 8150 2850 50  0001 C CNN
	1    8150 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 2900 8150 2850
Connection ~ 8150 2850
Wire Wire Line
	8150 2850 8150 2800
Text Label 8650 2700 0    50   ~ 0
T_JTMS_SWDIO
Text Label 8650 2800 0    50   ~ 0
T_JCLK_SWCLK
Text Label 8650 2900 0    50   ~ 0
T_JTDO_SWO
Text Label 8650 3000 0    50   ~ 0
T_JTDI
Text Label 8650 3100 0    50   ~ 0
T_NRST
Wire Wire Line
	3550 1850 3900 1850
Text Label 4800 1750 0    50   ~ 0
T_VCC
Text Label 8150 3450 2    50   ~ 0
T_VCC
$Comp
L power:GND #PWR017
U 1 1 5ED85469
P 8150 3600
F 0 "#PWR017" H 8150 3350 50  0001 C CNN
F 1 "GND" V 8155 3472 50  0000 R CNN
F 2 "" H 8150 3600 50  0001 C CNN
F 3 "" H 8150 3600 50  0001 C CNN
	1    8150 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 3550 8150 3600
Connection ~ 8150 3600
Wire Wire Line
	8150 3600 8150 3650
Text Label 8150 3850 2    50   ~ 0
GNDDetect
Text Label 8650 3450 0    50   ~ 0
T_JTMS_SWDIO
Text Label 8650 3550 0    50   ~ 0
T_JCLK_SWCLK
Text Label 8650 3650 0    50   ~ 0
T_JTDO_SWO
Text Label 8650 3850 0    50   ~ 0
T_NRST
Text Label 5200 4300 2    50   ~ 0
T_VCP_TX_(RX)
Text Label 5200 4600 2    50   ~ 0
T_VCP_RX_(TX)
Text Label 8650 3750 0    50   ~ 0
T_VCP_TX_(RX)
Text Label 8150 3750 2    50   ~ 0
T_VCP_RX_(TX)
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J6
U 1 1 5ED8932A
P 8350 5150
F 0 "J6" H 8400 5567 50  0000 C CNN
F 1 "UART/GPIO" H 8400 5476 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_2x05_P1.27mm_Vertical_SMD" H 8350 5150 50  0001 C CNN
F 3 "~" H 8350 5150 50  0001 C CNN
	1    8350 5150
	1    0    0    -1  
$EndComp
Text Label 8150 4200 2    50   ~ 0
T_VCC
Text Label 5200 4500 2    50   ~ 0
B_SPI_NSS
Text Label 8650 4500 0    50   ~ 0
B_SPI_NSS
Text Label 5200 3800 2    50   ~ 0
B_SPI_CLK
Text Label 8650 4400 0    50   ~ 0
B_SPI_CLK
Text Label 6800 3900 0    50   ~ 0
B_SPI_MOSI
Text Label 6800 4100 0    50   ~ 0
B_SPI_MISO
Text Label 8650 4200 0    50   ~ 0
B_SPI_MOSI
Text Label 8650 4300 0    50   ~ 0
B_SPI_MISO
Text Label 6800 4700 0    50   ~ 0
B_I2C_SDA
Text Label 5200 4700 2    50   ~ 0
B_I2C_SCL
Text Label 8150 4500 2    50   ~ 0
B_I2C_SCL
Text Label 8150 4400 2    50   ~ 0
B_I2C_SDA
Text Label 5200 4000 2    50   ~ 0
B_CAN_RX
Text Label 5200 4100 2    50   ~ 0
B_CAN_TX
Text Label 8650 4600 0    50   ~ 0
B_CAN_RX
$Comp
L power:GND #PWR015
U 1 1 5EDB7384
P 7700 4950
F 0 "#PWR015" H 7700 4700 50  0001 C CNN
F 1 "GND" V 7705 4822 50  0000 R CNN
F 2 "" H 7700 4950 50  0001 C CNN
F 3 "" H 7700 4950 50  0001 C CNN
	1    7700 4950
	0    1    1    0   
$EndComp
Text Label 5200 3200 2    50   ~ 0
B_UART_RX
Text Label 5200 4200 2    50   ~ 0
B_UART_TX
Text Label 8150 5250 2    50   ~ 0
B_UART_TX
Text Label 8150 5350 2    50   ~ 0
B_UART_RX
Text Label 5200 3400 2    50   ~ 0
B_UART_RTS
Text Label 5200 3300 2    50   ~ 0
B_UART_CTS
Text Label 8150 5150 2    50   ~ 0
B_UART_RTS
Text Label 8150 5050 2    50   ~ 0
B_UART_CTS
Text Label 6800 3200 0    50   ~ 0
T_SW_DIR
Text Label 8650 4950 0    50   ~ 0
T_SW_DIR
Text Label 6800 4300 0    50   ~ 0
B_GPIO3
Text Label 6800 4400 0    50   ~ 0
B_GPIO2
Text Label 6800 4500 0    50   ~ 0
B_GPIO1
Text Label 6800 4600 0    50   ~ 0
B_GPIO0
Text Label 8650 5350 0    50   ~ 0
B_GPIO3
Text Label 8650 5250 0    50   ~ 0
B_GPIO2
Text Label 8650 5150 0    50   ~ 0
B_GPIO1
Text Label 8150 4600 2    50   ~ 0
B_CAN_TX
$Comp
L power:GND #PWR014
U 1 1 5ED9B3CB
P 7750 4300
F 0 "#PWR014" H 7750 4050 50  0001 C CNN
F 1 "GND" V 7755 4172 50  0000 R CNN
F 2 "" H 7750 4300 50  0001 C CNN
F 3 "" H 7750 4300 50  0001 C CNN
	1    7750 4300
	0    1    1    0   
$EndComp
Text Label 8650 5050 0    50   ~ 0
B_GPIO0
Wire Wire Line
	7750 4300 8150 4300
Wire Wire Line
	7700 4950 8150 4950
$Comp
L Switch:SW_DPDT_x2 SW1
U 1 1 5EDDB56B
P 4100 1850
F 0 "SW1" H 4100 2135 50  0000 C CNN
F 1 "SW_DPDT_x2" H 4100 2044 50  0000 C CNN
F 2 "Button_Switch_THT:SW_CuK_JS202011CQN_DPDT_Straight" H 4100 1850 50  0001 C CNN
F 3 "~" H 4100 1850 50  0001 C CNN
	1    4100 1850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DPDT_x2 SW1
U 2 1 5EDDC217
P 4600 1850
F 0 "SW1" H 4600 2135 50  0000 C CNN
F 1 "SW_DPDT_x2" H 4600 2044 50  0000 C CNN
F 2 "Button_Switch_THT:SW_CuK_JS202011CQN_DPDT_Straight" H 4600 1850 50  0001 C CNN
F 3 "~" H 4600 1850 50  0001 C CNN
	2    4600 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1750 4800 1750
Wire Wire Line
	4400 1850 3900 1850
Connection ~ 3900 1850
Wire Wire Line
	4300 1950 4800 1950
Wire Wire Line
	4300 1950 3900 1950
Wire Wire Line
	3900 1950 3900 1850
Connection ~ 4300 1950
$EndSCHEMATC
