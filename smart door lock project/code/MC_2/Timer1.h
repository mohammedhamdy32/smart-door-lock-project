/*
 * Timer1.h
 *
 *  Created on: Oct 31, 2022
 *      Author: mohammedhamdy32
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"
/*configuration part*/
typedef enum{
   NO_CLOCK,PRESCALER_1,PRESCALER_8,PRESCALER_64,PRESCALER_256,PRESCALER_1024,EXTERNAL_CLOCK_FALLING_EDGE,EXTERNAL_CLOCK_RISING_EDGE
}Timer1_Prescaler;

typedef enum{
	NORMAL,COMPARE
}Timer1_Mode;

typedef struct {
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;


/*Functions prototypes*/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));
void Timer1_set_initial_value(uint16 a_initial_value ); /*a function to set the initial value of timer */

#endif /* TIMER1_H_ */
