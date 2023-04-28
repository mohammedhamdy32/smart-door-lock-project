/*
 * Timer1.c
 *
 *  Created on: Oct 31, 2022
 *      Author: mohammedhamdy32
 */

#include "Timer1.h"
#include "avr/io.h"
#include "common_macros.h"
#include "avr/interrupt.h"

static volatile void (*g_callBackFun)(void)=NULL_PTR;

ISR(TIMER1_COMPA_vect)
{
	(*g_callBackFun)();
}

ISR(TIMER1_OVF_vect)
{
	(*g_callBackFun)();
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCCR1A = (1<<FOC1A) | (1<<FOC1A);  /*Non PWM mode*/

	TCCR1B = Config_Ptr->prescaler;  /*to set the prescaler of timer*/

	TCCR1B |= (Config_Ptr->mode<<WGM12); /*set timer mode Normal or compare mode*/

	TCNT1 = Config_Ptr->initial_value;  /*set initial value of timer*/

	OCR1A = Config_Ptr->compare_value; /*set compare value*/

	TIMSK |= (1<<TICIE1) | (1<<OCIE1A); /*open intrrupt for normal mode and compare */

}

void Timer1_set_initial_value(uint16 a_initial_value )
{
	TCNT1 = a_initial_value;
}

void Timer1_deInit(void)
{
	/*To deinit the timer we close the clock source to timer*/
	CLEAR_BIT(TCCR1B,CS10);
	CLEAR_BIT(TCCR1B,CS11);
	CLEAR_BIT(TCCR1B,CS12);

}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackFun = a_ptr;
}

