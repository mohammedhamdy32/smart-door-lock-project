/******************************************************************************
 *  application.c                                                             *
 *  Created on: Nov 1, 2022                                                   *
 *  Author: mohammed hamdy halim                                              *
 *  This file contains the functions of application of first Micro_controler  *
 ******************************************************************************/

#include "application.h"

/*************************************************************
 * function name : callback_functon
 * Description : a call back function for ISR if timer1
 * Args   : void
 * return : void
 ************************************************************/
void callback_functon(void)
{
	trim++;
	Timer1_set_initial_value(TIMER_INITIAL_VALUE);
	if(trim==trim_numb)
	{
		g_blocked=FALSE;
		Timer1_deInit();
		trim=0;
	}
}

/*************************************************************
 * function name : write_pass_in_eeprom
 * Description : This function write the global variable
 * password (g_pass) in eeprom
 * Args   : void
 * return : void
 ************************************************************/
void write_pass_in_eeprom(void)
{
	for(int k=0;k<PASS_SIZE;k++)
	{
		EEPROM_writeByte(PASSWORD_ADDERESS+k, g_pass[k]); /* Write 0x0F in the external EEPROM */
		_delay_ms(10);
	}
}


/********************************************************************************
 * function name : read_pass_from_eeprom
 * Description : This function read the password from eeprom
 * Args   : uint8 *a_pass
 * IN : a_pass is an pointer to uint8 which will points to an array
 * contains password
 * return : void
 ***********************************************************************/
void read_pass_from_eeprom(uint8* a_pass)
{
	for(int k=0;k<PASS_SIZE;k++)
	{
		EEPROM_readByte(PASSWORD_ADDERESS+k, &a_pass[k]);
		_delay_ms(10);
	}
}

/********************************************************************************
 * function name : step_1_set_password
 *
 * Description : This function  make step one which takes the password from
 * user then re_take the password again then check if two entered passwords
 * are the same if yes it will send the password to MC2 by UART to save it in eeprom
 * if no will ask again the user to enter the password
 *
 * Args   : void
 * return : void
 ***********************************************************************/
void step_1_set_password(void)
{
	boolean again=TRUE; /*if this variable is true it will loop till it become false*/

	while(again) /*when again is false this means that the two entered passwords are same*/
	{
		LCD_clearScreen();
		LCD_writeString("PLZ enter pass:");
		LCD_sendCommand(LCD_CURSOR_ON);
		LCD_moveCursor(1,0);

		uint8 pressed_button;
		int i;
		for(i=0;i<PASS_SIZE;)
		{
			pressed_button=KEYPAD_getPressedKey();
			_delay_ms(300); /* Press time */

			if(pressed_button=='/') /*when the user wants to delete*/
			{
				if(i!=0) /*if i=0 then there is nothing*/
				{
					i--;
					g_pass[i]=100;
					LCD_moveCursor(1,i);
					LCD_writeChar(' ');
					LCD_moveCursor(1,i);
				}
			}else if(pressed_button == ' ' || pressed_button == '='
					|| pressed_button == '+' || pressed_button == '-')
			{
				/*Do nothing*/
			}
			else
			{
				g_pass[i]=pressed_button;
				//				LCD_integerToString(g_pass[i]);
				LCD_writeChar('*');
				i++;
			}
		}


		uint8 re_pass[5];  /*An array contains the re_enterd password by user*/

		LCD_clearScreen();
		LCD_writeString("PLZ re_enter the");
		LCD_moveCursor(1,0);
		LCD_writeString("same pass:");

		for(int j=0;j<PASS_SIZE;)
		{
			pressed_button=KEYPAD_getPressedKey();
			_delay_ms(300); /* Press time */
			if(pressed_button=='/')
			{
				if(j!=0)/*when the user wants to delete*/
				{
					j--;
					re_pass[j]=100;
					LCD_moveCursor(1,10+j);
					LCD_writeChar(' ');
					LCD_moveCursor(1,10+j);
				}
			}else if(pressed_button=='*')
			{
				break;
			}else if(pressed_button == ' ' || pressed_button == '='
					|| pressed_button == '+' || pressed_button == '-')
			{
				/*Do nothing*/
			}
			else
			{
				re_pass[j]=pressed_button;
				//				LCD_integerToString(re_pass[j]);
				LCD_writeChar('*');
				j++;
			}
		}


		LCD_clearScreen();

		boolean check_pass=TRUE;
		/*check if two passwords are same */
		for(int j=0;j<i;j++)
		{
			if(g_pass[j] != re_pass[j])
			{
				check_pass = FALSE;
				break;
			}
		}


		if(check_pass)
			again=FALSE; /*if the two passwords are not same will loop again*/
		else
			again=TRUE;  /*if the two passwords are same will exit from loop*/

	}

	/*At this point the password is similar to re_password so i will save it in External eeprom*/

	UART_sendByte(SEND_PASSWORD); /*tell the MC2 that he will send a password*/

	for(int j=0;j<PASS_SIZE;j++)
	{
		UART_sendByte(g_pass[j]); /*sending the password to MC2*/
		_delay_ms(10);
	}

}

