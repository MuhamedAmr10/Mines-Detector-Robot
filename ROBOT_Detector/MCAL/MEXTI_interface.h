/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : External Interrupts */
/*  Layer      : MCAL                */
/*  Version    : 1.0                 */
/*  Date       : Octuber 21, 2023    */
/*  Last Edit  : N/A     	         */
/*************************************/

#ifndef _MEXTI_INTERFACE_H_
#define _MEXTI_INTERFACE_H_

#define MEXTI_INT0     			 6
#define MEXTI_INT1     			 7
#define MEXTI_INT2     			 5

#define MEXTI_MODE_LOW			 0
#define MEXTI_MODE_IOC    	     1
#define MEXTI_MODE_RISING	  	 2
#define MEXTI_MODE_FALLING	     3

void MEXTI_voidInit(u8 ARG_u8InterruptNo ,u8 ARG_u8InterruptMode);

void MEXTI_voidEnableInterrupt(u8 ARG_u8InterruptNo);
void MEXTI_voidDisableInterrupt(u8 ARG_u8InterruptNo);

void MEXTI_voidSetCallback(void(*ARG_pvoidfUserFunction)(void), u8 ARG_u8InterruptNo);


#endif