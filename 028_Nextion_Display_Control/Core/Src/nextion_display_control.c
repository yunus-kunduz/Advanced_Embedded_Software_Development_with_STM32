/*
 * nextion_display_control.c
 *
 *  Created on: Mar 9, 2026
 *      Author: theyu
 */

#include "nextion_display_control.h"

void Nextion_Init(Nextion_t *nextion, UART_Ex_t *uart)
{
	nextion->nextionUart		= uart;

	nextion->rxBufferIndex 		= 0;

	memset(nextion->nextionRxBuffer, 0, sizeof(nextion->nextionRxBuffer));
	memset(&nextion->touchEvent, 0, sizeof(nextion->touchEvent));
}

static bool Nextion_Is_Message_Complete(Nextion_t *nextion)
{
	if(nextion->rxBufferIndex < 7)
		return false;

	return (nextion->nextionRxBuffer[nextion->rxBufferIndex -1] == 0xFF &&
			nextion->nextionRxBuffer[nextion->rxBufferIndex -2] == 0xFF &&
			nextion->nextionRxBuffer[nextion->rxBufferIndex -3] == 0xFF);
}

void Nextion_Process(Nextion_t *nextion)
{
	uint8_t data = 0;

	while(UARTx_Get_Char(nextion->nextionUart, &data))
	{
		if(nextion->rxBufferIndex < NEXT_RX_BUFF_SIZE - 1)
		{
			nextion->nextionRxBuffer[nextion->rxBufferIndex++] = data;

			if(Nextion_Is_Message_Complete(nextion))
			{
				// Dokunmatik bir olay gerçekleşti (touch event) kontrolü yap
				nextion->touchEvent.eventCode       = nextion->nextionRxBuffer[0];
				nextion->touchEvent.pageID          = nextion->nextionRxBuffer[1];
				nextion->touchEvent.componentID     = nextion->nextionRxBuffer[2];
				nextion->touchEvent.eventType       = nextion->nextionRxBuffer[3];

				nextion->newData					= true;

				memset(nextion->nextionRxBuffer, 0, sizeof(nextion->nextionRxBuffer));
				nextion->rxBufferIndex = 0;
			}
		}
		else
		{
			// Overflow - > reset buffer
			memset(nextion->nextionRxBuffer, 0, sizeof(nextion->nextionRxBuffer));
			nextion->rxBufferIndex = 0;
		}
	}
}

void Nextion_Send_Value(Nextion_t *nextion, const char *component, int value)
{
	char buffer[64];
	snprintf(buffer, sizeof(buffer), "%s.val=%d", component, value);
	Nextion_Send_Command(nextion, buffer);
}

void Nextion_Send_String(Nextion_t *nextion, const char *component, const char *text)
{
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "%s.txt=\"%s\"", component, text);
	Nextion_Send_Command(nextion, buffer);
}

void Nextion_Send_Command(Nextion_t *nextion, const char *command)
{
	UARTx_Put_String(nextion->nextionUart, (char*)command);
	UARTx_Put_String(nextion->nextionUart, "\xFF\xFF\xFF");
}

