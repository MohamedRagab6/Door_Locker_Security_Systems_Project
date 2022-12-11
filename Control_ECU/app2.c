/*
 * app2.c
 *
 *  Created on: Jul 14, 2022
 *      Author: Mohamed Ragab
 */
#include "timer.h"
#include "uart.h"
#include "app2.h"
#include <util/delay.h>
#include "external_eeprom.h"
#include "lcd.h"
#include "motor.h"
#include "buzzer.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
TIMER_ConfigType timer_config = {COMP_MODE , F_CPU_1024, 0 , 240};
uint8 g_count = 0 ;
uint8 state = 0;

/*Description:
 * a function to receive password from HMI_ECU
 */
void receivePassword( uint8 *pass_ptr)
{
	//while(UART_recieveByte() != MC_READY){};
	uint8 receiver;
	for(uint8 i = 0 ; i < SIZE_OF_PASSWORD ; i++)
	{
		receiver = UART_recieveByte();
		pass_ptr[i] = receiver;
	}
}


/*Description:
 * a function to store password in eeprom
 */
void storePassword(uint16 address , uint8 *pass_ptr)
{
	uint8 key;
	for(uint8 i = 0 ; i < SIZE_OF_PASSWORD ; i++)
	{
		key = *(pass_ptr + i);
		EEPROM_writeByte(address + i, key);
		_delay_ms(10);
	}
}

/*Description:
 * a function to get password from eeprom
 */
void getPasswordFromEeprom(uint16 address , uint8 *pass_ptr)
{
	uint8 key;
	for(uint8 i = 0 ; i < SIZE_OF_PASSWORD ; i++)
	{

		EEPROM_readByte(address + i, &key);
		pass_ptr[i] = key;
		_delay_ms(10);
	}
}

/*Description:
 * a function to check password enterned by the user with the password saved in eeprom
 */
uint8 checkPassword(uint8 *first_entered_password , uint8 *second_entered_password)
{

	for(uint8 i = 0 ; i  < SIZE_OF_PASSWORD ; i++)
	{

		if(first_entered_password[i] != second_entered_password[i])

			return PASSWORDS_ARE_NOT_MATCHED ;

	}
	return PASSWORDS_ARE_MATCHED ;
}

/*Description:
 * a call back function to lock door for 15 secs
 */
void LockDoorCallBack (void)
{
	g_count++ ;
	if(g_count == (32 * 5)) {

		Timer0_DeInit();
		DcMotor_Rotate(STOP);
		g_count = 0 ;

		state = 1;
	}

}
/*Description:
 * a call back function to hold motor for 3 secs
 */
void pauseCallBack(void)
{
	g_count++ ;

	if(g_count == (32 * 3)) {

		Timer0_DeInit();
		g_count = 0 ;
		DcMotor_Rotate(A_CW);

		state = 1;

	}
}
/*Description:
 * a call back function to unlock door for 15 secs
 */
void unlockDoorCallBack(void) {
	g_count++ ;

	if(g_count == (32 * 5)) {

		DcMotor_Rotate(STOP);
		g_count = 0 ;
		Timer0_DeInit();

		state = 1;

	}

}
/*Description:
 * a call back function for buzzerForBurgulars that is responsible for giving a buzzer alarm when a burgular tries to open door
 */
void buzzerForBurgularsCallBack(void)
{

	g_count++ ;
	if(g_count == 32*3)
	{
		Timer0_DeInit();
		g_count = 0 ;

		state = 1 ;

	}

}
/*Description:
 * a function that is responsible for controling door completely if the suer choose to open the door and entered the password
 */
void doorControl(void)
{

	DcMotor_Rotate(C_W);

	Timer0_setCallBack(unlockDoorCallBack);
	Timer0_init(&timer_config);
	while(state == 0) ;

	state = 0 ;
	Timer0_setCallBack(pauseCallBack);
	Timer0_init(&timer_config);
	while(state == 0) ;

	state = 0 ;
	Timer0_setCallBack(LockDoorCallBack);
	Timer0_init(&timer_config);
	while(state == 0) ;

	state = 0;
}
/*Description:
 * a function that is responsible making  a buzzer alarm when a burgular tries to enter the house
 */
void buzzerForBurgulars(void)
{

	Buzzer_On();

	Timer0_setCallBack(buzzerForBurgularsCallBack);
	Timer0_init(&timer_config);
	while(state == 0);

	Buzzer_Off();
	LCD_clearScreen();
	state = 0 ;
}

