/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : Timers		         */
/*  Layer      : MCAL                */
/*  Version    : 1.1                 */
/*  Date       : November 11, 2023   */
/*  Last Edit  : February  8	     */
/*************************************/

#include "../LIB/LSTD_types.h"
#include "../LIB/LBIT_math.h"

#include "MTIM_interface.h"
#include "MTIM_private.h"

static u8 MTIM_u8Timer0Clock = MTIM_CS_NOCLOCK;
static u8 MTIM_u8Timer1Clock = MTIM_CS_NOCLOCK;

static volatile u16 MTIM_u16Timer0OVFCount = 0;
static volatile u8	MTIM_u8Timer0Preload = 0;

static volatile u32 MTIM_u32Timer1OVFCount = 0;
static volatile u16	MTIM_u16Timer1Preload = 0;

static void (*MTIM_pvoidfUserFunctionT0OVF)(void) = NULL_POINTER;
static void (*MTIM_pvoidfUserFunctionT0OCM)(void) = NULL_POINTER;

static void (*MTIM_pvoidfUserFunctionT1OVF)(void) = NULL_POINTER;
static void (*MTIM_pvoidfUserFunctionT1OCMA)(void) = NULL_POINTER;
static void (*MTIM_pvoidfUserFunctionT1OCMB)(void) = NULL_POINTER;
static void (*MTIM_pvoidfUserFunctionT1ICU)(void) = NULL_POINTER;

void MTIM_voidInitTimer(u8 ARG_u8TimerNo, u8 ARG_u8Mode, u8 ARG_u8ClockSource, u8 ARG_u8HWPinMode)
{
	if((ARG_u8TimerNo<=2)&&(ARG_u8Mode<=3)&&(ARG_u8ClockSource<=7)&&(ARG_u8HWPinMode<=3))
	{
		switch(ARG_u8TimerNo)
		{
			case MTIM_TIMER0:  //TIMER0
			{
				switch(ARG_u8Mode)
				{
					case MTIM_MODE_NORMAL:
					{
						CLEAR_BIT(TCCR0, WGM01);
						CLEAR_BIT(TCCR0, WGM00);
						break;
					}
					case MTIM_MODE_CTC:
					{
						CLEAR_BIT(TCCR0, WGM00);
						SET_BIT(TCCR0, WGM01);
						break;
					}
					case MTIM_MODE_FASTPWM:
					{
						SET_BIT(TCCR0, WGM01);
						SET_BIT(TCCR0, WGM00);
						break;
					}
					case MTIM_MODE_PHASECORRECTPWM:
					{
						CLEAR_BIT(TCCR0, WGM01);
						SET_BIT(TCCR0, WGM00);
						break;
					}
					default: break; /* Report an Error */
				}
				TCCR0 = (TCCR0&0xCF) | (ARG_u8HWPinMode << COM00);
				MTIM_u8Timer0Clock = ARG_u8ClockSource;				
				break;
			}
			case MTIM_TIMER1A : //Timer1A
			{
				switch(ARG_u8Mode)
				{
					case MTIM_MODE_NORMAL: 
					{
						CLEAR_BIT(TCCR1B, WGM13);
						CLEAR_BIT(TCCR1B, WGM12);
						CLEAR_BIT(TCCR1A, WGM11);
						CLEAR_BIT(TCCR1A, WGM10);
						break;
					}
					case MTIM_MODE_CTC : 
					{
						CLEAR_BIT(TCCR1A,WGM10);
						CLEAR_BIT(TCCR1A,WGM11);
						CLEAR_BIT(TCCR1B,WGM13);
						SET_BIT(TCCR1B,WGM12);
					}
					case MTIM_MODE_FASTPWM :
					{
						CLEAR_BIT(TCCR1B,WGM13);
						CLEAR_BIT(TCCR1A,WGM11);
						SET_BIT(TCCR1A,WGM10);
						SET_BIT(TCCR1B,WGM12);
					}
					case MTIM_MODE_PHASECORRECTPWM :
					{
						CLEAR_BIT(TCCR1A,WGM11);
						CLEAR_BIT(TCCR1B,WGM13);
						CLEAR_BIT(TCCR1B,WGM12);
						CLEAR_BIT(TCCR1A,WGM10);
					}
					default: break; /* Report an Error */
				}
				TCCR1A = (TCCR1A&0x3F) | (ARG_u8HWPinMode << COM1A0);
				MTIM_u8Timer1Clock = ARG_u8ClockSource;
				break;
			}
			case MTIM_TIMER1B : //Timer1B
			{
				switch(ARG_u8Mode)
				{
					case MTIM_MODE_NORMAL: 
					{
						CLEAR_BIT(TCCR1B, WGM13);
						CLEAR_BIT(TCCR1B, WGM12);
						CLEAR_BIT(TCCR1A, WGM11);
						CLEAR_BIT(TCCR1A, WGM10);
						break;
					}
					case MTIM_MODE_CTC : 
					{
						CLEAR_BIT(TCCR1A,WGM10);
						CLEAR_BIT(TCCR1A,WGM11);
						CLEAR_BIT(TCCR1B,WGM13);
						SET_BIT(TCCR1B,WGM12);
					}
					case MTIM_MODE_FASTPWM :
					{
						CLEAR_BIT(TCCR1B,WGM13);
						CLEAR_BIT(TCCR1A,WGM11);
						SET_BIT(TCCR1A,WGM10);
						SET_BIT(TCCR1B,WGM12);
					}
					case MTIM_MODE_PHASECORRECTPWM :
					{
						CLEAR_BIT(TCCR1A,WGM11);
						CLEAR_BIT(TCCR1B,WGM13);
						CLEAR_BIT(TCCR1B,WGM12);
						CLEAR_BIT(TCCR1A,WGM10);
					}
					default: break; /* Report an Error */
				}
				TCCR1A = (TCCR1A&0xCF) | (ARG_u8HWPinMode << COM1B0);
				MTIM_u8Timer1Clock = ARG_u8ClockSource;
				break;
			}//end
			case MTIM_TIMER2:
			{
				break;
			}
			default: break; /* Report an Error */
		}
	}
	else
	{
		/* Report an Error */
	}
}

