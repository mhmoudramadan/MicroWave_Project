/*
 * main.c
 *
 *  Created on: Apr 19, 2022 3:33:55 AM
 *      Author: mahmoud ramadan 
 */
#include"LIB/LSTD_TYPES.h"
#include"MCAL/MDIO/MDIO_Interface.h"
#include"MICROWAVE/MICROWAVE_Interface.h"
#include"HAL/HCLCD/HCLCD_Config.h"
#include"HAL/HCLCD/HCLCD_Interface.h"
#ifndef F_CPU
#define F_CPU 16000000
#endif


int main(void)
{
	/*LCD PINS*/
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RS_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RW_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,E_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN4,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN5,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN6,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN7,PIN_OUTPUT);
	/*initialize LCD*/
		HAL_VidHCLCD_4BitModeInit();
	MicroWave_VidInit();
	while(1)
	{

	}
	return 0;
}
