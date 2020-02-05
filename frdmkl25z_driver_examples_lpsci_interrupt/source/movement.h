/*
 * movement.h
 *
 *  Created on: 1. 2. 2020
 *      Author: Erik
 */

/**
 * @file    movement.h
 * @brief   Subor obsahuje hlavicky funkcii suboru movement.c
 * @details Subor obsahuje hlavicky funkcii, deklaraciu pouzitych
 * 			premennych a tiez poli
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <defs.h>
#include <crc_check.h>

/***************************************************************************//**
 * Deklaracie premennych a poli
 ******************************************************************************/
extern uint8_t lastPosition,  buttonQueue[6],  buttonQueueIndex;
extern bool floorButton[5], isDoingSomeTask, goingUp, goingDown, init;

/***************************************************************************//**
 * Hlavicky funkcii
 ******************************************************************************/
void closeDoor(void);
void openDoor(void);
void moveUp(void);
void moveDown(void);
void stop(void);
uint8_t getPosition(void);
void showDirection(void);
void choseWhereToMove(void);
bool isFloorInQueue(uint8_t buttonPressed);
void resetButtons(void);

#endif /* MOVEMENT_H_ */
