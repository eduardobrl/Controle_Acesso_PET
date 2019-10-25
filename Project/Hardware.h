#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "Types.h"
#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"

//PINS DEFINITIONS


//LEDS
#define LED1_OUT                P7_bit.no0
#define LED1_PU                 PU7_bit.no0
#define LED1_PM                 PM7_bit.no0


#define LED2_OUT                P7_bit.no1
#define LED2_PU                 PU7_bit.no1
#define LED2_PM                 PM7_bit.no1

#define LED3_OUT                P7_bit.no2
#define LED3_PU                 PU7_bit.no2
#define LED3_PM                 PM7_bit.no2

#define LED_PLACA               P7_bit.no7
#define LED_PLACA_PM            P7_bit.no7

//BOTOES


#define SW1_IN                  P5_bit.no4
#define SW1_PU                  PU5_bit.no4
#define SW1_PM                  PM5_bit.no4    

#define SW2_IN                  P5_bit.no3
#define SW2_PU                  PU5_bit.no3
#define SW2_PM                  PU5_bit.no3


#define SET_PIN(pin)            pin  =       0
#define CLR_PIN(pin)            pin  =       1
#define TOGGLE_PIN(pin)         pin  ^=      1

#define READ_PIN(pin)           pin


//*******************************************************
//                     
//*******************************************************

//PORT_MODE_OPTIONS
#define PORT_OUTPUT_MODE                (0u)
#define PORT_INPUT_MODE                 (1u)

//PORT_VALUE
#define PORT_OFF                        (0u)
#define PORT_ON                         (1u)

//PORT_PULL
#define PORT_PULL_NO                    (0u)
#define PORT_PULL_UP                    (1u)

//PORT_INPUT_MODE
#define PORT_NORMAL_INPUT               (0u)
#define PORT_TTL_INPUT                  (1u)

//PORT_OUTPUT_MODE
#define PORT_NORMAL_OUTPUT               (0u)
#define PORT_OPEN_DRAIN_OUTPUT           (1u)

//PORT_MODE_CONTROL
#define PORT_DIGITAL                    (0u)
#define PORT_ANALOG                     (1u)


#define RESERVED                        (0u)

/******************************************************/
//PORT0
#define P00_MODE                 (PORT_OUTPUT_MODE)
#define P00_PORT                 (PORT_OFF)
#define P00_PULL                 (PORT_PULL_NO)
#define P00_INPUT_MODE           (RESERVED)
#define P00_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P00_PORT_MODE            (PORT_DIGITAL)

#define P01_MODE                 (PORT_OUTPUT_MODE)
#define P01_PORT                 (PORT_OFF)
#define P01_PULL                 (PORT_PULL_NO)
#define P01_INPUT_MODE           (PORT_NORMAL_INPUT)
#define P01_OUTPUT_MODE          (RESERVED)
#define P01_PORT_MODE            (PORT_DIGITAL)

#define P02_MODE                 (PORT_OUTPUT_MODE)
#define P02_PORT                 (PORT_OFF)
#define P02_PULL                 (PORT_PULL_NO)
#define P02_INPUT_MODE           (RESERVED)
#define P02_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P02_PORT_MODE            (PORT_DIGITAL)

#define P03_MODE                 (PORT_OUTPUT_MODE)
#define P03_PORT                 (PORT_OFF)
#define P03_PULL                 (PORT_PULL_NO)
#define P03_INPUT_MODE           (PORT_NORMAL_INPUT)
#define P03_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P03_PORT_MODE            (PORT_DIGITAL)

#define P04_MODE                 (PORT_OUTPUT_MODE)
#define P04_PORT                 (PORT_OFF)
#define P04_PULL                 (PORT_PULL_NO)
#define P04_INPUT_MODE           (PORT_NORMAL_INPUT)
#define P04_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P04_PORT_MODE            (RESERVED)

#define P05_MODE                 (PORT_OUTPUT_MODE)
#define P05_PORT                 (PORT_OFF)
#define P05_PULL                 (PORT_PULL_NO)
#define P05_INPUT_MODE           (RESERVED)
#define P05_OUTPUT_MODE          (RESERVED)
#define P05_PORT_MODE            (RESERVED)

