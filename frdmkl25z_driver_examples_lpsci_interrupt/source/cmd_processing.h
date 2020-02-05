/*
 * cmd_processing.h
 *
 *  Created on: 1. 2. 2020
 *      Author: Erik
 */

/**
 * @file    cmd_processing.h
 * @brief   Subor obsahuje hlavicky funkcii suboru cmd_processing.c
 * @details Subor obsahuje hlavicky funkcii a deklaraciu premennych
 * 			pouzitych pri spracovavani prijatych sprav
 */

#ifndef CMD_PROCESSING_H_
#define CMD_PROCESSING_H_

#include <defs.h>
#include <led_control.h>
#include <movement.h>

/***************************************************************************//**
 * Deklaracie premennych
 ******************************************************************************/
extern volatile uint8_t dataIndex, dataSize;
extern volatile bool processData;

extern uint8_t lastPosition,  buttonQueue[6],  buttonQueueIndex;
extern bool isCabinMoving, isDoingSomeTask, doorOpen, init, isOnTheSameFloor, preparedToMove, stopMotor, floorButton[5];

/***************************************************************************//**
 * Hlavicky funkcii
 ******************************************************************************/
void executeCommand(uint8_t sender, uint8_t _data);
void prepareForNewMsg(void);
void delay(int millis);

#endif /* CMD_PROCESSING_H_ */
