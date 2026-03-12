/*
 * nextion_display_control.h
 *
 *  Created on: Mar 9, 2026
 *      Author: theyu
 */

#ifndef INC_NEXTION_DISPLAY_CONTROL_H_
#define INC_NEXTION_DISPLAY_CONTROL_H_

#include "uart_ex.h"
#include "stdint.h"
#include "stdbool.h"

#define NEXT_RX_BUFF_SIZE		64

typedef struct
{
	uint8_t eventCode;
	uint8_t pageID;
	uint8_t componentID;
	uint8_t eventType;
}Nextion_TouchEvent_t;

typedef struct
{
	UART_Ex_t			   *nextionUart;

	Nextion_TouchEvent_t   touchEvent;

	uint8_t				   nextionRxBuffer[NEXT_RX_BUFF_SIZE];
	uint8_t 			   rxBufferIndex;

	bool				   newData;
}Nextion_t;

void Nextion_Init(Nextion_t *nextion, UART_Ex_t *uart);
void Nextion_Process(Nextion_t *nextion);
// Nextion_TouchEvent_t *Nextion_Get_Touch_Event(void);

void Nextion_Send_Value(Nextion_t *nextion, const char *component, int value);
void Nextion_Send_String(Nextion_t *nextion, const char *component, const char *text);
void Nextion_Send_Command(Nextion_t *nextion, const char *command);

// va0.val=22
// txt1.txt="Merhaba"

#endif /* INC_NEXTION_DISPLAY_CONTROL_H_ */