#define P06_MODE                 (PORT_OUTPUT_MODE)
#define P06_PORT                 (PORT_OFF)
#define P06_PULL                 (PORT_PULL_NO)
#define P06_INPUT_MODE           (RESERVED)
#define P06_OUTPUT_MODE          (RESERVED)
#define P06_PORT_MODE            (RESERVED)


#define P0_MODE                 (   0u << 7u | \
                                    P06_MODE << 6u | \
                                    P05_MODE << 5u | \
                                    P04_MODE << 4u | \
                                    P03_MODE << 3u | \
                                    P02_MODE << 2u | \
                                    P01_MODE << 1u | \
                                    P00_MODE << 0u )

#define P0_PORT                 (   0u << 7u | \
                                    P06_PORT << 6u | \
                                    P05_PORT << 5u | \
                                    P04_PORT << 4u | \
                                    P03_PORT << 3u | \
                                    P02_PORT << 2u | \
                                    P01_PORT << 1u | \
                                    P00_PORT << 0u )

#define P0_PULL                 (   0u << 7u | \
                                    P06_PULL << 6u | \
                                    P05_PULL << 5u | \
                                    P04_PULL << 4u | \
                                    P03_PULL << 3u | \
                                    P02_PULL << 2u | \
                                    P01_PULL << 1u | \
                                    P00_PULL << 0u )

#define P0_INPUT_MODE            (  0u << 7u | \
                                    P06_INPUT_MODE << 6u | \
                                    P05_INPUT_MODE << 5u | \
                                    P04_INPUT_MODE << 4u | \
                                    P03_INPUT_MODE << 3u | \
                                    P02_INPUT_MODE << 2u | \
                                    P01_INPUT_MODE << 1u | \
                                    P00_INPUT_MODE << 0u )

#define P0_OUTPUT_MODE                 (   0u << 7u | \
                                    P06_OUTPUT_MODE << 6u | \
                                    P05_OUTPUT_MODE << 5u | \
                                    P04_OUTPUT_MODE << 4u | \
                                    P03_OUTPUT_MODE << 3u | \
                                    P02_OUTPUT_MODE << 2u | \
                                    P01_OUTPUT_MODE << 1u | \
                                    P00_OUTPUT_MODE << 0u )

#define P0_PORT_MODE                 (   0u << 7u | \
                                    P06_PORT_MODE << 6u | \
                                    P05_PORT_MODE << 5u | \
                                    P04_PORT_MODE << 4u | \
                                    P03_PORT_MODE << 3u | \
                                    P02_PORT_MODE << 2u | \
                                    P01_PORT_MODE << 1u | \
                                    P00_PORT_MODE << 0u )

/******************************************************/
//PORT1
#define P10_MODE                 (PORT_OUTPUT_MODE)
#define P10_PORT                 (PORT_OFF)
#define P10_PULL                 (PORT_PULL_NO)
#define P10_INPUT_MODE           (RESERVED)
#define P10_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P10_PORT_MODE            (PORT_DIGITAL)

#define P11_MODE                 (PORT_INPUT_MODE)
#define P11_PORT                 (PORT_ON)
#define P11_PULL                 (PORT_PULL_NO)
#define P11_INPUT_MODE           (PORT_NORMAL_INPUT)
#define P11_OUTPUT_MODE          (RESERVED)
#define P11_PORT_MODE            (PORT_DIGITAL)

#define P12_MODE                 (PORT_OUTPUT_MODE)
#define P12_PORT                 (PORT_OFF)
#define P12_PULL                 (PORT_PULL_NO)
#define P12_INPUT_MODE           (RESERVED)
#define P12_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P12_PORT_MODE            (PORT_DIGITAL)

#define P13_MODE                 (PORT_OUTPUT_MODE)
#define P13_PORT                 (PORT_OFF)
#define P13_PULL                 (PORT_PULL_NO)
#define P13_INPUT_MODE           (PORT_NORMAL_INPUT)
#define P13_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P13_PORT_MODE            (PORT_DIGITAL)

