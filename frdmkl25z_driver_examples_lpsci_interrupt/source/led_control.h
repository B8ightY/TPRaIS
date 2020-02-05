/*
 * led_control.h
 *
 *  Created on: 1. 2. 2020
 *      Author: Erik
 */

/**
 * @file    led_control.h
 * @brief   Subor obsahuje hlavicky funkcii suboru led_control.c
 * @details Subor obsahuje hlavicky funkcii, deklaraciu premennej
 * 			urcujucu poslednu polohu vytahu a dve polia na ukladanie stavu lediek
 */

#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include <defs.h>

/***************************************************************************//**
 * Deklaracie premennych
 ******************************************************************************/
extern uint8_t lastPosition;
extern bool floorLED[5], cabinLED[5];

/***************************************************************************//**
 * Hlavicky funkcii
 ******************************************************************************/
void turnOfLed(void);
void led_P(bool floorLedOn, bool cabinLedOn);
void led_1(bool floorLedOn, bool cabinLedOn);
void led_2(bool floorLedOn, bool cabinLedOn);
void led_3(bool floorLedOn, bool cabinLedOn);
void led_4(bool floorLedOn, bool cabinLedOn);

#endif /* LED_CONTROL_H_ */
