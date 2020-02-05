/*
 * defs.h
 *
 *  Created on: 1. 2. 2020
 *      Author: Erik
 */

/**
 * @file    defs.h
 * @brief   Subor obsahuje definicie adries elementov vytahu
 * @details Subor obsahuje definicie adries jednotlivych elementov vytahu,
 * 			definicie potrebne pre komunikaciu a spolocne hlavickove subory pre viacere triedy
 */

#ifndef DEFS_H_
#define DEFS_H_

#include <fsl_lpsci.h>
#include <pin_mux.h>
#include <stdbool.h>

/***************************************************************************//**
 * Definicie pre komunikaciu
 ******************************************************************************/
#define LPSCI UART0
#define LPSCI_CLKSRC kCLOCK_CoreSysClk
#define LPSCI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define LPSCI_IRQn UART0_IRQn
#define LPSCI_IRQHandler UART0_IRQHandler

#define START_DATA 0xA0
#define START_ACK 0xA1
#define NO_DATA_TO_SEND 0x00

/***************************************************************************//**
 * Adresy elementov vytahu
 ******************************************************************************/
#define MY_ADDR 0x00
#define DOOR 0xF0
#define MOTOR 0xF1

#define BUTTON_P 0xC0
#define BUTTON_1 0xC1
#define BUTTON_2 0xC2
#define BUTTON_3 0xC3
#define BUTTON_4 0xC4

#define BUTTON_P_CABIN 0xB0
#define BUTTON_1_CABIN 0xB1
#define BUTTON_2_CABIN 0xB2
#define BUTTON_3_CABIN 0xB3
#define BUTTON_4_CABIN 0xB4

#define LIMIT_SWITCH_0 0xE0
#define LIMIT_SWITCH_1 0xE1
#define LIMIT_SWITCH_2 0xE2
#define LIMIT_SWITCH_3 0xE3
#define LIMIT_SWITCH_4 0xE4

#endif /* DEFS_H_ */