#define P14_MODE                 (PORT_OUTPUT_MODE)
#define P14_PORT                 (PORT_OFF)
#define P14_PULL                 (PORT_PULL_NO)
#define P14_INPUT_MODE           (PORT_NORMAL_INPUT)
#define P14_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P14_PORT_MODE            (RESERVED)

#define P15_MODE                 (PORT_OUTPUT_MODE)
#define P15_PORT                 (PORT_OFF)
#define P15_PULL                 (PORT_PULL_NO)
#define P15_INPUT_MODE           (RESERVED)
#define P15_OUTPUT_MODE          (RESERVED)
#define P15_PORT_MODE            (RESERVED)

#define P16_MODE                 (PORT_OUTPUT_MODE)
#define P16_PORT                 (PORT_OFF)
#define P16_PULL                 (PORT_PULL_NO)
#define P16_INPUT_MODE           (RESERVED)
#define P16_OUTPUT_MODE          (RESERVED)
#define P16_PORT_MODE            (RESERVED)

#define P17_MODE                 (PORT_OUTPUT_MODE)
#define P17_PORT                 (PORT_OFF)
#define P17_PULL                 (PORT_PULL_NO)
#define P17_INPUT_MODE           (PORT_NORMAL_INPUT)
#define P17_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
#define P17_PORT_MODE            (PORT_DIGITAL)

#define P1_MODE                 (   P17_MODE << 7u | \
                                    P16_MODE << 6u | \
                                    P15_MODE << 5u | \
                                    P14_MODE << 4u | \
                                    P13_MODE << 3u | \
                                    P12_MODE << 2u | \
                                    P11_MODE << 1u | \
                                    P10_MODE << 0u )

#define P1_PORT                 (   P17_PORT << 7u | \
                                    P16_PORT << 6u | \
                                    P15_PORT << 5u | \
                                    P14_PORT << 4u | \
                                    P13_PORT << 3u | \
                                    P12_PORT << 2u | \
                                    P11_PORT << 1u | \
                                    P10_PORT << 0u )

#define P1_PULL                 (   P17_PULL << 7u | \
                                    P16_PULL << 6u | \
                                    P15_PULL << 5u | \
                                    P14_PULL << 4u | \
                                    P13_PULL << 3u | \
                                    P12_PULL << 2u | \
                                    P11_PULL << 1u | \
                                    P10_PULL << 0u )

#define P1_INPUT_MODE            (  P17_INPUT_MODE << 7u | \
                                    P16_INPUT_MODE << 6u | \
                                    P15_INPUT_MODE << 5u | \
                                    P14_INPUT_MODE << 4u | \
                                    P13_INPUT_MODE << 3u | \
                                    P12_INPUT_MODE << 2u | \
                                    P11_INPUT_MODE << 1u | \
                                    P10_INPUT_MODE << 0u )

#define P1_OUTPUT_MODE                 (   P17_OUTPUT_MODE << 7u | \
                                    P16_OUTPUT_MODE << 6u | \
                                    P15_OUTPUT_MODE << 5u | \
                                    P14_OUTPUT_MODE << 4u | \
                                    P13_OUTPUT_MODE << 3u | \
                                    P12_OUTPUT_MODE << 2u | \
                                    P11_OUTPUT_MODE << 1u | \
                                    P10_OUTPUT_MODE << 0u )

#define P1_PORT_MODE                 (   P17_PORT_MODE << 7u | \
                                    P16_PORT_MODE << 6u | \
                                    P15_PORT_MODE << 5u | \
                                    P14_PORT_MODE << 4u | \
                                    P13_PORT_MODE << 3u | \
                                    P12_PORT_MODE << 2u | \
                                    P11_PORT_MODE << 1u | \
                                    P10_PORT_MODE << 0u )

/******************************************************/
//PORT2
#define P20_MODE                 (PORT_OUTPUT_MODE)
#define P20_PORT                 (PORT_OFF)

