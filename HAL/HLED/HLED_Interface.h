/*
 * HLED.Interface.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Dell
 */

#ifndef HAL_HLED_HLED_INTERFACE_H_
#define HAL_HLED_HLED_INTERFACE_H_



#define ACTIVE_HIGH 1
#define ACTIVE_LOW  0


typedef struct
{
	uint8 LedPort;
	uint8 LedPin;
	uint8 LedActiveState;
}LED_T;

ErrorState HLED_Errorstate_Led_Init(LED_T* copy_LED_object);
ErrorState HLED_Errorstate_Led_On(LED_T* copy_LED_object);
ErrorState HLED_Errorstate_Led_Off(LED_T* copy_LED_object);
ErrorState HLED_Errorstate_Led_Toggle(LED_T* copy_LED_object);

#endif /* HAL_HLED_HLED_INTERFACE_H_ */
