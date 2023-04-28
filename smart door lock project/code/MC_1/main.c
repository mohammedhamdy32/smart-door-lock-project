/*
 * main.c
 *
 *  Created on: Oct 27, 2022
 *      Author: mohammedhamdy32
 */



#include "application.h"


int main(void)
{

	LCD_init();
	UART_configType uart_conf = {DISABLE,ONE_BIT,BIT8,9600};
	UART_init(&uart_conf);

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);


	/*Step 1 to set the password*/
	step_1_set_password();
	/*end of step 1*/

	LCD_clearScreen();

	options chossen_option;
	for(;;)
	{
		LCD_writeString("+ : Open Door");
		LCD_moveCursor(1,0);
		LCD_writeString("- : Change Pass");
		uint8 error_open_door_numbs = 0;
		uint8 error_chang_pass_numbs = 0;

		chossen_option = KEYPAD_getPressedKey();
		_delay_ms(500);
		if(chossen_option==OPEN_DOOR)
		{
			step_3_open_the_door();
		}
		else if(chossen_option==CHANGE_PASS)
		{
			step_4_change_password();
		}

	}
}








