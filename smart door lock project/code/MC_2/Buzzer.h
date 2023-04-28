/*
 * Buzzer.h
 *
 *  Created on: Nov 1, 2022
 *      Author: mohammedhamdy32
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/*liberaries*/
#include "gpio.h"

/*#defines*/
#define BUZZER_PORT_ID    PORTD_ID
#define BUZZER_PIN_ID     PIN7_ID
#define BUZZER_ON         LOGIC_HIGH
#define BUZZER_OFF         LOGIC_LOW

/*Functions prototypes*/
void Buzzer_init();
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
