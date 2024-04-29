/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : Metal Detector      */
/*  Layer      : HAL                 */
/*  Version    : 1.0                 */
/*  Date       : March 2, 2024       */
/*  Last Edit  : N/A		         */
/*************************************/

#define F_CPU 	8000000UL
#include <util/delay.h>

#include "../LIB/LSTD_types.h"
#include "../LIB/LBIT_math.h"

#include "../MCAL/MDIO_interface.h"
#include "../MCAL/MEXTI_interface.h"

#include "HMETDET_config.h"
#include "HMETDET_interface.h"
#include "HMETDET_private.h"

static volatile u8 HMETDET_u8MineFlag = HMETDET_NO_MINE;

void HMETDET_voidInit(void)
{
	//Initializing External Interrput
	MEXTI_voidInit(HMETDET_INTERRUPT_NUM,HMETDET_INTERRUPT_MODE);
	MEXTI_voidEnableInterrupt(HMETDET_INTERRUPT_NUM);
	MEXTI_voidSetCallback(Metal_Detection,HMETDET_INTERRUPT_NUM);

	//Set External interrupt pin
	switch (HMETDET_INTERRUPT_NUM)
	{
	case MEXTI_INT0 :  MDIO_voidSetPinDirection(MDIO_PORTD,2,MDIO_INPUT); break;
	case MEXTI_INT1 :  MDIO_voidSetPinDirection(MDIO_PORTD,3,MDIO_INPUT); break;
	case MEXTI_INT2 :  MDIO_voidSetPinDirection(MDIO_PORTB,2,MDIO_INPUT); break;
	default : break;
	}
}

u8 HMETDET_u8GetMetalDetector(void)
{
	return HMETDET_u8MineFlag;
}

static void Metal_Detection(void)
{
	if(HMETDET_INTERRUPT_MODE==MEXTI_MODE_IOC)
	{
		static volatile u8 L_u8Counter = 0 ;
		L_u8Counter++;
		if(L_u8Counter % 2 == 1)
		{
			HMETDET_u8MineFlag = HMETDET_MINE;
		}
		else
		{
			HMETDET_u8MineFlag = HMETDET_NO_MINE;
		}
	}
	else
	{
		HMETDET_u8MineFlag = HMETDET_MINE;
	}
}

void HMETDET_voidClearMineFlag(void)
{
	HMETDET_u8MineFlag = HMETDET_NO_MINE;
}
