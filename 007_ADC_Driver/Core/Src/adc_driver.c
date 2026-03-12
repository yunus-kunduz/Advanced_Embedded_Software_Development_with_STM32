/*
 * adc_driver.c
 *
 *  Created on: Feb 14, 2026
 *      Author: theyu
 */

#include "adc_driver.h"

DMA_Transfer_Status_t globalDmaTransferStatus = DMA_Transfer_Not_Yet_Start;

void ADC_Initializaiton(ADC_Info_t *adcInfo, ADC_HandleTypeDef *hadc)
{
	adcInfo->hadc = hadc;
	adcInfo->adcErrorStatus = ADC_No_Error;

	for(int i = 0; i < NUM_OF_ADC_CHANNEL; i++)
	{
		adcInfo->adcConvertedData[i]       = 0;
		adcInfo->adcVoltageData[i]       = 0;
	}

	adcInfo->dmaTransferStatus = globalDmaTransferStatus;

	if(HAL_ADC_Start_DMA(hadc, (uint32_t*)adcInfo->adcConvertedData, NUM_OF_ADC_CHANNEL) != HAL_OK)
		adcInfo->adcErrorStatus = ADC_Init_Start_Error;

}

void ADC_DMA_Conversion(ADC_Info_t *adcInfo)
{
	adcInfo->dmaTransferStatus = globalDmaTransferStatus;

	if(adcInfo->dmaTransferStatus == DMA_Transfer_Completed)
	{
		globalDmaTransferStatus = DMA_Transfer_Not_Completed;

		for(int i = 0; i < NUM_OF_ADC_CHANNEL; i++)
		{
			adcInfo->adcVoltageData[i] = (__LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA,
					                                                   adcInfo->adcConvertedData[i],
																	   DIGITAL_SCALE)) / 1000.0;



		}

		adcInfo->VREF           = __LL_ADC_CALC_VREFANALOG_VOLTAGE(adcInfo->adcConvertedData[ADC_Channel_Vref], DIGITAL_SCALE);
		adcInfo->temperature    = __LL_ADC_CALC_TEMPERATURE(adcInfo->VREF, (adcInfo->adcConvertedData[ADC_Channel_Temp]), DIGITAL_SCALE);
		adcInfo->VBAT           = adcInfo->adcVoltageData[ADC_Channel_Vbat];
		adcInfo->pot1Percentage = MAP_Voltage_To_Percentage(adcInfo->adcVoltageData[ADC_Channel_2],
				                     0.0,
									 3.3,
									 0,
									 100);

	}
}


uint8_t MAP_Voltage_To_Percentage(float voltage, float inMin, float inMax, uint8_t outMin, uint8_t outMax)
{
	uint8_t percentage = 0;

	percentage = (voltage - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;

	return percentage;
}

/**
  * @brief  Regular conversion complete callback in non blocking mode
  * @param  hadc pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	// DMA Transfer Status completed
	globalDmaTransferStatus = DMA_Transfer_Completed;
}

/**
  * @brief  Regular conversion half DMA transfer callback in non blocking mode
  * @param  hadc pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	// DMA Transfer Status is not completed
	globalDmaTransferStatus = DMA_Transfer_Not_Completed;
}










