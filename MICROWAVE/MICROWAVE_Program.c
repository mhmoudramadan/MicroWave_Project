/*
 * MICROWAVE_Program.c
 *
 *  Created on: Apr 19, 2022 3:34:42 AM
 *      Author: mahmoud ramadan 
 */
#include"../LIB/LSTD_TYPES.h"
#include"../MCAL/MDIO/MDIO_Interface.h"
#include"../HAL/HBUTTON/HBUTTON_Interface.h"
#include"../MCAL/MADC/MADC_Interface.h"
#include"../MCAL/MTIMER0/MTIMER0_Config.h"
#include"../MCAL/MTIMER0/MTIMER0_Interface.h"
#include"../MCAL/MGIE/MGIE_Interface.h"
#include"../HAL/HKPD/HKPD_Config.h"
#include"../HAL/HKPD/HKPD_Interface.h"
#include"../HAL/HCLCD/HCLCD_Config.h"
#include"../HAL/HCLCD/HCLCD_Interface.h"
#include"../HAL/HLED/HLED_Interface.h"
#include"../HAL/HTEMPERATURE/HTEMPERATURE_Interface.h"
#include"MICROWAVE_Interface.h"
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/*Global Variable To Store Value of Time*/
volatile uint8 Global_uint8Timebuffer[5]="  :  ";
volatile uint8 Global_bufferIndex;

volatile uint8 CloseFlag=0,SensorFlag=0,DoorFlag=0,StartFlag=0,StopFlag=0,CancelFlag=0,Heatflag=0
		,HeatFlagEnd=0;

