/*
 * adc_driver.h
 *
 *  Created on: Feb 14, 2026
 *      Author: theyu
 */

#ifndef INC_ADC_DRIVER_H_
#define INC_ADC_DRIVER_H_

#include "main.h"

#define NUM_OF_ADC_CHANNEL       5         // ADC Kanal Sayısı

#define ADC_AVERAGE_COUNT        64

#define VDDA                     3300      // mv Cinsinden

#define DIGITAL_SCALE_6BITS      0x3F      // 63
#define DIGITAL_SCALE_8BITS      0xFF      // 255
#define DIGITAL_SCALE_10BITS     0x3FF     // 1023
#define DIGITAL_SCALE_12BITS     0xFFF     // 4095

#define DIGITAL_SCALE            DIGITAL_SCALE_12BITS

typedef enum
{
	ADC_Channel_2                = 0,
	ADC_Channel_3                = 1,
	ADC_Channel_Temp             = 2,
	ADC_Channel_Vref             = 3,
	ADC_Channel_Vbat             = 4
}ADC_Channel_Name;



typedef enum
{
	DMA_Transfer_Not_Completed   = 0,
	DMA_Transfer_Completed       = 1,
	DMA_Transfer_Not_Yet_Start   = 2
}DMA_Transfer_Status_t;

typedef enum
{
	ADC_No_Error                 = 0,
	ADC_Init_Start_Error         = 1
}ADC_Error_t;

typedef struct
{
	ADC_HandleTypeDef            *hadc;

	uint16_t                     adcConvertedData[NUM_OF_ADC_CHANNEL];
	uint32_t                     adcRawSum[NUM_OF_ADC_CHANNEL];
	uint16_t                     adcAverageData[NUM_OF_ADC_CHANNEL];
	uint8_t                      adcSampleCount;


	float                        adcVoltageData[NUM_OF_ADC_CHANNEL];

	float                        temperature;
	float                        realVDDA;
	float                        VBAT;

	uint8_t                      pot1Percentage;

	DMA_Transfer_Status_t        dmaTransferStatus;

	ADC_Error_t                  adcErrorStatus;

}ADC_Info_t;

void ADC_Initializaiton(ADC_Info_t  *adcInfo, ADC_HandleTypeDef *hadc);
void ADC_DMA_Conversion(ADC_Info_t  *adcInfo);

uint8_t MAP_Voltage_To_Percentage(float voltage, float inMin, float inMax, uint8_t outMin, uint8_t outMax);

#endif /* INC_ADC_DRIVER_H_ */






