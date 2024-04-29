/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : Metal Detector      */
/*  Layer      : HAL                 */
/*  Version    : 1.0                 */
/*  Date       : March 2, 2024       */
/*  Last Edit  : N/A		         */
/*************************************/

#ifndef HMETDET_INTERFACE_H_
#define HMETDET_INTERFACE_H_


#define HMETDET_NO_MINE		0
#define HMETDET_MINE		1


void HMETDET_voidInit(void);
u8 HMETDET_u8GetMetalDetector(void);
void HMETDET_voidClearMineFlag(void);

#endif
