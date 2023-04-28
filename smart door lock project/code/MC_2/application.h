/*
 * application.h
 *
 *  Created on: Nov 1, 2022
 *      Author: mohammedhamdy32
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "keypad.h"
#include "lcd.h"
#include "avr/delay.h"
#include "UART.h"
#include "Timer1.h"
#include "std_types.h"
#include "avr/io.h"
#include "external_eeprom.h"
#include "twi.h"
#include "Buzzer.h"
#include "UART.h"
#include "dc_motor.h"

#define PASSWORD_ADDERESS     0x0311
#define PASS_SIZE             5
#define ERROR_NUM             2
#define TIMER_INITIAL_VALUE   26595
#define IS_READY              0xFF
#define SEND_PASSWORD         0xFE
#define CHEAK_PASSWORD        0xFD
#define BUZZER_ON             0xFC
#define BUZZER_OFF            0xFB
#define C_START_MOTOR         0xFA
#define A_START_MOTOR         0xF9
#define STOP_MOTOR            0xF8

uint8 g_pass[5];  /*An array contains the password which entered by user*/

/*Functions prototypes*/
void write_pass_in_eeprom(void);
static void read_pass_from_eeprom(uint8* a_temp_pass);
boolean compare_eeprom_pass_with_your_pass(uint8 *a_your_pass);

typedef enum{
	OPEN_DOOR=43,CHANGE_PASS=45
}options;


#endif /* APPLICATION_H_ */
