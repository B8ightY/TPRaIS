/**
 * @file    lpsci_interrupt.c
 * @brief   Hlavny spustaci subor
 * @details Subor obsahuje funkciu hlavnu funkciu main a spravcu preruseni
 */

#include <board.h>
#include <vars.h>
#include <clock_config.h>
#include <fsl_clock.h>
#include <fsl_common.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include <stdio.h>
#include <cmd_processing.h>
#include <led_control.h>
#include <movement.h>
#include <crc_check.h>
#include <defs.h>

/***************************************************************************//**
 * Funkcia na spravu preruseni. Ak je vyvolane prerusenie, prijme sa 1 bajt
 * a ulozi do pola. Ak je sprava cela nastavi sa flag processData na nenulovy.
 ******************************************************************************/
void LPSCI_IRQHandler(void) {
	if ((kLPSCI_RxDataRegFullFlag) & LPSCI_GetStatusFlags(LPSCI)) {
		data[dataIndex] = LPSCI_ReadByte(LPSCI);

		if(dataIndex == 0 && !((data[0] & 0xFE) == 0xA0)) return;

		if(dataIndex == 3) dataSize = data[dataIndex];
		if(dataIndex == (dataSize + 4)) processData = true;

		dataIndex++;
	}
}

/***************************************************************************//**
 * Funckia main inicializuje komunikiaciu cez LPSCI prostrednictvom preruseni.
 * Nasledne sa zatvoria dvere a na ack odpoved sa vytah inicializuje, co znamena jeho presun na prizemie.
 * V nekonecnej slucke sa kontroluje dostupnost prijatych dat, overi sa typ prijatej spravy s kontrolou crc
 * a vykona dany prikaz. V pripade, ze vytah nic nerobi a bolo stlacenych viac tlacidiel,
 * zacne ich postupne vykonavat.
 ******************************************************************************/
int main(void) {
	lpsci_config_t config;

	BOARD_InitPins();
	BOARD_BootClockRUN();
	CLOCK_SetLpsci0Clock(0x1U);

	LPSCI_GetDefaultConfig(&config);
	config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	config.enableTx = true;
	config.enableRx = true;

	LPSCI_Init(LPSCI, &config, LPSCI_CLK_FREQ);

	LPSCI_EnableInterrupts(LPSCI, kLPSCI_RxDataRegFullInterruptEnable);
	EnableIRQ(LPSCI_IRQn);

	closeDoor();

	while(1) {
		if(processData && data[0] == START_ACK) {
			if(checkCrc()) executeCommand(data[2], 0);
			prepareForNewMsg();
		} else if(processData && data[0] == START_DATA) {
			sendAck(data[1], data[2]);
			if(dataSize == 1) executeCommand(data[2], data[4]);
			else executeCommand(data[2], 0);

			prepareForNewMsg();
		} else if(!isDoingSomeTask && doorOpen && buttonQueueIndex > 0) {
			uint8_t nextFloor = buttonQueue[1];
			delay(550);
			for(uint8_t i = 1; i < buttonQueueIndex + 1; i++) buttonQueue[i] = buttonQueue[i + 1];
			buttonQueueIndex--;

			executeCommand(nextFloor, 0);
		}
	}
}
