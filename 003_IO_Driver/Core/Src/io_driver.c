/*
 * io_driver.c
 *
 *  Created on: Feb 13, 2026
 *      Author: theyu
 */


#include "io_driver.h"


void IO_Initialization(IO_Info_t *ioInfo)
{
	/************************Input Initialization************************/
	ioInfo->inputsInfo.userButton.GPIOx          = USER_BUTTON_GPIO_Port;   // Port Bilgisi Atama
	ioInfo->inputsInfo.userButton.GPIO_Pin       = USER_BUTTON_Pin;         // Pin Bilgisi Atama
	ioInfo->inputsInfo.userButton.numOfInput     = 0;                       // Pin Numarası
	ioInfo->inputsInfo.userButton.currentState   = GPIO_PIN_RESET;          // O anki durum bilgisi
	ioInfo->inputsInfo.userButton.lastState      = GPIO_PIN_RESET;          // Son durum bilgisi
	ioInfo->inputsInfo.userButton.InputStatus    = Input_Status_Low;        // Karar verilmiş dijital giriş durumu low olarak ayarlama
	ioInfo->inputsInfo.userButton.currentTime    = 0;                       // Debounce algoritması başlangıç zamanı 0 olarak ayarlama
	ioInfo->inputsInfo.userButton.debounceTime   = DEBOUNCE_TIME;           // Debounce süresi ayarlama

	/************************Input Initialization************************/
	ioInfo->outputsInfo.ledGreen.GPIOx           = LED_GREEN_GPIO_Port;
	ioInfo->outputsInfo.ledGreen.GPIO_Pin        = LED_GREEN_Pin;
	ioInfo->outputsInfo.ledGreen.pinState        = GPIO_PIN_RESET;

	ioInfo->outputsInfo.ledOrange.GPIOx           = LED_ORANGE_GPIO_Port;
	ioInfo->outputsInfo.ledOrange.GPIO_Pin        = LED_ORANGE_Pin;
	ioInfo->outputsInfo.ledOrange.pinState        = GPIO_PIN_RESET;

	ioInfo->outputsInfo.ledRed.GPIOx           = LED_RED_GPIO_Port;
	ioInfo->outputsInfo.ledRed.GPIO_Pin        = LED_RED_Pin;
	ioInfo->outputsInfo.ledRed.pinState        = GPIO_PIN_RESET;

	ioInfo->outputsInfo.ledBlue.GPIOx           = LED_BLUE_GPIO_Port;
	ioInfo->outputsInfo.ledBlue.GPIO_Pin        = LED_BLUE_Pin;
	ioInfo->outputsInfo.ledBlue.pinState        = GPIO_PIN_RESET;
}



void IO_Status_Control(IO_Info_t *ioInfo)
{
	IO_Output_Control(&ioInfo->outputsInfo.ledGreen);
	IO_Output_Control(&ioInfo->outputsInfo.ledOrange);
	IO_Output_Control(&ioInfo->outputsInfo.ledRed);
	IO_Output_Control(&ioInfo->outputsInfo.ledBlue);

	IO_Input_Control_With_Debounce(&ioInfo->inputsInfo.userButton);
}



void IO_Input_Control_With_Debounce(Input_State_t *inputState)
{
	inputState->currentState = HAL_GPIO_ReadPin(inputState->GPIOx, inputState->GPIO_Pin);

	if(inputState->currentState == GPIO_PIN_SET)
	{
		if(inputState->InputStatus == Input_Status_Low)
		{
			if(inputState->currentState != inputState->lastState)
			{
				inputState->lastState   = inputState->currentState;
				inputState->currentTime = HAL_GetTick();
			}

			if((HAL_GetTick() - inputState->currentTime)  >= inputState->debounceTime)
			{
				inputState->InputStatus = Input_Status_Hıgh;
			}
		}
		else
		{
			//zaten high
		}
	}
	else
	{
		inputState->lastState   = inputState->currentState;
		inputState->InputStatus = Input_Status_Low;
	}

}


void IO_Output_Control(Output_State_t *outputState)
{
	HAL_GPIO_WritePin(outputState->GPIOx, outputState->GPIO_Pin, outputState->pinState);
}
