/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : DIO		         */
/*  Layer      : MCAL                */
/*  Version    : 1.1                 */
/*  Date       : September 9 , 2023  */
/*  Last Edit  : September 15, 2023  */
/*************************************/

#ifndef _MDIO_INTERFACE_H_
#define _MDIO_INTERFACE_H_

#define MDIO_PORTA 24
#define MDIO_PORTB 9
#define MDIO_PORTC 20
#define MDIO_PORTD 2

#define MDIO_PORT_OUTPUT 0xFF
#define MDIO_PORT_INPUT  0x00

#define MDIO_INPUT          90
#define MDIO_OUTPUT         100
#define MDIO_INPUT_PULLUP	200	

#define MDIO_LOW            0
#define MDIO_HIGH           1
#define MDIO_TOGGLE         2


/* Port Access*/
void MDIO_voidSetPortDirection(u8 ARG_u8Port,u8 ARG_u8Direction);
void MDIO_voidSetPortValue(u8 ARG_u8Port,u8 ARG_u8Value);
u8   MDIO_u8GetPortValue(u8 ARG_u8Port);

/* Pin Access*/
void MDIO_voidSetPinDirection(u8 ARG_u8Port,u8 ARG_u8Pin,u8 ARG_u8Direction);
void MDIO_voidSetPinValue(u8 ARG_u8Port,u8 ARG_u8Pin,u8 ARG_u8Value);
u8 MDIO_u8GetPinValue(u8 ARG_u8Port,u8 ARG_u8Pin);

#endif
