/*  Author     : Muhamed Amr         */
/*  SWC        : DC MOTOR	         */
/*  Layer      : HAL                 */		
/*  Version    : 1.0                 */
/*  Date       : FEBRAURY 18, 2024   */
/*  Last Edit  : N/P                 */
/*************************************/

#include "../LIB/LSTD_types.h"
#include "../LIB/LBIT_math.h"

#include "../MCAL/MDIO_interface.h"
#include "../MCAL/MTIM_interface.h"

#include "HMOTOR_interface.h"
#include "HMOTOR_config.h"

void HMOTOR_voidInit(void)
{
	//Set the Direction of OC0 as Output Pin
	MDIO_voidSetPinDirection(MDIO_PORTB,3,MDIO_OUTPUT);

	//Timer 0 is used to Control Speed Of Motor Using FASTPWM Mode
	MTIM_voidInitTimer(MTIM_TIMER0,MTIM_MODE_FASTPWM,MTIM_CS_PRESCALER_64,MTIM_HWPIN_NONINVERTING_PWM);

	//Setting The Motor Normal Speed in General Case
	HMOTOR_voidSpeedControl(HMOTOR_SPEED_NORMAL);

	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_OUTPUT);


}
void HMOTOR_voidStartMovement(u8 ARG_u8Direction)
{
	if(ARG_u8Direction == HMOTOR_DIRECTION_LEFT )
	{
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_LOW);
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_LOW);

		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_HIGH);
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_HIGH);

	}
	else if(ARG_u8Direction == HMOTOR_DIRECTION_RIGHT )
		{
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_LOW);
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_LOW);
			
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_HIGH);
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_HIGH);
			
		}
	else if(ARG_u8Direction == HMOTOR_DIRECTION_FORWARD )
		{
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_LOW);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_LOW);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_HIGH);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_HIGH);
		    
		}
	else if(ARG_u8Direction == HMOTOR_DIRECTION_BACKWARD )
		{
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_LOW);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_LOW);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_HIGH);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_HIGH);
		  
		}
	else
	{
		//report an Error
	}
	MTIM_voidStartTimer(MTIM_TIMER0);
}

void HMOTOR_voidStopMovement(void)
{
	MTIM_voidStopTimer(MTIM_TIMER0);

	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_LOW);
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_LOW);
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_LOW);
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_LOW);
	
}
void HMOTOR_voidSpeedControl(u8 ARG_u8MotorSpeed)
{
	if((ARG_u8MotorSpeed <=HMOTOR_SPEED_FAST)&&(ARG_u8MotorSpeed>=HMOTOR_SPEED_SLOW))
	{

	 switch(ARG_u8MotorSpeed)
	 {
	 case HMOTOR_SPEED_FAST   :MTIM_voidSetOCR(MTIM_TIMER0,230);break;
	 case HMOTOR_SPEED_NORMAL :MTIM_voidSetOCR(MTIM_TIMER0,150);break;
	 case HMOTOR_SPEED_SLOW   :MTIM_voidSetOCR(MTIM_TIMER0,100);break;
	 default : break; /* Report an Error */

	 }

	}
	else
	{
		/* MISRA */
	}

}

