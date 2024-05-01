/*
 * main.c
 *
 *  Created on: Apr 29, 2024
 *      Author: ahmed yousif
 */


#define F_CPU 8000000UL
#include <util/delay.h>

#include "LIB/LSTD_types.h"
#include "LIB/LBIT_math.h"

#include "MCAL/MDIO_interface.h"
#include "MCAL/MGIE_interface.h"
#include "MCAL/MTIM_interface.h"
#include "MCAL/MEXTI_interface.h"
#include "MCAL/MUART_interface.h"

#include "HAL/HMOTOR_interface.h"
#include "HAL/HUS_interface.h"
#include "HAL/HMETDET_interface.h"
#include "HAL/HBLTH_interface.h"
#include "HAL/HBUZ_interface.h"

#include "config.h"
#include "interface.h"


int main(void)
{
	/*
	//Set Pin Output For Buzzer
	MDIO_voidSetPinDirection(MDIO_PORTB,7,MDIO_OUTPUT);
	//By default Pin Buzzer is Low
	MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_LOW);
	*/

	//Initializing Drivers

	HMOTOR_voidInit();
	HUS_voidInit();
	HMETDET_voidInit();
	HBUZ_voidInit();
	HBLTH_voidInit();

	//Enable GIE
	MGIE_voidEnableGIE();

	while(1)
	{

		// Automatic Mode

		if(APP_AUTO_MODE == APP_MODE)
		{
			u8 L_u8Obstacle 	= HUS_u8GetUltraSonic();;
			u8 L_u8Mine		= HMETDET_u8GetMetalDetector();

			//Detecting Obstacle

			if(HUS_OBSTACLE == L_u8Obstacle)
			{
				// In this codition there is obstacle , so robot should stop ,then move backward ,then move left and finaly stop

				HMOTOR_voidStopMovement();
				_delay_ms(500);
				HMOTOR_voidStartMovement(HMOTOR_DIRECTION_BACKWARD);
				_delay_ms(1000);
				HMOTOR_voidStopMovement();
				_delay_ms(500);
				HMOTOR_voidStartMovement(HMOTOR_DIRECTION_LEFT);
				_delay_ms(300);
				HMOTOR_voidStopMovement();
			}

			else if(HUS_NO_OBSTACLE == L_u8Obstacle)
			{
				// In this codition there is no obstacle , so robot moves forward
				HMOTOR_voidStartMovement(HMOTOR_DIRECTION_FORWARD);
			}

			//Detecting Mine

			if (HMETDET_MINE == L_u8Mine)
			{
				// In this codition mine is found , so robot should stop ,then give a five-minute alarm and finaly continue detection

				// Robot stop
				HMOTOR_voidStopMovement();

				HBUZ_voidEnableAlarm();
				HBUZ_voidDisableAlarm();

				// In order to continue detection
				HMETDET_voidClearMineFlag();
			}

		}

		//Manual Mode

		else if(APP_MANUAL_MODE	== APP_MODE )
		{

			u8 L_u8Mine	= HMETDET_u8GetMetalDetector();
			char L_charMovementControl = HBLTH_charReceiveChar();

			//Direction Remote Control

			if(MOVEMENT_FORWARD == L_charMovementControl)
			{
				HMOTOR_voidStartMovement(HMOTOR_DIRECTION_FORWARD);
				_delay_ms(1000);
				HMOTOR_voidStopMovement();
			}

			else if (MOVEMENT_BACKWARD == L_charMovementControl)
			{
				HMOTOR_voidStartMovement(HMOTOR_DIRECTION_BACKWARD);
				_delay_ms(1000);
				HMOTOR_voidStopMovement();
			}

			else if (MOVEMENT_LEFT == L_charMovementControl)
			{
				HMOTOR_voidStartMovement(HMOTOR_DIRECTION_LEFT);
				_delay_ms(200);
				HMOTOR_voidStopMovement();
			}

			else if(MOVEMENT_RIGHT == L_charMovementControl)
			{
				HMOTOR_voidStartMovement(HMOTOR_DIRECTION_RIGHT);
				_delay_ms(200);
				HMOTOR_voidStopMovement();
			}

			else if (MOVEMENT_STOP == L_charMovementControl)
			{
				HMOTOR_voidStopMovement();
			}

			//Speed Remote Control

			else if (SPEED_SLOW == L_charMovementControl)
			{
				HMOTOR_voidSpeedControl(HMOTOR_SPEED_SLOW);
			}
			else if (SPEED_NORMAL == L_charMovementControl)
			{
				HMOTOR_voidSpeedControl(HMOTOR_SPEED_NORMAL);
			}
			else if (SPEED_FAST == L_charMovementControl)
			{
				HMOTOR_voidSpeedControl(HMOTOR_SPEED_FAST);
			}

			// Detecting Mine

			if (HMETDET_MINE == L_u8Mine)
			{
				// In this codition mine is found , so robot should stop ,then give a five-minute alarm and finaly continue detection

				// Robot stop
				HMOTOR_voidStopMovement();

				// Buzzer give an alaram for a while
				HBUZ_voidEnableAlarm();
				HBUZ_voidDisableAlarm();

				// In order to continue detection
				HMETDET_voidClearMineFlag();
			}

		}

	}

	return 0;
}
