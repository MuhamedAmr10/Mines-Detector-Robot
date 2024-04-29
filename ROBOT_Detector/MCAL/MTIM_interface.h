/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : Timers		         */
/*  Layer      : MCAL                */
/*  Version    : 1.1                 */
/*  Date       : November 11, 2023   */
/*  Last Edit  : November 25         */
/*************************************/


#ifndef _MTIM_INTERFACE_H_
#define _MTIM_INTERFACE_H_

//Timers Names
#define	MTIM_TIMER0					0
#define MTIM_TIMER1A				1
#define MTIM_TIMER1B				2
#define MTIM_TIMER2					3

//Timers Mode Operation
#define MTIM_MODE_NORMAL			0
#define MTIM_MODE_CTC				1
#define MTIM_MODE_FASTPWM			2
#define MTIM_MODE_PHASECORRECTPWM	3

//Prescaller 
#define MTIM_CS_NOCLOCK				0
#define MTIM_CS_PRESCALER_1			1
#define MTIM_CS_PRESCALER_8			2
#define MTIM_CS_PRESCALER_64		3
#define MTIM_CS_PRESCALER_256		4
#define MTIM_CS_PRESCALER_1024		5
#define MTIM_CS_T0_FALLING			6
#define MTIM_CS_T0_RISING			7

//Hardware Pin Mode
#define MTIM_HWPIN_DISCONNECTED		0
#define MTIM_HWPIN_TOGGLE			1
#define MTIM_HWPIN_CLEAR			2
#define MTIM_HWPIN_SET				3
#define MTIM_HWPIN_NONINVERTING_PWM	2
#define MTIM_HWPIN_INVERTING_PWM	3

//Interrupt Sources
#define MTIM_INTERRUPT_T0_OVF		0
#define MTIM_INTERRUPT_T0_OCM		1
#define MTIM_INTERRUPT_T1_OVF		2
#define MTIM_INTERRUPT_T1_OCMB		3
#define MTIM_INTERRUPT_T1_OCMA		4
#define MTIM_INTERRUPT_T1_ICU		5

//ICU Edge Selection
#define MTIM_EDGE_SELECT_FALLING	0
#define MTIM_EDGE_SELECT_RISING		1

//ICU Noise Canceler Connection 
#define MTIM_EDGE_SELECT_DISCONNECT	0	
#define MTIM_NOISE_CANCELER_SET		1



#ifndef F_CPU
#define F_CPU	8000000UL
#warning F_CPU not define. Assuming 8MHz Clock.
#endif

void MTIM_voidInitTimer(u8 ARG_u8TimerNo, u8 ARG_u8Mode, u8 ARG_u8ClockSource, u8 ARG_u8HWPinMode);

void MTIM_voidForceOutputCompare(u8 ARG_u8TimerNo);

void MTIM_voidEnableInterrupt(u8 ARG_u8InterruptSource);
void MTIM_voidDisableInterrupt(u8 ARG_u8InterruptSource);
void MTIM_voidSetCallback(void (*ARG_pvoidfUserFunction)(void), u8 ARG_u8InterruptSource);

void MTIM_voidStartTimer(u8 ARG_u8TimerNo);
void MTIM_voidStopTimer(u8 ARG_u8TimerNo);

void MTIM_voidSetTimerValue(u8 ARG_u8TimerNo, u16 ARG_u16Value);
u16	 MTIM_u16GetTimerValue(u8 ARG_u8TimerNo);
void MTIM_voidTimerDelay(u8 ARG_u8TimerNo, u32 ARG_u32Delay);
void MTIM_voidResetTimer(u8 ARG_u8TimerNo);

void MTIM_voidSetOCR(u8 ARG_u8TimerNo, u16 ARG_u16OCRValue);

void MTIM_voidInitICU(u8 ARG_u8EdgeSelect,u8 ARG_u8NoiseCancelerConnection);
u16 MTIM_u16ReadingICU(void);
void MTIM_voidICUSelectEdge(u8 ARG_u8EdgeSelect);


#endif
