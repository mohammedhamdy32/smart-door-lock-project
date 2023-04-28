/*
 * keypad.h
 *
 *  Created on: Oct 10, 2022
 *      Author: mohammedhamdy32
 */

#include "gpio.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEYPAD_ROWS_NUMB      4
#define KEYPAD_COLUMN_NUMB    4

#define BUTTON_IS_PRESSED     0

/*Row port and it's start pin*/
#define KEYPAD_ROW_PORT_ID          PORTB_ID
#define KEYPAD_ROW_START_PIN_ID     PIN0_ID

/*Column port and it's start pin*/
#define KEYPAD_COL_PORT_ID          PORTA_ID
#define KEYPAD_COL_START_PIN_ID     PIN0_ID


/*To set the value of buttons*/
#define BUTTON1         '/'
#define BUTTON2          9
#define BUTTON3          8
#define BUTTON4          7
#define BUTTON5          '*'
#define BUTTON6          6
#define BUTTON7          5
#define BUTTON8          4
#define BUTTON9          '-'
#define BUTTON10          3
#define BUTTON11          2
#define BUTTON12          1
#define BUTTON13          '+'
#define BUTTON14           '='
#define BUTTON15           0
#define BUTTON16           ' '





uint8 KEYPAD_getPressedKey();


#endif /* KEYPAD_H_ */
