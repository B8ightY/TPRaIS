/*
 * movement.c
 *
 *  Created on: 1. 2. 2020
 *      Author: Erik
 */

/**
 * @file    movement.c
 * @brief   Subor obsahuje funkcie na riadenie pohybu vytahu
 * @details Subor obsahuje funkcie na riadenie vsetkych pohybov vytahu,
 * 			zistovanie jeho polohy a urcenie smeru pohybu
 */

#include <movement.h>

/***************************************************************************//**
 * Funkcia na zavretie dveri vytahu
 ******************************************************************************/
void closeDoor(void) {
	isDoingSomeTask = true;

	uint8_t msg[] = {START_DATA, DOOR, MY_ADDR, 0x01, 0x01, 0xD3};
	LPSCI_WriteBlocking(LPSCI, msg, sizeof(msg));
}

/***************************************************************************//**
 * Funkcia na otvorenie dveri vytahu
 ******************************************************************************/
void openDoor(void) {
	uint8_t msg[] = {START_DATA, DOOR, MY_ADDR, 0x01, 0x00, 0x8D};
	LPSCI_WriteBlocking(LPSCI, msg, sizeof(msg));
}

/***************************************************************************//**
 * Funkcia na pohyb vytahu smerom nahor
 ******************************************************************************/
void moveUp(void) {
	goingUp = true;
	showDirection();

	uint8_t move_up[] = {START_DATA, MOTOR, MY_ADDR, 0x05, 0x02, 0x64, 0x00, 0x00, 0x00, 0x64};
	LPSCI_WriteBlocking(LPSCI, move_up, sizeof(move_up));
}

/***************************************************************************//**
 * Funkcia na pohyb vytahu smerom nadol
 ******************************************************************************/
void moveDown(void) {
	goingDown = true;
	showDirection();

	uint8_t move_down[] = {START_DATA, MOTOR, MY_ADDR, 0x05, 0x02, 0x9C, 0xFF, 0xFF, 0xFF, 0x6F};
	LPSCI_WriteBlocking(LPSCI, move_down, sizeof(move_down));
}

/***************************************************************************//**
 * Funkcia na zastavenie motoru vytahu
 ******************************************************************************/
void stop(void) {
	uint8_t msg[] = {START_DATA, MOTOR, MY_ADDR, 0x01, 0x01, 0x78};
	LPSCI_WriteBlocking(LPSCI, msg, sizeof(msg));
}

/***************************************************************************//**
 * Funkcia na ziskanie cisla poschodia kabiny
 *
 * @return Cislo poschodia
 ******************************************************************************/
uint8_t getPosition(void) {
	switch(lastPosition) {
	case LIMIT_SWITCH_0:
		return 0;
	case LIMIT_SWITCH_1:
		return 1;
	case LIMIT_SWITCH_2:
		return 2;
	case LIMIT_SWITCH_3:
		return 3;
	case LIMIT_SWITCH_4:
		return 4;
	}

	return 5;
}

/***************************************************************************//**
 * Funkcia na zobrazenie smeru kabiny a cislo poschodia, na ktorom sa nachadza.
 * Ak sa vytah inicializuje, zobrazi sa namiesto cisla poschodia "Init"
 ******************************************************************************/
void showDirection(void) {
	const uint8_t floor[6] = {0x50, 0x31, 0x32, 0x33, 0x34, 0x00};
	uint8_t dir;

	if(!init) {
		if(goingDown) dir = 0x02;
		else if(goingUp) dir = 0x01;
		else { dir = 0x00; isDoingSomeTask = false; }

		uint8_t crcData[] = {0x30, MY_ADDR, dir, floor[getPosition()]};
		uint8_t direction[] = {START_DATA, 0x30, MY_ADDR, 0x02, dir, floor[getPosition()], calculateCrc(crcData, sizeof(crcData))};
		LPSCI_WriteBlocking(LPSCI, direction, sizeof(direction));
	} else {
		uint8_t direction[] = {START_DATA, 0x30, MY_ADDR, 0x05, 0x02, 0x49, 0x6e, 0x69, 0x74, 0xC4};
		LPSCI_WriteBlocking(LPSCI, direction, sizeof(direction));
	}
}

/***************************************************************************//**
 * Funkcia urcujuca ktorym smerom sa vytah vyberie na zaklade aktualneho poschodia
 ******************************************************************************/
void choseWhereToMove(void) {
	switch(lastPosition) {
	case LIMIT_SWITCH_0:
		moveUp();
		break;
	case LIMIT_SWITCH_1:
		if(floorButton[0]) moveDown();
		else moveUp();
		break;
	case LIMIT_SWITCH_2:
		if(floorButton[1] || floorButton[0]) moveDown();
		else moveUp();
		break;
	case LIMIT_SWITCH_3:
		if(floorButton[4]) moveUp();
		else moveDown();
		break;
	case LIMIT_SWITCH_4:
		moveDown();
		break;
	}
}

/***************************************************************************//**
 * Funkcia na zistenie, ci uz je aktualne stlacene poschodie v poli poschodi
 * cakajucich na prichod kabiny
 *
 * @param buttonPressed Aktualne stlacene tlacidlo
 * @return Je v rade - nenulova hodnota, nie je v rade - nulova hodnota
 ******************************************************************************/
bool isFloorInQueue(uint8_t buttonPressed) {
	for(uint8_t i = 1; i < buttonQueueIndex + 1; i++) {
		if(buttonPressed == buttonQueue[i]) return true;
	}

	return false;
}

/***************************************************************************//**
 * Funkcia resetujuca priznaky aktualne stlaceneho tlacidla poschodia
 * a smeru vytahu po tom, co zastavi na urcenom poschodi
 ******************************************************************************/
void resetButtons(void) {
	for(uint8_t i = 0; i < sizeof(floorButton); i++) floorButton[i] = false;

	goingDown = false;
	goingUp = false;
}
