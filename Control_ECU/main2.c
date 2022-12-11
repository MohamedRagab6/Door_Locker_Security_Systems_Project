/*
 * main2.c
 *
 *  Created on: Jul 16, 2022
 *      Author: Mohamed Ragab
 */
#include "app2.h"
#include "uart.h"
#include "twi.h"
#include "timer.h"
#include "motor.h"
#include <util/delay.h>
#include "buzzer.h"
int main(void)
{
	/*variables to store passwords*/
	uint8 first_entered_password[5];
	uint8 second_repeated_password[5];
	uint8 password_in_eeprom[5];
	uint8 main_options_password[5];
	uint8 result_for_new_password;
	uint8 result_for_saved_password;
	uint8 counter = 0 ;
	uint8 state;
	/*configurations for timer, uart and i2c*/
	Uart_ConfigType config_type = {9600,MODE_8_BIT,DISABLED,STOP_BIT_1};
	TWI_ConfigType config = {FAST_MODE,0b00000100};

	/*initialization for motor,uart,buzzer and i2c*/
	DcMotor_Init();
	UART_init(&config_type);
	TWI_init(&config);
	Buzzer_Init();
	/*                  application              */
	while(1)
	{
		/* this while loop is responsible for receiving the two passwords from the HMI ECU and comparing them
		 * and there are two cases:
		 * 1. if the passwords are matched the control ECU will tell HMI ECU that and will store the password
		 * in eeprom
		 * 2. if the passwords are NOT matched  the control ECU will tell HMI ECU so that the HMI ECU takes
		 *  input again from user
		 *  */
		while(1)
		{
			receivePassword(first_entered_password);
			receivePassword(second_repeated_password);
			result_for_new_password = checkPassword(first_entered_password,second_repeated_password);
			if (result_for_new_password == PASSWORDS_ARE_MATCHED)
			{
				 UART_sendByte(PASSWORDS_ARE_MATCHED);
				 storePassword(0x0311 ,first_entered_password);
				 getPasswordFromEeprom(0x0311 , password_in_eeprom);
				 break;
			}
			else if (result_for_new_password == PASSWORDS_ARE_NOT_MATCHED)
			{
				UART_sendByte(PASSWORDS_ARE_NOT_MATCHED);
			}
		}
		/*this loop is responsible for taking password from main options menu and this loop will not be
		 * exited unless the suer wants to change password and enters the correct password.
		 * 1. if the user choose to open the door and entered the password correctly the the door will be opened
		 * 2. if the user choose to change password and enters the password correctly he will be allowed
		 * to enter new password.
		 * 3. if the user choose either to open door or change the password and fails to enter password for
		 * three times a buzzer alarm will be initiated.
		 */
		while(1)
		{

			receivePassword(main_options_password);
			result_for_saved_password = checkPassword(main_options_password,password_in_eeprom);
			if (result_for_saved_password == PASSWORDS_ARE_MATCHED)
			{
				UART_sendByte(PASSWORDS_ARE_MATCHED);
				state = UART_recieveByte();
				if (state == '+')
				{
				/*door opening*/
				while(UART_recieveByte() != DOOR_UNLOCKING){};
				doorControl();
				}
				else if(state == '-')
				{
					break;
				}
			}
			else if (result_for_saved_password == PASSWORDS_ARE_NOT_MATCHED)
			{
				UART_sendByte(PASSWORDS_ARE_NOT_MATCHED);
				counter++;
				if (counter == 3)
				{
					/*buzzer alaaaaaaarm*/
					while(UART_recieveByte() != BURGULAR){};
					buzzerForBurgulars();
					counter = 0;
				}
			}
		}
	}
}
