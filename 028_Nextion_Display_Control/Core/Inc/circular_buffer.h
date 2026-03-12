/*
 * circular_buffer.h
 *
 *  Created on: Feb 15, 2026
 *      Author: theyu
 */

#ifndef INC_CIRCULAR_BUFFER_H_
#define INC_CIRCULAR_BUFFER_H_

#include "stdbool.h"
#include "stdint.h"
#include "string.h"

#define CIRCULAR_BUFFER_SIZE        512

typedef struct
{
	uint8_t buffer[CIRCULAR_BUFFER_SIZE];
	uint16_t head;
	uint16_t tail;
}Circular_Buffer_t;


// Buffer Initialization
void Circular_Buffer_Init(Circular_Buffer_t *circularBuffer);

// is Buffer Empty? | is Buffer fully?
bool Circular_Buffer_is_Empty(Circular_Buffer_t *circularBuffer);
bool Circular_Buffer_is_Fully(Circular_Buffer_t *circularBuffer);

bool Circular_Buffer_Enqueue(Circular_Buffer_t *circularBuffer, uint8_t data);
bool Circular_Buffer_Dequeue(Circular_Buffer_t *circularBuffer, uint8_t *data);

uint8_t Circular_Buffer_Count(Circular_Buffer_t *circularBuffer);

#endif /* INC_CIRCULAR_BUFFER_H_ */