#define P21_MODE                 (PORT_OUTPUT_MODE)
#define P21_PORT                 (PORT_OFF)

#define P22_MODE                 (PORT_OUTPUT_MODE)
#define P22_PORT                 (PORT_OFF)

#define P23_MODE                 (PORT_OUTPUT_MODE)
#define P23_PORT                 (PORT_OFF)

#define P24_MODE                 (PORT_OUTPUT_MODE)
#define P24_PORT                 (PORT_OFF)

#define P25_MODE                 (PORT_OUTPUT_MODE)
#define P25_PORT                 (PORT_OFF)

#define P26_MODE                 (PORT_OUTPUT_MODE)
#define P26_PORT                 (PORT_OFF)

#define P27_MODE                 (PORT_OUTPUT_MODE)
#define P27_PORT                 (PORT_OFF)

#define P2_MODE                 (   P27_MODE << 7u | \
                                    P26_MODE << 6u | \
                                    P25_MODE << 5u | \
                                    P24_MODE << 4u | \
                                    P23_MODE << 3u | \
                                    P22_MODE << 2u | \
                                    P21_MODE << 1u | \
                                    P20_MODE << 0u )

#define P2_PORT                 (   P27_PORT << 7u | \
                                    P26_PORT << 6u | \
                                    P25_PORT << 5u | \
                                    P24_PORT << 4u | \
                                    P23_PORT << 3u | \
                                    P22_PORT << 2u | \
                                    P21_PORT << 1u | \
                                    0 << 0u )

/******************************************************/
//PORT3
#define P30_MODE                 (PORT_OUTPUT_MODE)
#define P30_PORT                 (PORT_OFF)
#define P30_PULL                 (PORT_PULL_NO)

#define P31_MODE                 (PORT_OUTPUT_MODE)
#define P31_PORT                 (PORT_OFF)
#define P31_PULL                 (PORT_PULL_NO)

#define P3_MODE                 (   P31_MODE << 1u | \
                                    P30_MODE << 0u )

#define P3_PORT                 (   P31_PORT << 1u | \
                                    P30_MODE << 0u )

#define P3_PULL                 (   P31_PULL << 1u | \
                                    P30_MODE << 0u )


/******************************************************/
//PORT4
#define P40_MODE                 (PORT_OUTPUT_MODE)
#define P40_PORT                 (PORT_OFF)
#define P40_PULL                 (PORT_PULL_NO)

#define P41_MODE                 (PORT_OUTPUT_MODE)
#define P41_PORT                 (PORT_OFF)
#define P41_PULL                 (PORT_PULL_NO)

#define P42_MODE                 (PORT_OUTPUT_MODE)
#define P42_PORT                 (PORT_OFF)
#define P42_PULL                 (PORT_PULL_NO)

#define P43_MODE                 (PORT_OUTPUT_MODE)
#define P43_PORT                 (PORT_OFF)
#define P43_PULL                 (PORT_PULL_NO)

#define P4_MODE                 (   P43_MODE << 3u | \
                                    P42_MODE << 2u | \
                                    P41_MODE << 1u | \
                                    P40_MODE << 0u )

#define P4_PORT                 (   P43_PORT << 3u | \
                                    P42_PORT << 2u | \
                                    P41_PORT << 1u | \
                                    P40_MODE << 0u )

#define P4_PULL                 (   P43_PULL << 3u | \
                                    P42_PULL << 2u | \
                                    P41_PULL << 1u | \
                                    P40_MODE << 0u )


/******************************************************/
//PORT5
#define P50_MODE                 (PORT_OUTPUT_MODE)
#define P50_PORT                 (PORT_OFF)
#define P50_PULL                 (PORT_PULL_NO)
#define P50_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)


#define P51_MODE                 (PORT_OUTPUT_MODE)
#define P51_PORT                 (PORT_OFF)
#define P51_PULL                 (PORT_PULL_NO)

#define P52_MODE                 (PORT_OUTPUT_MODE)
#define P52_PORT                 (PORT_OFF)
#define P52_PULL                 (PORT_PULL_NO)

