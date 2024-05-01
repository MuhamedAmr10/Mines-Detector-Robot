/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : Buzzer		         */
/*  Layer      : HAL                 */
/*  Version    : 1.0                 */
/*  Date       : April 20, 2024      */
/*  Last Edit  : N/A		         */
/*************************************/

#define F_CPU 	8000000UL
#include <util/delay.h>

#include "../LIB/LSTD_types.h"
#include "../LIB/LBIT_math.h"

#include "../MCAL/MDIO_interface.h"

#include "HBUZ_interface.h"
#include "HBUZ_private.h"
#include "HBUZ_config.h"

void HBUZ_voidInit(void)
{
	MDIO_voidSetPinDirection(HBUZ_PORT,HBUZ_PIN,MDIO_OUTPUT);
	
	//by default buzzer pin is low
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_LOW);
}
void HBUZ_voidEnableAlarm(void)
{
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_HIGH);
	_delay_ms(1000);
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_LOW);
	_delay_ms(500);
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_HIGH);
	_delay_ms(1000);
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_LOW);
	_delay_ms(1000);
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_HIGH);
	_delay_ms(500);
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_LOW);
	_delay_ms(500);
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_HIGH);
	_delay_ms(500);
}
void HBUZ_voidDisableAlarm(void)
{
	MDIO_voidSetPinValue(HBUZ_PORT,HBUZ_PIN,MDIO_LOW);
}
