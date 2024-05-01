/*  Author     : Muhamed Amr         */
/*  SWC        : BlueTooth Module    */
/*  Layer      : HAL                 */		
/*  Version    : 1.0                 */
/*  Date       : April 22, 2024      */
/*  Last Edit  : N/P                 */
/*************************************/

#include "../LIB/LSTD_types.h"
#include "../LIB/LBIT_math.h"

#include "../MCAL/MUART_interface.h"

#include "HBLTH_interface.h"
#include "HBLTH_config.h"
#include "HBLTH_private.h"


void HBLTH_voidInit(void)
{
	MUART_voidInit(9600,HBLTH_DATABITS,HBLTH_PARITY,HBLTH_STOPBITS);
	MUART_voidEnableTx();
	MUART_voidEnableRx();
}
char HBLTH_charReceiveChar(void)
{
	char L_charRx;
	L_charRx = MUART_charReceiveChar();
	return L_charRx;
}