#define P53_MODE                 (PORT_OUTPUT_MODE)
#define P53_PORT                 (PORT_OFF)
#define P53_PULL                 (PORT_PULL_NO)

#define P54_MODE                 (PORT_OUTPUT_MODE)
#define P54_PORT                 (PORT_OFF)
#define P54_PULL                 (PORT_PULL_NO)

#define P55_MODE                 (PORT_OUTPUT_MODE)
#define P55_PORT                 (PORT_OFF)
#define P55_PULL                 (PORT_PULL_NO)
#define P55_INPUT_MODE           (PORT_NORMAL_INPUT)
#define P55_OUTPUT_MODE          (PORT_NORMAL_OUTPUT)
/******************************************************/
//PORT6
#define P40_MODE                 (PORT_OUTPUT_MODE)
#define P40_PORT                 (PORT_OFF)
#define P40_PULL                 (PORT_PULL_NO)

#define P41_MODE                 (PORT_OUTPUT_MODE)
#define P41_PORT                 (PORT_OFF)
#define P41_PULL                 (PORT_PULL_NO)

#define P42_MODE                 (PORT_OUTPUT_MODE)
#define P42_PORT                 (PORT_OFF)
#define P42_PULL                 (PORT_PULL_NO)

#define P43_MODE                 (PORT_OUTPUT_MODE)
#define P43_PORT                 (PORT_OFF)
#define P43_PULL                 (PORT_PULL_NO)

/******************************************************/
//PORT7
#define P70_MODE                 (PORT_INPUT_MODE)
#define P70_PORT                 (PORT_OFF)
#define P70_PULL                 (PORT_PULL_UP)

#define P71_MODE                 (PORT_INPUT_MODE)
#define P71_PORT                 (PORT_OFF)
#define P71_PULL                 (PORT_PULL_UP)
#define P71_OUTPUT_MODE          (0u)

#define P72_MODE                 (PORT_INPUT_MODE)
#define P72_PORT                 (PORT_OFF)
#define P72_PULL                 (PORT_PULL_UP)

#define P73_MODE                 (PORT_INPUT_MODE)
#define P73_PORT                 (PORT_OFF)
#define P73_PULL                 (PORT_PULL_UP)

#define P74_MODE                 (PORT_INPUT_MODE)
#define P74_PORT                 (PORT_OFF)
#define P74_PULL                 (PORT_PULL_UP)
#define P74_OUTPUT_MODE          (0u)

#define P75_MODE                 (PORT_INPUT_MODE)
#define P75_PORT                 (PORT_OFF)
#define P75_PULL                 (PORT_PULL_UP)

#define P76_MODE                 (PORT_INPUT_MODE)
#define P76_PORT                 (PORT_OFF)
#define P76_PULL                 (PORT_PULL_UP)

#define P77_MODE                 (PORT_INPUT_MODE)
#define P77_PORT                 (PORT_OFF)
#define P77_PULL                 (PORT_PULL_UP)

#define P7_MODE                 (   P77_MODE << 7u | \
                                    P76_MODE << 6u | \
                                    P75_MODE << 5u | \
                                    P74_MODE << 4u | \
                                    P73_MODE << 3u | \
                                    P72_MODE << 2u | \
                                    P71_MODE << 1u | \
                                    P70_MODE << 0u )

#define P7_PORT                 (   P77_PORT << 7u | \
                                    P76_PORT << 6u | \
                                    P75_PORT << 5u | \
                                    P74_PORT << 4u | \
                                    P73_PORT << 3u | \
                                    P72_PORT << 2u | \
                                    P71_PORT << 1u | \
                                    P70_PORT << 0u )

#define P7_PULL                 (   P77_PULL << 7u | \
                                    P76_PULL << 6u | \
                                    P75_PULL << 5u | \
                                    P74_PULL << 4u | \
                                    P73_PULL << 3u | \
                                    P72_PULL << 2u | \
                                    P71_PULL << 1u | \
                                    P70_PULL << 0u )



#endif