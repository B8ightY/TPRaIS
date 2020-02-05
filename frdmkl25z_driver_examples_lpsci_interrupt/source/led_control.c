/*
 * led_control.c
 *
 *  Created on: 1. 2. 2020
 *      Author: Erik
 */

/**
 * @file    led_control.c
 * @brief   Subor obsahuje funkcie na riadenie lediek
 * @details Subor obsahuje funkcie na riadenie vvsetkych lediek
 * 			ci uz na jednotlivych poschodiach alebo vo vytahu
 */

#include <led_control.h>

/***************************************************************************//**
 * Funkcia na vypnutie ledky/lediek prisluchajuc poschodiu, na ktorom vytah zastavil
 ******************************************************************************/
void turnOfLed(void) {
	switch(lastPosition) {
	case LIMIT_SWITCH_0:
		led_P(false, NULL);
		break;
	case LIMIT_SWITCH_1:
		led_1(false, NULL);
		break;
	case LIMIT_SWITCH_2:
		led_2(false, NULL);
		break;
	case LIMIT_SWITCH_3:
		led_3(false, NULL);
		break;
	case LIMIT_SWITCH_4:
		led_4(false, NULL);
		break;
	}
}

/***************************************************************************//**
 * Funkcia na vypnutie/zapnutie ledky P na poschodi/v kabine
 *
 * @param floorLedOn Urcuje, ci sa ma ledka na poschodi P zapnut alebo vypnut
 * @param cabinLedOn Urcuje, ci sa zmena stavu ledky na poschodi P tyka aj ledky v kabine
 ******************************************************************************/
void led_P(bool floorLedOn, bool cabinLedOn) {
	if(floorLedOn) {
		if(!floorLED[0]) {
			uint8_t led_10[] = {START_DATA, 0x10, MY_ADDR, 0x01, 0x01, 0x14};
			LPSCI_WriteBlocking(LPSCI, led_10, sizeof(led_10));

			floorLED[0] = true;
		}

		if(cabinLedOn && !cabinLED[0]) {
			uint8_t led_20[] = {START_DATA, 0x20, MY_ADDR, 0x01, 0x01, 0xCA};
			LPSCI_WriteBlocking(LPSCI, led_20, sizeof(led_20));

			cabinLED[0] = true;
		}
	} else {
		if(floorLED[0]) {
			uint8_t led_10[] = {START_DATA, 0x10, MY_ADDR, 0x01, 0x00, 0x4A};
			LPSCI_WriteBlocking(LPSCI, led_10, sizeof(led_10));

			floorLED[0] = false;
		}

		if(cabinLED[0]) {
			uint8_t led_20[] = {START_DATA, 0x20, MY_ADDR, 0x01, 0x00, 0x94};
			LPSCI_WriteBlocking(LPSCI, led_20, sizeof(led_20));

			cabinLED[0] = false;
		}
	}
}

/***************************************************************************//**
 * Funkcia na vypnutie/zapnutie ledky 1 na poschodi/v kabine
 *
 * @param floorLedOn Urcuje, ci sa ma ledka na poschodi 1 zapnut alebo vypnut
 * @param cabinLedOn Urcuje, ci sa zmena stavu ledky na poschodi 1 tyka aj ledky v kabine
 ******************************************************************************/
void led_1(bool floorLedOn, bool cabinLedOn) {
	if(floorLedOn) {
		if(!floorLED[1]) {
			uint8_t led_11[] = {START_DATA, 0x11, MY_ADDR, 0x01, 0x01, 0xBF};
			LPSCI_WriteBlocking(LPSCI, led_11, sizeof(led_11));

			floorLED[1] = true;
		}

		if(cabinLedOn && !cabinLED[1]) {
			uint8_t led_21[] = {START_DATA, 0x21, MY_ADDR, 0x01, 0x01, 0x61};
			LPSCI_WriteBlocking(LPSCI, led_21, sizeof(led_21));

			cabinLED[1] = true;
		}
	} else {
		if(floorLED[1]) {
			uint8_t led_11[] = {START_DATA, 0x11, MY_ADDR, 0x01, 0x00, 0xE1};
			LPSCI_WriteBlocking(LPSCI, led_11, sizeof(led_11));

			floorLED[1] = false;
		}

		if(cabinLED[1]) {
			uint8_t led_21[] = {START_DATA, 0x21, MY_ADDR, 0x01, 0x00, 0x3F};
			LPSCI_WriteBlocking(LPSCI, led_21, sizeof(led_21));

			cabinLED[1] = false;
		}
	}
}

/***************************************************************************//**
 * Funkcia na vypnutie/zapnutie ledky 2 na poschodi/v kabine
 *
 * @param floorLedOn Urcuje, ci sa ma ledka na poschodi 2 zapnut alebo vypnut
 * @param cabinLedOn Urcuje, ci sa zmena stavu ledky na poschodi 2 tyka aj ledky v kabine
 ******************************************************************************/
