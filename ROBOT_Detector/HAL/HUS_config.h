/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : ULTRA-Sonic         */
/*  Layer      : HAL                 */
/*  Version    : 1.0                 */
/*  Date       : February 11, 2024   */
/*  Last Edit  : N/A                 */
/*************************************/

#ifndef HUS_CONFIG_H_
#define HUS_CONFIG_H_

#define HUS_TRIG_PORT					MDIO_PORTA
#define HUS_TRIG_PIN					0

#define HUS_MIN_DISTANCE				30	 	   /* cm  */

#define HUS_CHECKING_TIME				250	       /* ms */


// Choose "PreScaler"  			Recommended to choose prescaler 8 to increase the maximum measured distance.

//#define HUS_TIMER1_PRESCALER           MTIM_CS_PRESCALER_1
#define HUS_TIMER1_PRESCALER           MTIM_CS_PRESCALER_8
//#define HUS_TIMER1_PRESCALER           MTIM_CS_PRESCALER_64
//#define HUS_TIMER1_PRESCALER           MTIM_CS_PRESCALER_256
//#define HUS_TIMER1_PRESCALER           MTIM_CS_PRESCALER_1024

// Choose "Prescaler value" 	As Distance = (34300 cm/s)*(TimerCounts)*(Precaler/(2*F_CPU))

//#define HUS_TIMER1_PRESCALER_VALUE 	   1
#define HUS_TIMER1_PRESCALER_VALUE 	   8
//#define HUS_TIMER1_PRESCALER_VALUE 	   64
//#define HUS_TIMER1_PRESCALER_VALUE 	   256
//#define HUS_TIMER1_PRESCALER_VALUE 	   1024

//Note that if you choose a value that is not equivalent to prescaler the Distance equation will be wrong

#endif
