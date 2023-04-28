/*
 * application.h
 *
 *  Created on: Nov 1, 2022
 *      Author: mohammedhamdy32
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

/***************Libraries*************/
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
/***************#defines*******************/
#define PASSWORD_ADDERESS 0x0311
#define PASS_SIZE 5
#define ERROR_NUM 3
#define TIMER_INITIAL_VALUE  26595
#define IS_READY 0xFF
#define SEND_PASSWORD 0xFE
#define CHEAK_PASSWORD 0xFD
#define BUZZER_ON             0xFC
#define BUZZER_OFF            0xFB
#define C_START_MOTOR         0xFA
#define A_START_MOTOR         0xF9
#define STOP_MOTOR            0xF8

/****************Global varibles*********************/
uint8 g_pass[5];  /*An array contains the password which entered by user*/
volatile boolean g_blocked ;
volatile uint8 trim;
volatile uint8 trim_numb;

/******************Functions prototypes***************/
void step_1_set_password(void);
void step_3_open_the_door(void);
boolean take_password_and_cheak_it(void);
void step_4_change_password(void);
void error_pass(void);
void callback_functon(void);


/*enum for door which 43 is asci of + and 45 is asci of - */
typedef enum{
	OPEN_DOOR=43,CHANGE_PASS=45
}options;


#endif /* APPLICATION_H_ */