void MTIM_voidForceOutputCompare(u8 ARG_u8TimerNo)
{
	SET_BIT(TCCR0, FOC0);
}

void MTIM_voidEnableInterrupt(u8 ARG_u8InterruptSource)
{
	if(ARG_u8InterruptSource<=7)
	{
	  SET_BIT(TIMSK, ARG_u8InterruptSource);
	}
	else
	{
		/* Report an Error */
	}
}

void MTIM_voidDisableInterrupt(u8 ARG_u8InterruptSource)
{
	if(ARG_u8InterruptSource<=7)
	{
		CLEAR_BIT(TIMSK, ARG_u8InterruptSource);
	}
	else
	{
		/* Report an Error */
	}
}

void MTIM_voidSetCallback(void (*ARG_pvoidfUserFunction)(void), u8 ARG_u8InterruptSource)
{
	if(ARG_pvoidfUserFunction!=NULL_POINTER)
	{
		switch(ARG_u8InterruptSource)
		{
			case MTIM_INTERRUPT_T0_OVF : MTIM_pvoidfUserFunctionT0OVF  = ARG_pvoidfUserFunction; break;
			case MTIM_INTERRUPT_T0_OCM : MTIM_pvoidfUserFunctionT0OCM  = ARG_pvoidfUserFunction; break;
			case MTIM_INTERRUPT_T1_OVF : MTIM_pvoidfUserFunctionT1OVF  = ARG_pvoidfUserFunction; break;
			case MTIM_INTERRUPT_T1_OCMA: MTIM_pvoidfUserFunctionT1OCMA = ARG_pvoidfUserFunction; break;
			case MTIM_INTERRUPT_T1_OCMB: MTIM_pvoidfUserFunctionT1OCMB = ARG_pvoidfUserFunction; break;
			case MTIM_INTERRUPT_T1_ICU : MTIM_pvoidfUserFunctionT1ICU  = ARG_pvoidfUserFunction; break;
			default: break; /* Report an Error */
		}
	}
	else
	{
		/* Report an Error */
	}
}

void MTIM_voidStartTimer(u8 ARG_u8TimerNo)
{
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0 : TCCR0 = (TCCR0 & 0xF8) | MTIM_u8Timer0Clock; break;
		case MTIM_TIMER1A: TCCR1B = (TCCR1B & 0xF8) | MTIM_u8Timer1Clock; break;
		case MTIM_TIMER1B: TCCR1B = (TCCR1B & 0xF8) | MTIM_u8Timer1Clock; break;
		case MTIM_TIMER2 : break;
		default: break; /* Report an Error */
	}
}

