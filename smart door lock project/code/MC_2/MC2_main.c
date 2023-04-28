/*
 * MC2_main.c
 *
 *  Created on: Nov 2, 2022
 *      Author: mohammedhamdy32
 */


#include "application.h"

int main(void)
{

	/******************INIT eeprom************************/
	UART_configType uart_conf = {DISABLE,ONE_BIT,BIT8,9600};
	UART_init(&uart_conf);
	/******************INIT i2c************************/
	TWI_ConfigType twi_conf = {0b00000010,400000};
	TWI_init(&twi_conf); /*init I2C to send password to eeprom*/
	/******************INIT Buzzer*********************/
	Buzzer_init();
   /*******************INIT motor*********************/
   DcMotor_Init();

	uint8 recieved_byte;

	for(;;)
	{
		recieved_byte = UART_recieveByte();

		if(recieved_byte == SEND_PASSWORD)/*MC2 will Writes the recived password in eeprom if SEND_PASSWORD byte is recived */
		{
			for(int j=0;j<PASS_SIZE;j++)
			{
				g_pass[j] = UART_recieveByte();
				_delay_ms(10);
				LCD_integerToString(g_pass[j]);
			}

			write_pass_in_eeprom();

		}
		else if(recieved_byte == CHEAK_PASSWORD)/*MC2 will check the recived password if CHEAK_PASSWORD byte is recived */
		{
			LCD_writeChar('i');
			uint8 pass[PASS_SIZE];
			for(int j=0;j<PASS_SIZE;j++)
			{
				pass[j] = UART_recieveByte();
				_delay_ms(10);
				LCD_integerToString(pass[j]);
			}

			boolean is_right_pass;
			is_right_pass = compare_eeprom_pass_with_your_pass(pass);

			UART_sendByte(is_right_pass);

		}else if(recieved_byte == BUZZER_ON) /*MC2 will open buzzer if BUZZER_ON byte is recived */
		{
			LCD_writeString("B ON");
			Buzzer_on();
		}else if(recieved_byte == BUZZER_OFF) /*MC2 will close buzzer if BUZZER_ON byte is recived */
		{
			Buzzer_off();
			LCD_writeString("B OFF");
		}else if( recieved_byte==C_START_MOTOR )/*MC2 will open motor in clock wise if C_START_MOTOR byte is recived */
		{
            DcMotor_Rotate(CLOCK_WISE);
		}
		else if(recieved_byte==A_START_MOTOR) /*MC2 will open motor in anti clock wise if A_START_MOTOR byte is recived */
		{
            DcMotor_Rotate(ANTI_CLOCK_WISE);
			LCD_writeString("stop");
		}
		else if(recieved_byte == STOP_MOTOR ) /*MC2 will open motor if STOP_MOTOR byte is recived */
		{
            DcMotor_Rotate(STOP);
		}

	}


}