static uint32 TimerCounts=0;
Button_t startbutton={MDIO_PORTD,PIN1,PULL_UP};
Button_t doorbutton={MDIO_PORTD,PIN0,PULL_UP};
Button_t canceltbutton={MDIO_PORTD,PIN2,PULL_UP};
Button_t DoorClose={MDIO_PORTD,PIN4,PULL_UP};
Button_t weightsensortbutton={MDIO_PORTC,PIN7,PULL_UP};
Button_t stopbutton={MDIO_PORTC,PIN6,PULL_UP};
LED_T HeaterLed={MDIO_PORTC,PIN5,ACTIVE_HIGH};
/*Timer Call Back*/
void App_Tov(void);
/*initialize Microwave*/
void MicroWave_VidInit(void)
{
	uint8 Loc_KeypadState;
	/*Initialize button of
	 * 1-start
	 * 2-stop
	 * 3-cancel
	 * 4-open fan
	 * 5-open heater
	 * 6-door*/
	MicroWave_VidWelcomemessage();
	_delay_ms(1000);
	MicroWave_VidUserMessage();
	_delay_ms(1000);
	HAL_VidHCLCD_4BitModeSendCommand(0x01);
	HBUTTON_Errorstate_Button_Init(&startbutton);
	HBUTTON_Errorstate_Button_Init(&doorbutton);
	HBUTTON_Errorstate_Button_Init(&canceltbutton);
	HBUTTON_Errorstate_Button_Init(&weightsensortbutton);
	HBUTTON_Errorstate_Button_Init(&stopbutton);
	HBUTTON_Errorstate_Button_Init(&DoorClose);
	/*Global interrupt*/
	MGIE_Enable();
	/*initialize Fan DC motor D3*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN3,PIN_OUTPUT);
	/*Initialize heater Temperature ADC pin A0 */
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN0,PIN_INPUT);
	/*Set Buzzer*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTC,PIN0,PIN_OUTPUT);
	/*Initialize heater*/
	HTEMP_VidInit();
	/*initialize heater led*/
	HLED_Errorstate_Led_Init(&HeaterLed);
	/*Initialize KEYPAD*/
	HKPD_VidInit();
	while(1)
	{
		Loc_KeypadState=HKPD_uint8GetPressed();
		if(Loc_KeypadState!=HKPD_NOTPRESSED)
		{
			MicroWave_VidGetTime(Loc_KeypadState);
		}
	}

}
/*Welcome message*/
void MicroWave_VidWelcomemessage(void)
{
	HAL_VidHCLCD_4BitModeSetPosition(1,0);
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"Welcome..");
	_delay_ms(3000);

}
/*user message to set time*/
void MicroWave_VidUserMessage(void)
{
	HAL_VidHCLCD_4BitModeSendCommand(0x01);
	HAL_VidHCLCD_4BitModeSetPosition(1,0);
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"Set Time");
	_delay_ms(2000);

}
/*Print default Time*/
void MicroWave_VidDefaultTime(void)
{
	HAL_VidHCLCD_4BitModeSetPosition(1,0);
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"00:00");
}
/*Get time From User*/
void MicroWave_VidGetTime(uint8 copy_uint8Time)
{
	if(copy_uint8Time == '=')
		{
		Heatflag=1;
		StartFlag=1;
		MTIMER0_VidInit();
			/*Call Manage System*/
		MicroWave_VidManageSystem();
		}
		else
		{
			HAL_VidHCLCD_4BitModeWriteChar(copy_uint8Time);
			Global_uint8Timebuffer[Global_bufferIndex]=copy_uint8Time+48;
			Global_bufferIndex++;
			if(Global_bufferIndex==2)
			{
				HAL_VidHCLCD_4BitModeWriteChar(':');
			}
		}
}
/*Get time*/
void MicroWave_VidSetTime(void)
{
	/*Check for CountDown of Time*/
	uint8 i=0;
	if(CloseFlag==1)
	{
		for(i=0;i<Global_bufferIndex;i++)
		{
			Global_uint8Timebuffer[Global_bufferIndex]=48-Global_uint8Timebuffer[Global_bufferIndex];
		}
	}
}
/*Get weight sensor value*/
uint8 MicroWave_uint8Sensor(void)
{
	if(HBUTTON_Errorstate_Button_Pressed(&weightsensortbutton) && HBUTTON_Errorstate_Button_Pressed(&doorbutton)
			&& HBUTTON_Errorstate_Button_Pressed(&startbutton))
	{
		SensorFlag=1;
	}
	MicroWave_VidUserMessage();
	return SensorFlag;
}
/*open Fan*/
void MicroWave_VidOpenFan(void)
{
	/*Dc motor Pin D3*/
	MDIO_Errorstate_SetPinValue(MDIO_PORTD,PIN3,PIN_HIGH);

}
/*Close Fan*/
void MicroWave_VidCloseFan(void)
{
	MDIO_Errorstate_SetPinValue(MDIO_PORTD,PIN3,PIN_LOW);
}
/*open Microwave*/
void MicroWave_VidOpenMicroWave(void)
{
	if(HBUTTON_Errorstate_Button_Pressed(&doorbutton))
	{
		DoorFlag=1;
	}
}
/*Close Microwave*/
void MicroWave_VidCloseMicroWave(void)
{
	if(HBUTTON_Errorstate_Button_Pressed(&DoorClose)&&(SensorFlag==1))
	{
		CloseFlag=1;
	}
	else
	{
		MDIO_Errorstate_SetPinValue(MDIO_PORTC,PIN0,PIN_HIGH);
		_delay_ms(500);
		MDIO_Errorstate_SetPinValue(MDIO_PORTC,PIN0,PIN_LOW);
	}
}
/*Cancel operation of MicroWave*/
void MicroWave_vidCancelOperation(void)
{
	/*Push button*/
	if(HBUTTON_Errorstate_Button_Pressed(&canceltbutton))
	{
		CancelFlag=1;
		Heatflag=0;
		HAL_VidHCLCD_4BitModeSendCommand(0x01);
		HAL_VidHCLCD_4BitModeWriteString((uint8*)"Cancel Heat");
	}
}
/*MicroWave manage*/
void MicroWave_VidManageSystem(void)
{

	if(CloseFlag==1 && StartFlag==1 && Heatflag==1)
	{

		MTIMER0_VidTimerOverFlow_SetCallBack(App_Tov);
		if(HeatFlagEnd==1)
		{
			HAL_VidHCLCD_4BitModeSendCommand(0x01);
			/*Finish*/
			MicroWave_VidTimeFinish();
			MicroWave_VidDefaultTime();
			/*open microwave*/
			MicroWave_VidOpenMicroWave();
			HeatFlagEnd=0;
			CloseFlag=0;
			Heatflag=0;
			StopFlag=0;
			StartFlag=0;
		}
		else
		{
			HAL_VidHCLCD_4BitModeSetPosition(2,0);
			HAL_VidHCLCD_4BitModeWriteString((uint8*)"Heating");
		}
	}



}
/*Time Finished*/
void MicroWave_VidTimeFinish(void)
{
	HAL_VidHCLCD_4BitModeSetPosition(2,0);
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"HappyMeal");
}
void MicorWave_VidHeaterInit(void)
{
	/*Led on*/
	HLED_Errorstate_Led_On(&HeaterLed);
	Heatflag=1;
}
/*Temperature of Heater */
void MicroWave_VidGetHeaterTemp(uint16 copy_uint8Temp)
{
	copy_uint8Temp=HTEMP_uintGetTemp(0);
	MicroWave_VidHeaterTempDisplay();
	HAL_VidHCLCD_4BitModeSetPosition(1,5);
	HAL_VidHCLCD_4BitModeWriteNumber(copy_uint8Temp);
	_delay_ms(1000);
	HAL_VidHCLCD_4BitModeSendCommand(0x01);
	if(copy_uint8Temp==0)
	{
		HLED_Errorstate_Led_Off(&HeaterLed);
	}
}
/*Temperature message*/
void MicroWave_VidHeaterTempDisplay(void)
{
	HAL_VidHCLCD_4BitModeSendCommand(0x01);
	HAL_VidHCLCD_4BitModeSetPosition(1,0);
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"temp:");
}
void App_Tov(void)
{
	TimerCounts++;
	if(TimerCounts==1000)
	{
		MicroWave_VidSetTime();
	}
	else
	{

	}
}