void led_2(bool floorLedOn, bool cabinLedOn) {
	if(floorLedOn) {
		if(!floorLED[2]) {
			uint8_t led_12[] = {START_DATA, 0x12, MY_ADDR, 0x01, 0x01, 0x5B};
			LPSCI_WriteBlocking(LPSCI, led_12, sizeof(led_12));

			floorLED[2] = true;
		}

		if(cabinLedOn && !cabinLED[2]) {
			uint8_t led_22[] = {START_DATA, 0x22, MY_ADDR, 0x01, 0x01, 0x85};
			LPSCI_WriteBlocking(LPSCI, led_22, sizeof(led_22));

			cabinLED[2] = true;
		}

	} else {
		if(floorLED[2]) {
			uint8_t led_12[] = {START_DATA, 0x12, MY_ADDR, 0x01, 0x00, 0x5};
			LPSCI_WriteBlocking(LPSCI, led_12, sizeof(led_12));

			floorLED[2] = false;
		}

		if(cabinLED[2]) {
			uint8_t led_22[] = {START_DATA, 0x22, MY_ADDR, 0x01, 0x00, 0xDB};
			LPSCI_WriteBlocking(LPSCI, led_22, sizeof(led_22));

			cabinLED[2] = false;
		}
	}
}

/***************************************************************************//**
 * Funkcia na vypnutie/zapnutie ledky 3 na poschodi/v kabine
 *
 * @param floorLedOn Urcuje, ci sa ma ledka na poschodi 3 zapnut alebo vypnut
 * @param cabinLedOn Urcuje, ci sa zmena stavu ledky na poschodi 3 tyka aj ledky v kabine
 ******************************************************************************/
void led_3(bool floorLedOn, bool cabinLedOn) {
	if(floorLedOn) {
		if(!floorLED[3]) {
			uint8_t led_13[] = {START_DATA, 0x13, MY_ADDR, 0x01, 0x01, 0xF0};
			LPSCI_WriteBlocking(LPSCI, led_13, sizeof(led_13));

			floorLED[3] = true;
		}

		if(cabinLedOn && !cabinLED[3]) {
			uint8_t led_23[] = {START_DATA, 0x23, MY_ADDR, 0x01, 0x01, 0x2E};
			LPSCI_WriteBlocking(LPSCI, led_23, sizeof(led_23));

			cabinLED[3] = true;
		}
	} else {
		if(floorLED[3]) {
			uint8_t led_13[] = {START_DATA, 0x13, MY_ADDR, 0x01, 0x00, 0xAE};
			LPSCI_WriteBlocking(LPSCI, led_13, sizeof(led_13));

			floorLED[3] = false;
		}

		if(cabinLED[3]) {
			uint8_t led_23[] = {START_DATA, 0x23, MY_ADDR, 0x01, 0x00, 0x70};
			LPSCI_WriteBlocking(LPSCI, led_23, sizeof(led_23));

			cabinLED[3] = false;
		}
	}
}

/***************************************************************************//**
 * Funkcia na vypnutie/zapnutie ledky 4 na poschodi/v kabine
 *
 * @param floorLedOn Urcuje, ci sa ma ledka na poschodi 4 zapnut alebo vypnut
 * @param cabinLedOn Urcuje, ci sa zmena stavu ledky na poschodi 4 tyka aj ledky v kabine
 ******************************************************************************/
void led_4(bool floorLedOn, bool cabinLedOn) {
	if(floorLedOn) {
		if(!floorLED[4]) {
			uint8_t led_14[] = {START_DATA, 0x14, MY_ADDR, 0x01, 0x01, 0x8A};
			LPSCI_WriteBlocking(LPSCI, led_14, sizeof(led_14));

			floorLED[4] = true;
		}

		if(cabinLedOn && !cabinLED[4]) {
			uint8_t led_24[] = {START_DATA, 0x24, MY_ADDR, 0x01, 0x01, 0x54};
			LPSCI_WriteBlocking(LPSCI, led_24, sizeof(led_24));

			cabinLED[4] = true;
		}
	} else {
		if(floorLED[4]) {
			uint8_t led_14[] = {START_DATA, 0x14, MY_ADDR, 0x01, 0x00, 0xD4};
			LPSCI_WriteBlocking(LPSCI, led_14, sizeof(led_14));

			floorLED[4] = false;
		}

		if(cabinLED[4]) {
			uint8_t led_24[] = {START_DATA, 0x24, MY_ADDR, 0x01, 0x00, 0xA};
			LPSCI_WriteBlocking(LPSCI, led_24, sizeof(led_24));

			cabinLED[4] = false;
		}
	}
}
