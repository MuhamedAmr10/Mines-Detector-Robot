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

#include "HMOTOR_interface.h"
#include "HMOTOR_config.h"

void HMOTOR_voidInit(void)
{
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_ENA ,MDIO_OUTPUT);
	MDIO_voidSetPinDirection(HMOTOR_PORT,HMOTOR_PIN_ENB ,MDIO_OUTPUT);
}

void HMOTOR_voidStartMovement(u8 ARG_u8Direction)
{
	if(ARG_u8Direction == HMOTOR_DIRECTION_RIGHT )
	{
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_LOW);
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_LOW);
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_HIGH);
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_HIGH);
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENA,MDIO_HIGH);
		MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENB,MDIO_HIGH);
	}
	else if(ARG_u8Direction == HMOTOR_DIRECTION_LEFT )
		{
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_LOW);
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_LOW);
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENA ,MDIO_HIGH);
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_HIGH);
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_HIGH);
			MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENB ,MDIO_HIGH);
		}
	else if(ARG_u8Direction == HMOTOR_DIRECTION_FORWARD )
		{
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_LOW);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_LOW);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_HIGH);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_HIGH);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENA ,MDIO_HIGH);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENB ,MDIO_HIGH);
		}
	else if(ARG_u8Direction == HMOTOR_DIRECTION_BACKWARD )
		{
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_LOW);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_LOW);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_HIGH);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_HIGH);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENA ,MDIO_HIGH);
		    MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENB ,MDIO_HIGH);
		}
	else
	{
		//report an Error
	}
}

void HMOTOR_voidStopMovement(void)
{
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT1,MDIO_LOW);
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT3,MDIO_LOW);
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT2,MDIO_LOW);
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_INT4,MDIO_LOW);
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENA ,MDIO_LOW);
	MDIO_voidSetPinValue(HMOTOR_PORT,HMOTOR_PIN_ENB ,MDIO_LOW);
}

