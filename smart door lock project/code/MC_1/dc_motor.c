/*
 * dc_motor.c
 *
 *  Created on: Oct 9, 2022
 *      Author: mohammedhamdy32
 */

#include "dc_motor.h"
#include "gpio.h"
#include "common_macros.h"



void DcMotor_Init(void)
{
	GPIO_setupPinDirection(H_BRIDGE_PORT_ID,H_BRIDGR_PIN0, OUTPUT);
	GPIO_setupPinDirection(H_BRIDGE_PORT_ID,H_BRIDGR_PIN1,OUTPUT);  /*set two pins of H bridge */

	GPIO_writePin(H_BRIDGE_PORT_ID , H_BRIDGR_PIN0 , LOGIC_LOW);
	GPIO_writePin(H_BRIDGE_PORT_ID , H_BRIDGR_PIN1 , LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state)
{
    GPIO_writePin(H_BRIDGE_PORT_ID , H_BRIDGR_PIN0 , GET_BIT(state,0));
    GPIO_writePin(H_BRIDGE_PORT_ID , H_BRIDGR_PIN1 , GET_BIT(state,1));
}
