/*
 * crc_check.h
 *
 *  Created on: 1. 2. 2020
 *      Author: Erik
 */

/**
 * @file    crc_check.h
 * @brief   Subor obsahuje hlavicky funkcii suboru crc_check.c
 * @details Subor obsahuje hlavicky funkcii, deklaraciu pola na ukladanie sprav
 * 			a deklaraciu premennej urcujucu velkost dat v aktualne prijatej sprave
 */

#ifndef CRC_CHECK_H_
#define CRC_CHECK_H_

#include <defs.h>

/***************************************************************************//**
 * Deklaracie premennych
 ******************************************************************************/
extern volatile uint8_t data[256], dataSize;

/***************************************************************************//**
 * Hlavicky funkcii
 ******************************************************************************/
unsigned char calculateCrc(const unsigned char *_data, const unsigned int size);
void sendAck(uint8_t receiver, uint8_t sender);
bool checkCrc(void);

#endif /* CRC_CHECK_H_ */