/********************************************************************************
 * function name : take_password_and_cheak_it
 *
 * Description : This function take a password from user then
 * take the correct password from eeprom if the password is
 * similar eemprom password the function returns true else
 * will returns false
 *
 * Args   : void
 * return : boolean
 ***********************************************************************/
boolean take_password_and_cheak_it(void)
{
	LCD_clearScreen();
	LCD_writeString("PLZ enter pass:");
	LCD_sendCommand(LCD_CURSOR_ON);
	LCD_moveCursor(1,0);

	uint8 pressed_button;
	uint8 pass[5];
	uint8 pass_num=0;
	while(1) /*infinity loop till the user press enter button '*' */
	{
		pressed_button=KEYPAD_getPressedKey();
		_delay_ms(300); /* Press time */
		if(pressed_button=='/')
		{
			if(pass_num!=0)
			{
				pass_num--;
				pass[pass_num]=100;
				LCD_moveCursor(1,pass_num);
				LCD_writeChar(' ');
				LCD_moveCursor(1,pass_num);
			}
		}else if(pressed_button=='*')
		{
			break;
		}else if(pressed_button == ' ' || pressed_button == '='
				|| pressed_button == '+' || pressed_button == '-' || pass_num>4)
		{
			/*Do nothing*/
		}
		else
		{
			pass[pass_num]=pressed_button;
			//			LCD_integerToString(pass[pass_num]);
			LCD_writeChar('*');
			pass_num++;
		}
	}

	if(pass_num != 5)
		return FALSE;


	UART_sendByte(CHEAK_PASSWORD); /*tell MC2 that he will send a password if it's wright sent 1 else send 0*/
	_delay_ms(10);

	for(int j=0;j<PASS_SIZE;j++)
	{
		UART_sendByte( pass[j] ); /*sending the password to MC2*/
		_delay_ms(10);
	}

	boolean is_right_pass;
	is_right_pass = UART_recieveByte(); /*MC2 will sent true or false*/

	return is_right_pass;
}

/********************************************************************************
 * function name : step_4_change_password
 *
 * Description : call take_password_and_cheak_it() function then if it returns true
 * will call step_1_set_password() function to change password if not true will loop
 * ERROR_NUM times to take the password again if none passwords is correct then it will
 * call error_pass() function
 *
 * Args   : void
 * return : boolean
 ***********************************************************************/
void step_4_change_password(void)
{
	boolean is_pass_right;
	uint8 error_num=1;
	is_pass_right=take_password_and_cheak_it();

	if(is_pass_right)
	{
		LCD_clearScreen();
		LCD_writeString("Correct pass");
		_delay_ms(1000);
		step_1_set_password();
	}
	else
	{
		LCD_clearScreen();
		LCD_writeString("Not correct pass");
		_delay_ms(2000);
		while( !take_password_and_cheak_it() ) /*will loop till it's true or break statment*/
		{
			error_num++;
			if(error_num>=ERROR_NUM)
			{
				error_pass();
				return;
			}
			LCD_clearScreen();
			LCD_writeString("Not correct pass");
			_delay_ms(2000);
		}

		LCD_clearScreen();
		LCD_writeString("Correct pass");
		_delay_ms(1000);

		step_1_set_password(); /*if the user enter correct password after wrong one*/

	}
	LCD_clearScreen();
}

