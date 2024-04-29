/*  Author     : Muhamed Amr         */
/*  SWC        : DC MOTOR	         */
/*  Layer      : HAL                 */		
/*  Version    : 1.0                 */
/*  Date       : FEBRAURY 18, 2024   */
/*  Last Edit  : N/P                 */
/*************************************/

#ifndef HMOTOR_INTERFACE_H_
#define HMOTOR_INTERFACE_H_


#define HMOTOR_DIRECTION_RIGHT 		0
#define HMOTOR_DIRECTION_LEFT		1
#define HMOTOR_DIRECTION_FORWARD	2
#define HMOTOR_DIRECTION_BACKWARD	3

void HMOTOR_voidInit(void);
void HMOTOR_voidStartMovement(u8 ARG_u8Direction);
void HMOTOR_voidStopMovement(void);

#endif