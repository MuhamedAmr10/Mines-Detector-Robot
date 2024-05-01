/*  Author     : Muhamed Amr         */
/*  SWC        : UART			     */
/*  Layer      : MCAL                */
/*  Version    : 1.0                 */
/*  Date       : December 2, 2023    */
/*  Last Edit  : N/P                 */
/*************************************/

#ifndef _MUART_INTERFACE_H_
#define _MUART_INTERFACE_H_


#define MUART_DATABITS_5		0
#define MUART_DATABITS_6		1
#define MUART_DATABITS_7		2
#define MUART_DATABITS_8		3
#define MUART_DATABITS_9		7

#define MUART_PARITY_NONE		0
#define MUART_PARITY_EVEN		2
#define MUART_PARITY_ODD		3

#define MUART_STOPBITS_1		0
#define MUART_STOPBITS_2		1

#define MUART_INTERRUPT_RXC		7
#define MUART_INTERRUPT_TXC		6
#define MUART_INTERRUPT_UDRE	5

void MUART_voidInit(u32 ARG_u32BaudRate ,u8 ARG_u8DataBits ,u8 ARG_u8Parity ,u8 ARG_u8StopBits);

void MUART_voidEnableTx(void);
void MUART_voidDisableTx(void);

void MUART_voidEnableRx(void);
void MUART_voidDisableRx(void);

void MUART_voidEnableInterrupt(u8 ARG_u8InterruptSource);
void MUART_voidDisableInterrupt(u8 ARG_u8InterruptSource);
void MUART_voidSetCallback(void (*ARG_pvoidfUserFunction)(void), u8 ARG_u8InterruptSource);

void MUART_voidTxFlagPolling(void);
void MUART_voidRxFlagPolling(void);
void MUART_voidUDREFlagPolling(void);

void MUART_voidSendChar(char ARG_charChar);
char MUART_charReceiveChar(void);

void MUART_voidSendString(const char* ARG_ccharpString);
void MUART_voidReceiveStringUntil(char* ARG_ccharpString ,char ARG_charTerminatingChar);



#endif