/********************************************************************************
 * function name : step_4_open_door
 *
 * Description : This function open the motor for 15sec in Clockwise direction
 * then for another 15sec in Anti_Clockwise direction
 *
 * Args   : void
 * return : void
 ***********************************************************************/
static void open_door(void)
{
	/*motor*/
	Timer1_ConfigType config = {TIMER_INITIAL_VALUE,0,PRESCALER_1024,NORMAL};
	Timer1_setCallBack(callback_functon);
	trim_numb=3; /*to make 15sec*/
	g_blocked=TRUE;
	Timer1_init(&config);

	/*FIRST 15 SEC*/
	UART_sendByte(C_START_MOTOR); /*tell MC2 to open motor in clockwise*/
	_delay_ms(10);
	LCD_clearScreen();
	LCD_writeString("Door is Unlocking");
	while(g_blocked);

	g_blocked=TRUE;
	trim_numb=1; /*to make 5sec*/
	/*SECOND 5 SEC*/
	UART_sendByte(STOP_MOTOR);/*tell MC2 to STOP motor */
	_delay_ms(10);
	Timer1_init(&config); /*init timer again*/
	LCD_clearScreen();
	LCD_writeString("Door is holding");
	while(g_blocked);

	g_blocked=TRUE;
	trim_numb=3; /*to make 15sec*/
	/*SECOND 15 SEC*/
	UART_sendByte(A_START_MOTOR);/*tell MC2 to open motor in anti_clockwise*/
	_delay_ms(10);
	Timer1_init(&config); /*init timer again*/
	LCD_clearScreen();
	LCD_writeString("Door is locking");
	while(g_blocked);

	LCD_clearScreen();
	UART_sendByte(STOP_MOTOR);/*tell MC2 to stop the motor*/
	_delay_ms(10);
}

/********************************************************************************
 * function name :step_3_open_the_door
 *
 * Description : call take_password_and_cheak_it() function then if it returns true
 * will call open_door() function to open the door if not true will loop
 * ERROR_NUM times to take the password again if none passwords is correct then it will
 * call error_pass() function
 *
 * Args   : void
 * return : void
 *******************************************************************************/
void step_3_open_the_door(void)
{

	boolean is_pass_right;
	uint8 error_num=1;
	is_pass_right= take_password_and_cheak_it();

	if(is_pass_right)
	{
		LCD_clearScreen();
		LCD_writeString("Correct pass");
		_delay_ms(1000);
		open_door();
	}else
	{
		LCD_clearScreen();
		LCD_writeString("Not correct pass");
		_delay_ms(2000);
		while( !take_password_and_cheak_it() ) /*will loop till it's true or break statment*/
		{

			error_num++;


			if(error_num>=ERROR_NUM)
			{
				error_pass();
				return;
			}
			LCD_clearScreen();
			LCD_writeString("Not correct pass");
			_delay_ms(2000);
		}
		LCD_clearScreen();
		LCD_writeString("Correct pass");
		_delay_ms(1000);
		open_door(); /*if the user enter correct password after wrong one*/
	}

	LCD_clearScreen();
}

/********************************************************************************
 * function name :error_pass
 *
 * Description : This function open the buzzer and display error massage on LCD
 * for 60 second
 *
 * Args   : void
 * return : void
 *******************************************************************************/

void error_pass(void)
{
	Timer1_ConfigType config = {TIMER_INITIAL_VALUE,0,PRESCALER_1024,NORMAL};
	Timer1_init(&config);
	Timer1_setCallBack(callback_functon);
	trim_numb=12; /*to make 60 sec*/
	g_blocked=TRUE;
	UART_sendByte(BUZZER_ON); /*tells MC2 to open buzzer*/
	_delay_ms(10);
	LCD_clearScreen();
	LCD_writeString("ERROR");
	while(g_blocked); /*will loop till ISR function make g_blocked false*/
	LCD_clearScreen();
	UART_sendByte(BUZZER_OFF); /*tells MC2 to close the buzzer*/
	_delay_ms(10);
}


