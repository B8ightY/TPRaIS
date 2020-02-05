/*
 * cmd_processing.c
 *
 *  Created on: 1. 2. 2020
 *      Author: Erik
 */

/**
 * @file    cmd_processing.c
 * @brief   Subor obsahuje funkcie spracovavajuce prijate spravy
 * @details Subor obsahuje funkciu spracovavajucu prikazy vsetkych
 * 			prijatych sprav bez ohladu na ich typ a dalsie funkcie
 * 			potrebne pre spravny chod aplikacie
 */

#include <cmd_processing.h>

/***************************************************************************//**
 * Funkcia spracovavajuca prikazy vsetkych prijatych sprav bez ohladu na ich typ
 * na zaklade adresy odosielatela danej spravy. Dany prikaz moze vyvolat spatnu odpoved
 * alebo iba ulozenie stavu urciteho elementu vytahu v prislusnej premennej
 *
 * @param sender Adresa odosielatela
 * @param _data Prvy bajt dat prijatej spravy
 ******************************************************************************/
void executeCommand(uint8_t sender, uint8_t _data) {
	switch(sender) {
	case DOOR:
		if(!isCabinMoving) doorOpen = !doorOpen;
		if(isOnTheSameFloor) {
			isOnTheSameFloor = false;
			delay(550);
			openDoor();
		} else if(!doorOpen && preparedToMove && !init) {
			delay(350);
			choseWhereToMove();
		} else if(doorOpen) {
			delay(150);
			turnOfLed();
			showDirection();
		} else if(init) {
			led_P(true, false);
			floorButton[0] = true;
			delay(350);
			moveDown();
		}
		break;
	case MOTOR:
		if(stopMotor) {
			stopMotor = false;
			isCabinMoving = false;
			init = false;
			resetButtons();
			delay(550);
			openDoor();
		} else if(preparedToMove) {
			preparedToMove = false;
			isCabinMoving = true;
		}
		break;


	case LIMIT_SWITCH_0:
		if(_data == 0x01 && lastPosition != LIMIT_SWITCH_0) {
			if(floorButton[0]) {
				stopMotor = true;
				delay(35);
				stop();
			}
		}
		if(_data == 0x01) {
			lastPosition = LIMIT_SWITCH_0;
			if(!init) showDirection();
		}
		break;
	case LIMIT_SWITCH_1:
		if(_data == 0x01 && lastPosition != LIMIT_SWITCH_1) {
			if(!init) showDirection();
			if(floorButton[1]) {
				stopMotor = true;
				delay(35);
				stop();
			}
		}
		if(_data == 0x01) {
			lastPosition = LIMIT_SWITCH_1;
			if(!init) showDirection();
		}
		break;
	case LIMIT_SWITCH_2:
		if(_data == 0x01 && lastPosition != LIMIT_SWITCH_2) {
			if(!init) showDirection();
			if(floorButton[2]) {
				stopMotor = true;
				delay(35);
				stop();
			}
		}
		if(_data == 0x01) {
			lastPosition = LIMIT_SWITCH_2;
			if(!init) showDirection();
		}
		break;
	case LIMIT_SWITCH_3:
		if(_data == 0x01 && lastPosition != LIMIT_SWITCH_3) {
			if(!init) showDirection();
			if(floorButton[3]) {
				stopMotor = true;
				delay(35);
				stop();
			}
		}
		if(_data == 0x01) {
			lastPosition = LIMIT_SWITCH_3;
			if(!init) showDirection();
		}
		break;
	case LIMIT_SWITCH_4:
		if(_data == 0x01 && lastPosition != LIMIT_SWITCH_4) {
			if(!init) showDirection();
			if(floorButton[4]) {
				stopMotor = true;
				delay(35);
				stop();
			}
		}
		if(_data == 0x01) {
			lastPosition = LIMIT_SWITCH_4;
			if(!init) showDirection();
		}
		break;


	case BUTTON_P:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_P)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_P;
			led_P(true, false);
		} else if(!isDoingSomeTask) {
			floorButton[0] = true;
			led_P(true, false);
			if(lastPosition == LIMIT_SWITCH_0) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	case BUTTON_1:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_1)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_1;
			led_1(true, false);
		} else if(!isDoingSomeTask) {
			floorButton[1] = true;
			led_1(true, false);
			if(lastPosition == LIMIT_SWITCH_1) {
				isOnTheSameFloor = true;
			}
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	case BUTTON_2:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_2)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_2;
			led_2(true, false);
		} else if(!isDoingSomeTask) {
			floorButton[2] = true;
			led_2(true, false);
			if(lastPosition == LIMIT_SWITCH_2) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	case BUTTON_3:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_3)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_3;
			led_3(true, false);
		} else if(!isDoingSomeTask) {
			floorButton[3] = true;
			led_3(true, false);
			if(lastPosition == LIMIT_SWITCH_3) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	case BUTTON_4:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_4)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_4;
			led_4(true, false);
		} else if(!isDoingSomeTask) {
			floorButton[4] = true;
			led_4(true, false);
			if(lastPosition == LIMIT_SWITCH_4) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;


	case BUTTON_P_CABIN:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_P)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_P;
			led_P(true, true);
		} else if(!isDoingSomeTask) {
			floorButton[0] = true;
			led_P(true, true);
			if(lastPosition == LIMIT_SWITCH_0) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	case BUTTON_1_CABIN:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_1)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_1;
			led_1(true, true);
		} else if(!isDoingSomeTask) {
			floorButton[1] = true;
			led_1(true, true);
			if(lastPosition == LIMIT_SWITCH_1) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	case BUTTON_2_CABIN:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_2)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_2;
			led_2(true, true);
		} else if(!isDoingSomeTask) {
			floorButton[2] = true;
			led_2(true, true);
			if(lastPosition == LIMIT_SWITCH_2) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	case BUTTON_3_CABIN:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_3)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_3;
			led_3(true, true);
		} else if(!isDoingSomeTask) {
			floorButton[3] = true;
			led_3(true, true);
			if(lastPosition == LIMIT_SWITCH_3) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	case BUTTON_4_CABIN:
		if(isDoingSomeTask && !isFloorInQueue(BUTTON_4)) {
			buttonQueue[++buttonQueueIndex] = BUTTON_4;
			led_4(true, true);
		} else if(!isDoingSomeTask) {
			floorButton[4] = true;
			led_4(true, true);
			if(lastPosition == LIMIT_SWITCH_4) isOnTheSameFloor = true;
			else preparedToMove = true;
			if(doorOpen) closeDoor();
		}
		break;
	}
}

/***************************************************************************//**
 * Funkcia resetujuca premenne pouzivane pri prijimani sprav po uspesnom prijati
 ******************************************************************************/
void prepareForNewMsg(void) {
	dataIndex = 0;
	dataSize = 0;
	processData = false;
}

/***************************************************************************//**
 * Funkcia sposobujuca oneskorenie
 ******************************************************************************/
void delay(int millis) {
	for(long i = 0; i < millis * 10000; i++) __asm("nop");
}