void MTIM_voidStopTimer(u8 ARG_u8TimerNo)
{
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0 : TCCR0 = (TCCR0 & 0xF8) | MTIM_CS_NOCLOCK; break;
		case MTIM_TIMER1A: TCCR1B = (TCCR1B & 0xF8) | MTIM_CS_NOCLOCK; break;
		case MTIM_TIMER1B: TCCR1B = (TCCR1B & 0xF8) | MTIM_CS_NOCLOCK; break;
		case MTIM_TIMER2 : break;
		default: break; /* Report an Error */
	}
}

void MTIM_voidSetTimerValue(u8 ARG_u8TimerNo, u16 ARG_u16Value)
{
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0 : TCNT0 = (u8)ARG_u16Value;	break;
		case MTIM_TIMER1A: TCNT1 = ARG_u16Value;		break;
		case MTIM_TIMER1B: TCNT1 = ARG_u16Value;		break;
		case MTIM_TIMER2 :	break;
		default:	break; /* Report an Error */
	}
}

u16	 MTIM_u16GetTimerValue(u8 ARG_u8TimerNo)
{
	u16 L_u16ReturnValue = 0;
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0 : L_u16ReturnValue = (u16)TCNT0;	break;
		case MTIM_TIMER1A: L_u16ReturnValue = TCNT1;			break;
		case MTIM_TIMER1B: L_u16ReturnValue = TCNT1;			break;
		case MTIM_TIMER2 :	break;
		default:	break; /* Report an Error */
	}
	return L_u16ReturnValue;
}

void MTIM_voidResetTimer(u8 ARG_u8TimerNo)
{
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0 : TCNT0 = 0x00;		break;
		case MTIM_TIMER1A: TCNT1 = 0x0000;	break;
		case MTIM_TIMER1B: TCNT1 = 0x0000;	break;
		case MTIM_TIMER2 :	break;
		default:	break; /* Report an Error */
	}
}

void MTIM_voidSetOCR(u8 ARG_u8TimerNo, u16 ARG_u16OCRValue)
{
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0 : OCR0 = (u8)ARG_u16OCRValue; break;
		case MTIM_TIMER1A: OCR1A = ARG_u16OCRValue;  break;
		case MTIM_TIMER1B: OCR1B = ARG_u16OCRValue;  break;
		case MTIM_TIMER2 : break;
		default: break; /* Report an Error */
	}
}

void MTIM_voidTimerDelay(u8 ARG_u8TimerNo, u32 ARG_u32Delay)
{
	f32 L_f32TickTime, L_f32OVFTime;
	u16 L_u16Prescaler;
	switch(ARG_u8TimerNo)
	{
		case MTIM_TIMER0:
		{
			switch(MTIM_u8Timer0Clock)
			{
				case MTIM_CS_PRESCALER_1:		L_u16Prescaler = 1;		break;
				case MTIM_CS_PRESCALER_8:		L_u16Prescaler = 8;		break;
				case MTIM_CS_PRESCALER_64:		L_u16Prescaler = 64 ;	break;
				case MTIM_CS_PRESCALER_256:		L_u16Prescaler = 256;	break;
				case MTIM_CS_PRESCALER_1024:	L_u16Prescaler = 1024;	break;
				default: break; /* Error */
			}
			L_f32TickTime = (f32)L_u16Prescaler / F_CPU;
			L_f32OVFTime = L_f32TickTime * 256;
			MTIM_u16Timer0OVFCount = ((f32)ARG_u32Delay / 1000) / L_f32OVFTime;
			MTIM_u8Timer0Preload = 256 - ((ARG_u32Delay / 1000) % (u32)L_f32OVFTime);
			TCNT0 = MTIM_u8Timer0Preload;
			break;
		}
		case MTIM_TIMER1A: 
		{
			switch(MTIM_u8Timer1Clock)
			{
				case MTIM_CS_PRESCALER_1:		L_u16Prescaler = 1;		break;
				case MTIM_CS_PRESCALER_8:		L_u16Prescaler = 8;		break;
				case MTIM_CS_PRESCALER_64:		L_u16Prescaler = 64 ;	break;
				case MTIM_CS_PRESCALER_256:		L_u16Prescaler = 256;	break;
				case MTIM_CS_PRESCALER_1024:	L_u16Prescaler = 1024;	break;
				default: break; /* Error */
			}
			L_f32TickTime = (f32)L_u16Prescaler / F_CPU;
			L_f32OVFTime = L_f32TickTime * 65536;
			MTIM_u32Timer1OVFCount = ((f32)ARG_u32Delay / 1000) / L_f32OVFTime;
			MTIM_u16Timer1Preload = 65536 - (ARG_u32Delay % ((u32)(L_f32OVFTime * 1000))) / (L_f32TickTime * 1000);

			TCNT1 = MTIM_u16Timer1Preload;
			break;
		}
		case MTIM_TIMER1B: 
		{
			switch(MTIM_u8Timer1Clock)
			{
				case MTIM_CS_PRESCALER_1:		L_u16Prescaler = 1;		break;
				case MTIM_CS_PRESCALER_8:		L_u16Prescaler = 8;		break;
				case MTIM_CS_PRESCALER_64:		L_u16Prescaler = 64 ;	break;
				case MTIM_CS_PRESCALER_256:		L_u16Prescaler = 256;	break;
				case MTIM_CS_PRESCALER_1024:	L_u16Prescaler = 1024;	break;
				default: break; /* Error */
			}
			L_f32TickTime = (f32)L_u16Prescaler / F_CPU;
			L_f32OVFTime = L_f32TickTime * 65536;
			MTIM_u32Timer1OVFCount = ((f32)ARG_u32Delay / 1000) / L_f32OVFTime;
			MTIM_u16Timer1Preload = 65536 - (ARG_u32Delay % ((u32)(L_f32OVFTime * 1000))) / (L_f32TickTime * 1000);

			TCNT1 = MTIM_u16Timer1Preload;
			break;
		}
		case MTIM_TIMER2: break;
		default: break; /* Error */
	}
}
void MTIM_voidInitICU(u8 ARG_u8EdgeSelect,u8 ARG_u8NoiseCancelerConnection)
{
	if((1>=ARG_u8EdgeSelect)&&(1>=ARG_u8NoiseCancelerConnection))
	{
		TCCR1B = (TCCR1B & 0x3F) | (ARG_u8EdgeSelect<< ICES1) | (ARG_u8NoiseCancelerConnection<<ICNC1);

		TIMSK = (TIMSK & 0xDF) | (1<<TICIE1); // Enable Interrupt ICU

		TCNT1 = 0x0000;	// Clear Counter
	}
}
			
