/*
 * software_timer.c
 *
 *  Created on: Mar 9, 2026
 *      Author: theyu
 */

#include "software_timer.h"

uint32_t msTick = 0;

// 1 - Timer Çevresel Birimini seç ve başlat
void Software_Timer_Init(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Start_IT(htim);
}

// 1 - Timer Set Et ve Başlat
void Software_Timer_Set_Time(STimer_t *sTimer, uint32_t intervalMs)
{
	sTimer->startTime       = Software_Timer_Get_Time();
	sTimer->intervalTime    = intervalMs;
	sTimer->activated       = true;
}

// 3 - Zamanı Al
uint32_t Software_Timer_Get_Time(void)
{
	return msTick;
}

// 4 - Geçen zamanı kontrol et
bool Software_Timer_Check_Elapsed_Time(STimer_t *sTimer)
{
	if(sTimer->activated)
	{
		uint32_t currentTick = Software_Timer_Get_Time();

		if(sTimer->startTime <= currentTick)
		{
			if(currentTick - sTimer->startTime >= sTimer->intervalTime)
			{
				Software_Timer_Disable(sTimer);

				return true;
			}
		}
		else
		{
			if((0xFFFFFFFF - (sTimer->startTime - currentTick)) >= sTimer->intervalTime)
			{
				Software_Timer_Disable(sTimer);

				return true;
			}
		}
	}

	return false;
}

// 5 - Zamanlayıcıyı durdur
void Software_Timer_Disable(STimer_t *sTimer)
{
	sTimer->activated       = false;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM10)
	{
		// 1ms kesme
		msTick++;
	}
}
