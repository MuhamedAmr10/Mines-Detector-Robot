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

#include "HAL/HMOTOR_interface.h"
#include "HAL/HUS_interface.h"
#include "HAL/HMETDET_interface.h"

int main(void)
{
	//Set Pin Output For Buzzer
	MDIO_voidSetPinDirection(MDIO_PORTB,7,MDIO_OUTPUT);
	//By default Pin Buzzer is Low
	MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_LOW);

	//Initializing Drivers

	HMOTOR_voidInit();
	HUS_voidInit();
	HMETDET_voidInit();

	//Enable GIE
	MGIE_voidEnableGIE();

	while(1)
	{
		u8 L_u8Obstacle = HUS_u8GetUltraSonic();
		u8 L_u8Mine	= HMETDET_u8GetMetalDetector();

		//Detecting Obstacle

		if(HUS_NO_OBSTACLE == L_u8Obstacle)
		{
			// In this codition there is no obstacle , so robot moves forward

			HMOTOR_voidStartMovement(HMOTOR_DIRECTION_FORWARD);
		}
		else if(HUS_OBSTACLE == L_u8Obstacle)
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

		//Detecting Mine

		 if (HMETDET_MINE == L_u8Mine)
		{
			// In this codition mine is found , so robot should stop ,then give a five-minute alarm and finaly continue detection

			// Robot stop
			HMOTOR_voidStopMovement();

			// PORTB Pin 7 is Buzzer Pin

			MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_HIGH);
			_delay_ms(1000);
			MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_LOW);
			_delay_ms(500);
			MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_HIGH);
			_delay_ms(700);
			MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_LOW);
			_delay_ms(500);
			MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_HIGH);
			_delay_ms(500);
			MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_LOW);
			_delay_ms(1200);
			MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_HIGH);
			_delay_ms(300);
			MDIO_voidSetPinValue(MDIO_PORTB,7,MDIO_LOW);

			// In order to continue detection
			HMETDET_voidClearMineFlag();
		}

	}

	return 0;
}
