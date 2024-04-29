/*************************************/
/*  Author     : Muhamed Amr         */
/*  SWC        : Metal Detector      */
/*  Layer      : HAL                 */
/*  Version    : 1.0                 */
/*  Date       : March 2, 2024       */
/*  Last Edit  : N/A		         */
/*************************************/

#ifndef HMETDET_CONFIG_H_
#define HMETDET_CONFIG_H_

// choose interrupt num
#define HMETDET_INTERRUPT_NUM		MEXTI_INT0
//#define HMETDET_INTERRUPT_NUM		MEXTI_INT1
//#define HMETDET_INTERRUPT_NUM		MEXTI_INT2

// Choose Mode operation
//#define HMETDET_INTERRUPT_MODE      MEXTI_MODE_IOC
//#define HMETDET_INTERRUPT_MODE      MEXTI_MODE_LOW
//#define HMETDET_INTERRUPT_MODE      MEXTI_MODE_RISING
#define HMETDET_INTERRUPT_MODE      MEXTI_MODE_FALLING

#endif