u16 MTIM_u16ReadingICU(void)
{
	return ICR1;
}

void MTIM_voidICUSelectEdge(u8 ARG_u8EdgeSelect)
{
	if(1>=ARG_u8EdgeSelect)
	{
		TCCR1B = (TCCR1B & 0xBF) | (ARG_u8EdgeSelect << ICES1);
	}
	else
	{
		//MISRA
	}
}



void __vector_10(void) __attribute__((signal));
void __vector_10(void)	/* T0 OCM Vector */
{
	
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)	/* T0 OVF Vector */
{
	static volatile u16 L_u16OVFCounter = 0;
	L_u16OVFCounter++;
	if(L_u16OVFCounter == (MTIM_u16Timer0OVFCount+1))
	{
		TCNT0 = MTIM_u8Timer0Preload;
		L_u16OVFCounter = 0;
		if(MTIM_pvoidfUserFunctionT0OVF!=NULL_POINTER)
		{
			(*MTIM_pvoidfUserFunctionT0OVF)();
		}
		else
		{
			/* Do nothing (MISRA) */
		}
	}
	else
	{
		/* Do nothing (MISRA) */
	}
}

void __vector_9(void) __attribute__((signal));
void __vector_9(void)	/* T1 OVF Vector */
{
	static volatile u32 L_u32OVFCounter = 0;
	L_u32OVFCounter++;
	if(L_u32OVFCounter == (MTIM_u32Timer1OVFCount+1))
	{
		TCNT1 = MTIM_u16Timer1Preload;
		L_u32OVFCounter = 0;
		if(MTIM_pvoidfUserFunctionT1OVF!=NULL_POINTER)
		{
			(*MTIM_pvoidfUserFunctionT1OVF)();
		}
		else
		{
			/* Do nothing (MISRA) */
		}
	}
	else
	{
		/* Do nothing (MISRA) */
	}
}

void __vector_8(void) __attribute__((signal));
void __vector_8(void)	/* T1 OCMA Vector */
{
	
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void)	/* T1 OCMB Vector */
{
	
}

void __vector_6(void) __attribute__((signal));
void __vector_6(void)	/* T1 ICU Vector */
{

	if(MTIM_pvoidfUserFunctionT1ICU!=NULL_POINTER)
	{
		(*MTIM_pvoidfUserFunctionT1ICU)();
	}
	else
	{
		/* Do nothing (MISRA) */
	}
}
