/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : ULTRA-Sonic         */
/*  Layer      : HAL                 */
/*  Version    : 1.0                 */
/*  Date       : February 11, 2024   */
/*  Last Edit  : N/A                 */
/*************************************/

#ifndef HUS_INTERFACE_H_
#define HUS_INTERFACE_H_


#define HUS_NO_OBSTACLE				0
#define HUS_OBSTACLE				1


#ifndef F_CPU
#define F_CPU	8000000UL
#warning F_CPU not define. Assuming 8MHz Clock.
#endif


u8 HUS_u8GetUltraSonic(void);
void HUS_voidInit(void);

#endif 
