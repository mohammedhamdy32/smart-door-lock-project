/*
 * dc_motor.h
 *
 *  Created on: Oct 9, 2022
 *      Author: mohammedhamdy32
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "gpio.h"

#define H_BRIDGE_PORT_ID       PORTB_ID
#define H_BRIDGR_PIN0          PIN0_ID
#define H_BRIDGR_PIN1          PIN1_ID


/*clockwise or anti_clock_wise*/
typedef enum{
	STOP,CLOCK_WISE,ANTI_CLOCK_WISE
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
