/*
 *  application.c
 *
 *  Created on: Nov 1, 2022
 *  Author: mohammedhamdy32
 *
 *  This file for functions of MC2
 *
 */

#include "application.h"

/*************************************************************
 * function name : write_pass_in_eeprom
 *
 * Description : This function writes the global password g_pass
 * in eeprom
 *
 * Args   : void
 * return : void
 ************************************************************/
void write_pass_in_eeprom(void)
{
	for(int k=0;k<PASS_SIZE;k++)
	{
		EEPROM_writeByte(PASSWORD_ADDERESS+k, g_pass[k]);
		_delay_ms(10);
	}
	LCD_moveCursor(1,0);
}

/*************************************************************
 * function name : read_pass_from_eeprom
 *
 * Description : This function read the paswword from eeprom and copy
 * it in a_temp_pass variable
 *
 * in eeprom
 *
 * Args   : void
 * return : void
 ************************************************************/
static void read_pass_from_eeprom(uint8* a_temp_pass)
{
	for(int k=0;k<PASS_SIZE;k++)
	{
		EEPROM_readByte(PASSWORD_ADDERESS+k, &a_temp_pass[k]);
		_delay_ms(10);
	}
}

/*************************************************************
 * function name : compare_eeprom_pass_with_your_pass
 *
 * Description : This function compares the password passed in arrgument
 * with password in eeprom and returns true if they are same and false if not
 *
 *
 * Args   : void
 * return : boolean
 ************************************************************/
boolean compare_eeprom_pass_with_your_pass(uint8 *a_your_pass)
{
	int i;
	uint8 eemprom_pass[PASS_SIZE];
	read_pass_from_eeprom(eemprom_pass);

	LCD_integerToString(eemprom_pass[0]);
	LCD_integerToString(a_your_pass[0]);

	for(i=0;i<PASS_SIZE;i++)
	{
		if(eemprom_pass[i] != a_your_pass[i] )
			return FALSE; /*will return false if they are not same*/
	}

	return TRUE; /*will return true if two passwords are same*/
}





