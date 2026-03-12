/*
 * uart_ex.h
 *
 *  Created on: Feb 15, 2026
 *      Author: theyu
 */

#ifndef INC_UART_EX_H_
#define INC_UART_EX_H_

#include "main.h"
#include "circular_buffer.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"

typedef struct
{
	UART_HandleTypeDef *huart;
	Circular_Buffer_t *cbIn;
	Circular_Buffer_t *cbOut;
}UART_Ex_t;

void UARTx_Initialization(UART_Ex_t *uart, UART_HandleTypeDef *huart, Circular_Buffer_t *cbIn, Circular_Buffer_t *cbOut);
uint8_t UARTx_Get_Char(UART_Ex_t *uart, uint8_t *data);
void UARTx_Write_Char(UART_Ex_t *uart, char ch);
void UARTx_Put_String(UART_Ex_t *uart, char *str);
int UARTx_Printf(UART_Ex_t *uart, const char *format, ...);
bool UARTx_ReadLine(UART_Ex_t *uart, char *lineBuffer, uint16_t maxLen);

#endif /* INC_UART_EX_H_ */
