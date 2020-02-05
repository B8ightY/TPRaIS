/*
 * vars.h
 *
 *  Created on: 4. 2. 2020
 *      Author: Erik
 */

/**
 * @file    vars.h
 * @brief   Subor obsahuje deklaracie globalnych premennych
 * @details Subor obsahuje deklaracie vsetkych globalnych premennych
 * 			potrebnych pre riadenie vytahu.
 */

#ifndef VARS_H_
#define VARS_H_

/***************************************************************************//**
 * Deklaracie premennych
 ******************************************************************************/
volatile uint8_t data[256], dataIndex = 0, dataSize = 0;
volatile bool processData = false;

uint8_t lastPosition,  buttonQueue[6],  buttonQueueIndex = 0;

bool floorButton[5] = {false, false, false, false, false};
bool floorLED[5] = {false, false, false, false, false};
bool cabinLED[5] = {false, false, false, false, false};

bool doorOpen = true, preparedToMove = false, stopMotor = false, isOnTheSameFloor = false;
bool init = true, isCabinMoving = false, goingUp = false, goingDown = false, isDoingSomeTask = false;

#endif /* VARS_H_ */
