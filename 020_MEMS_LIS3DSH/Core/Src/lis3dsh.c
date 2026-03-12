/*
 * lis3dsh.c
 *
 *  Created on: Feb 18, 2026
 *      Author: theyu
 */

#include "lis3dsh.h"
#include "stdbool.h"

static void LIS3DSH_CS_Enable(LIS3DSH_t *lis3dsh)
{
	HAL_GPIO_WritePin(lis3dsh->cs_port, lis3dsh->cs_pin, GPIO_PIN_RESET);
}

static void LIS3DSH_CS_Disable(LIS3DSH_t *lis3dsh)
{
	HAL_GPIO_WritePin(lis3dsh->cs_port, lis3dsh->cs_pin, GPIO_PIN_SET);
}

bool LIS3DSH_Initialization(LIS3DSH_t *lis3dsh, SPI_HandleTypeDef *hspi, GPIO_InitTypeDef *csPort, uint16_t csPin)
{
	lis3dsh->hspi		= hspi;
	lis3dsh->cs_port    = csPort;
	lis3dsh->cs_pin     = csPin;

	lis3dsh->x_raw		= 0;
	lis3dsh->y_raw		= 0;
	lis3dsh->z_raw		= 0;

	if(LIS3DSH_Who_Am_I(lis3dsh) == LIS3DSH_WHO_AM_I_VALUE)
	{
		//Sensor Bulundu!
		lis3dsh->found  = true;

		// Config
		// CTRL_REG4: X, Y, Z aktif ve ODR 800Hz
		if(!LIS3DSH_Write_Register(lis3dsh, LIS3DSH_CTRL_REG4, 0x87))
			return false;
		// CTRL_REG5: +-2g full scale, anti-alias filter 800Hz
		if(!LIS3DSH_Write_Register(lis3dsh, LIS3DSH_CTRL_REG5, 0x00))
			return false;
	}
	else
	{
		lis3dsh->found  = false;
	}

	return true;
}

uint8_t LIS3DSH_Who_Am_I(LIS3DSH_t *lis3dsh)
{
	return LIS3DSH_Read_Register(lis3dsh, LIS3DSH_WHO_AM_I_ADDR);
}

bool LIS3DSH_Read_XYZ(LIS3DSH_t *lis3dsh)
{
	uint8_t xl, xh, yl, yh, zl, zh;

	xl = LIS3DSH_Read_Register(lis3dsh, LIS3DSH_OUT_X_L);
	xh = LIS3DSH_Read_Register(lis3dsh, LIS3DSH_OUT_X_H);
	lis3dsh->x_raw = (int16_t)(xh << 8) | xl;

	yl = LIS3DSH_Read_Register(lis3dsh, LIS3DSH_OUT_Y_L);
	yh = LIS3DSH_Read_Register(lis3dsh, LIS3DSH_OUT_Y_H);
	lis3dsh->y_raw = (int16_t)(yh << 8) | yl;

	zl = LIS3DSH_Read_Register(lis3dsh, LIS3DSH_OUT_Y_L);
	zh = LIS3DSH_Read_Register(lis3dsh, LIS3DSH_OUT_Y_H);
	lis3dsh->z_raw = (int16_t)(zh << 8) | zl;

	return true;
}

uint8_t LIS3DSH_Read_Register(LIS3DSH_t *lis3dsh, uint8_t regAddr)
{
	// MSB = 1 olacak okuma işlemi için
	uint8_t txData = regAddr | 0x80;
	uint8_t rxData = 0;

	LIS3DSH_CS_Enable(lis3dsh);
	// 1. Yöntem
	if(HAL_SPI_Transmit(lis3dsh->hspi, &txData, 1, 100) == HAL_OK)
	{
		// TODO: Veriyi al...
		if(HAL_SPI_Receive(lis3dsh->hspi, &rxData, 1, 100) == HAL_OK)
		{
			// Diagnostic mesajlar ya da farklı işlemler
		}
	}
	// 2. Yöntem
	/*
	if(HAL_SPI_TransmitReceive(lis3dsh->hspi, &txData, &rxData, 1, 100) == HAL_OK)
	{
		return rxData;
	}
	*/
	LIS3DSH_CS_Disable(lis3dsh);

	return rxData;
}

bool LIS3DSH_Write_Register(LIS3DSH_t *lis3dsh, uint8_t regAddr, uint8_t data)
{
	uint8_t txData[2] = {0};

	txData[0] = regAddr & 0x7F;
	txData[1] = data;

	LIS3DSH_CS_Enable(lis3dsh);
	HAL_StatusTypeDef status = HAL_SPI_Transmit(lis3dsh->hspi, txData, 2, 100);
    LIS3DSH_CS_Disable(lis3dsh);

	return (status == HAL_OK);
}


