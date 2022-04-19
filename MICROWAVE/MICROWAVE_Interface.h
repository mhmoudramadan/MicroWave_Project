/*
 * MICROWAVE_Interface.h
 *
 *  Created on: Apr 19, 2022 3:34:23 AM
 *      Author: mahmoud ramadan 
 */

#ifndef MICROWAVE_MICROWAVE_INTERFACE_H_
#define MICROWAVE_MICROWAVE_INTERFACE_H_

/*initialize Microwave*/
void MicroWave_VidInit(void);
/*Welcome message*/
void MicroWave_VidWelcomemessage(void);
/*user message to set time*/
void MicroWave_VidUserMessage(void);
/*Print default Time*/
void MicroWave_VidDefaultTime(void);
/*Get time From User*/
void MicroWave_VidGetTime(uint8 copy_uint8Time);
/*Get weight sensor value*/
uint8 MicroWave_uint8Sensor(void);
/*Get time*/
void MicroWave_VidSetTime(void);
/*open Fan*/
void MicroWave_VidOpenFan(void);
/*Close Fan*/
void MicroWave_VidCloseFan(void);
/*open Microwave*/
void MicroWave_VidOpenMicroWave(void);
/*Close Microwave*/
void MicroWave_VidCloseMicroWave(void);
/*Cancel operation of MicroWave*/
void MicroWave_vidCancelOperation(void);
/*MicroWave manage*/
void MicroWave_VidManageSystem(void);
/*Time Finished*/
void MicroWave_VidTimeFinish(void);
/*Heater on*/
void MicorWave_VidHeaterInit(void);
/*Temperature of Heater */
void MicroWave_VidGetHeaterTemp(uint16 copy_uint8Temp);
/*Temperature message*/
void MicroWave_VidHeaterTempDisplay(void);
#endif /* MICROWAVE_MICROWAVE_INTERFACE_H_ */
