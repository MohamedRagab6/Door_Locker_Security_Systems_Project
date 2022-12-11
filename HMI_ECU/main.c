/*
 * main.c
 *
 *  Created on: Jul 14, 2022
 *      Author: Mohamed Ragab
 */
#include "app.h"
#include "lcd.h"
#include "uart.h"
#include <util/delay.h>
#include "timer.h"
#include "keypad.h"
int main(void)
{
	uint8 result_of_new_password;
	uint8 result_of_saved_password;
	uint8 counter = 0;
	/* configuration of Uart */
	Uart_ConfigType config_type = {9600,MODE_8_BIT,DISABLED,STOP_BIT_1};

	/*initializing both lcd and Uart modules*/
	LCD_init();
	UART_init(&config_type);
	/*          application                */
	while(1)
	{
		/* this while loop takes the passwords from the user and send the two password to the control ECU
		 * so that the control ECU compares them and there is two possibilities:
		 * 1. if the passwords are matched the control ECU will send by Uart to HMI ECU that the password are matched
		 * so that the lcd screen will display that the passwords are matched.
		 * 2.if the passwords are not matched the control ECU will send by Uart to HMI ECU that the password are NOT matched
		 * so that the lcd screen will display that the passwords are NOT matched.
		 */
		while(1)
		{
			displayWelcomeString();
			displayPasswordOnKeypad();
			displayRepeatPasswordString();
			displayPasswordOnKeypad();
			result_of_new_password = UART_recieveByte();
			if (result_of_new_password == PASSWORDS_ARE_MATCHED)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0 , 0 ,"Passwords are ");
				LCD_moveCursor(1,3);
				LCD_displayString("matched !!! ");
				_delay_ms(2000);
				LCD_clearScreen();
				break;
			}
			else if (result_of_new_password == PASSWORDS_ARE_NOT_MATCHED)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0 , 0 ,"Passwords are not");
				LCD_moveCursor(1,3);
				LCD_displayString("matched !!! ");
				_delay_ms(2000);
				LCD_clearScreen();
			}
		}
		/* this second while loop is responsible for main options and this loop will not be exited unless
		 * the user wants to change password and enters the right password then the loop will be breaked
		 * and the first loop will be executed again.
		 * the main options will be displayed the user can choose either to open door or change password
		 * 1. if the user choose to open door and enters the password correctly the door will be opened.
		 * 2. if the user choose to change password and enters the password correctly he will be allowed
		 * to enter new password.
		 * 3. if the user choose either to open door or change the password and fails to enter password for
		 * three times a buzzer alarm will be initiated.
		 * */
		while(1)
		{
			displayMainOptions();
			uint8 key;
			key = KEYPAD_getPressedKey();
			if(key == '+')
			{
				while(1)
				{
					displayMainOptionsEnterPass();
					displayPasswordOnKeypad();
					result_of_saved_password = UART_recieveByte();
					if (result_of_saved_password  == PASSWORDS_ARE_MATCHED)
					{
						// open door
						UART_sendByte('+');
						UART_sendByte(DOOR_UNLOCKING);
						doorControl();
						break;
					}
					else if (result_of_saved_password  == PASSWORDS_ARE_NOT_MATCHED)
					{
						counter ++;
						if (counter < 3)
						{
							LCD_clearScreen();
							LCD_displayStringRowColumn(0 , 0 ,"pass is not  ");
							LCD_moveCursor(1,3);
							LCD_displayString("correct !!! ");
							_delay_ms(2000);
						}
						if (counter == 3)
						{
							//buzzer alaaaaaarm
							UART_sendByte(BURGULAR);
							buzzerForBurgulars();
							counter = 0;
							break;
						}
					}
				}
			}
			if (key == '-')
			{
				while(1)
				{
					displayMainOptionsEnterPass();
					displayPasswordOnKeypad();
					result_of_saved_password = UART_recieveByte();
					if (result_of_saved_password  == PASSWORDS_ARE_MATCHED)
					{
						UART_sendByte('-');
						break;
					}
					else if (result_of_saved_password  == PASSWORDS_ARE_NOT_MATCHED)
					{
						counter ++;
						if (counter < 3)
						{
							LCD_clearScreen();
							LCD_displayStringRowColumn(0 , 0 ,"pass is not  ");
							LCD_moveCursor(1,3);
							LCD_displayString("correct !!! ");
							_delay_ms(2000);
						}
						if (counter == 3)
						{
							//buzzer alaaaaaarm
							UART_sendByte(BURGULAR);
							buzzerForBurgulars();
							break;
						}
					}
				}
			}
			if ((key == '-') && (counter < 3))
			{
				break;
			}
		}
	}
}

