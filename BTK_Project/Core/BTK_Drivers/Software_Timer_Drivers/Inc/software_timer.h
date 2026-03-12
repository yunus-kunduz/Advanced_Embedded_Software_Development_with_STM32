/*
 * software_timer.h
 *
 *  Created on: Mar 9, 2026
 *      Author: theyu
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#include "stdbool.h"

typedef struct
{
	uint32_t startTime;
	uint32_t intervalTime;
	bool     activated;
}STimer_t;

// 1 - Timer Çevresel Birimini seç ve başlat
void Software_Timer_Init(TIM_HandleTypeDef *htim);
// 1 - Timer Set Et ve Başlat
void Software_Timer_Set_Time(STimer_t *sTimer, uint32_t intervalMs);
// 3 - Zamanı Al
uint32_t Software_Timer_Get_Time(void);
// 4 - Geçen zamanı kontrol et
bool Software_Timer_Check_Elapsed_Time(STimer_t *sTimer);
// 5 - Zamanlayıcıyı durdur
void Software_Timer_Disable(STimer_t *sTimer);

#endif /* INC_SOFTWARE_TIMER_H_ */
