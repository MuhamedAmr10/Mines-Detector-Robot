/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : ULTRA-Sonic         */
/*  Layer      : HAL                 */
/*  Version    : 1.0                 */
/*  Date       : February 11, 2024   */
/*  Last Edit  : N/A                 */
/*************************************/


#include <util/delay.h>

#include "../LIB/LSTD_types.h"
#include "../LIB/LBIT_math.h"

#include "../MCAL/MDIO_interface.h"
#include "../MCAL/MTIM_interface.h"

#include "HUS_interface.h"
#include "HUS_config.h"


static volatile u16 L_u16Distance;
static volatile u8  L_u8ObstecalFlag = HUS_NO_OBSTACLE;


void HUS_voidEcho(void);
void HUS_voidTrig(void);


void HUS_voidInit(void)
{
	//Initializing Timer1A
	MTIM_voidInitTimer(MTIM_TIMER1A,MTIM_MODE_NORMAL,HUS_TIMER1_PRESCALER,MTIM_HWPIN_DISCONNECTED);

	// Set Pin Trig Output
	MDIO_voidSetPinDirection(HUS_TRIG_PORT,HUS_TRIG_PIN,MDIO_OUTPUT);

	// Set Pin Echo InputPullUp
	MDIO_voidSetPinDirection(MDIO_PORTD,6,MDIO_INPUT_PULLUP);

	//Initializing Input Capture Unit
	MTIM_voidInitICU(MTIM_EDGE_SELECT_RISING,MTIM_NOISE_CANCELER_SET);

	//// You should set the Timer1A delay to assign the parameters Timer1OVFCount and  Timer1Preload to execute the HUS_CHECKING_TIME.
	MTIM_voidTimerDelay(MTIM_TIMER1A, HUS_CHECKING_TIME);

    MTIM_voidEnableInterrupt(MTIM_INTERRUPT_T1_OVF);

    //Don't worry ICU Interrupt is Enabled in Trig function
	MTIM_voidSetCallback(HUS_voidEcho,MTIM_INTERRUPT_T1_ICU);
	MTIM_voidSetCallback(HUS_voidTrig,MTIM_INTERRUPT_T1_OVF);

	MTIM_voidStartTimer(MTIM_TIMER1A);
}

u8 HUS_u8GetUltraSonic(void)
{
	return L_u8ObstecalFlag;
}

void HUS_voidEcho(void)
{
	static volatile u8 L_u8EchoCounter=0;
	static volatile u16 L_u16PulseStart;
	static volatile u16 L_u16PulseEnd;

	L_u8EchoCounter++;
	
	/*Pulse is started*/
	if(L_u8EchoCounter % 2 == 1)
	{
		L_u16PulseStart = MTIM_u16ReadingICU();

		MTIM_voidICUSelectEdge(MTIM_EDGE_SELECT_FALLING);
	}
	
	/*Pulse is Ended*/
	else
	{
		L_u16PulseEnd = MTIM_u16ReadingICU();

		MTIM_voidICUSelectEdge(MTIM_EDGE_SELECT_RISING);

		L_u16Distance = (f32)17150 * (L_u16PulseEnd - L_u16PulseStart) * ((f32)HUS_TIMER1_PRESCALER_VALUE / F_CPU);

		if(L_u16Distance <= HUS_MIN_DISTANCE)
		{
			L_u8ObstecalFlag = HUS_OBSTACLE;
		}
		else
		{
			L_u8ObstecalFlag = HUS_NO_OBSTACLE;
		}

		MTIM_voidDisableInterrupt(MTIM_INTERRUPT_T1_ICU);

	}

}

void HUS_voidTrig(void)
{

	MDIO_voidSetPinValue(HUS_TRIG_PORT,HUS_TRIG_PIN,MDIO_HIGH);
	_delay_us(10);
	MDIO_voidSetPinValue(HUS_TRIG_PORT,HUS_TRIG_PIN,MDIO_LOW);

	//// Reset Timer to maximize utilization of the timer range in the measurement process.
	MTIM_voidResetTimer(MTIM_TIMER1A);

	//Enable Input capture unit Interrupt
	MTIM_voidEnableInterrupt(MTIM_INTERRUPT_T1_ICU);

}
