/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : Global Interrupt    */
/*  Layer      : MCAL                */
/*  Version    : 1.0                 */
/*  Date       : Octuber 21, 2023    */
/*  Last Edit  : N/A     	         */
/*************************************/

#include "../LIB/LSTD_types.h"
#include "../LIB/LBIT_math.h"

#include "MGIE_private.h"
#include "MGIE_interface.h"

void MGIE_voidEnableGIE(void)
{
	SET_BIT(SREG, I);
}

void MGIE_voidDisableGIE(void)
{
	CLEAR_BIT(SREG, I);
}
