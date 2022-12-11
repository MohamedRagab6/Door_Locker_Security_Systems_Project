/*
 * Mini_Project_5_MC1.c
 *
 *  Created on: Jul 13, 2022
 *      Author: Mohamed Ragab
 */
#include "app.h"
#include "common_macros.h"
#include "keypad.h"
#include "lcd.h"
#include "timer.h"
#include "uart.h"
#include <util/delay.h>
#define F_CPU 8000000


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 password[SIZE_OF_PASSWORD];
TIMER_ConfigType timer_config = {COMP_MODE , F_CPU_1024, 0 , 240};
uint8 g_count = 0;
uint8 state = 0;

/*Description:
 * a function to display the first string that asks the user to enter their new password
 */
void displayWelcomeString(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("please enter new");
	LCD_moveCursor(1,0);
	LCD_displayString("pass:");
}
/*Description:
 * a function to display a string that asks the user
 * to repeat their password so that we can check if the password is correct
 */
void displayRepeatPasswordString(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("please re-enter ");
	LCD_moveCursor(1,0);
	LCD_displayString("pass:");
}
/*Description:
 * a function to display string that asks the user to enter their existing password
 */
void displayMainOptionsEnterPass(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("please enter your");
	LCD_moveCursor(1,0);
	LCD_displayString("pass:");
}
/*Description:
 * a function to display main options in LCD
 */
void displayMainOptions(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("+: open door");
	LCD_moveCursor(1,0);
	LCD_displayString("-: change pass");
}
/*Description:
 * a function that is responsible for taking password from keypad and storing it in an array
 */
void displayPasswordOnKeypad(void)
{
	uint8 key;
	LCD_moveCursor(1,5);

	for(uint8 i = 0 ; i < SIZE_OF_PASSWORD; i++)
	{
		key = KEYPAD_getPressedKey();

		if((key >= 0) && (key  <= 9))
		{
			UART_sendByte(key);
			LCD_displayCharacter('*');
			_delay_ms(500);
		}
	}

	while(KEYPAD_getPressedKey() != '='){};

	_delay_ms(500);

}

/*Description:
 * call back function for display locking door for 15 seconds
 */
void LockDoorCallBack (void)
{
	g_count++ ;
	/* the time should be 15 seconds but made it 5 seconds for simulation*/
	if(g_count == (32 * 5)) {
		Timer0_DeInit();
		LCD_clearScreen();
		g_count = 0 ;
		state = 1;
	}

}
/*Description:
 * call back function for display holding motor string for 3 seconds and then display door is locking string
 */
void pauseCallBack (void)
{
	g_count++ ;

	if(g_count == (32*3)) {

		Timer0_DeInit();
		g_count = 0 ;
		LCD_clearScreen();
		LCD_displayStringRowColumn(0 , 0 ,"   Door is  ");
		LCD_moveCursor(1,3);
		LCD_displayString("locking !!! ");

		state = 1;

	}
}
/*Description:
 * a call back function to unlock door string for 15 secs then after then 15 secs door is open string will
 * be displayed
 */
void unlockDoorCallBack(void) {
	g_count++ ;
	/* the time should be 15 seconds but made it 5 seconds for simulation*/
	if(g_count == (32*5)) {
		Timer0_DeInit();
		LCD_clearScreen();
		LCD_displayStringRowColumn(0 , 0 ,"   Door is  ");
		LCD_moveCursor(1,3);
		LCD_displayString("open !!! ");
		g_count = 0 ;

		state = 1;



	}

}
/*Description:
 * a call back function for buzzer alarm string for 1 minute
 */
void buzzerForBurgularsCallBack(void)
{
	/* the time should be 1 minute but made it 3 seconds for simulation*/
	g_count++ ;
	if(g_count == 32*3)
	{
		Timer0_DeInit();
		g_count = 0 ;

		state = 1 ;

	}

}
/*Description:
 * a function that is responsible for displaying door opening and closing strings in lcd and their timing
 */
void doorControl(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0 , 0 ,"   Door is  ");
	LCD_moveCursor(1,3);
	LCD_displayString("unlocking !!! ");

	state = 0;
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


	LCD_clearScreen();
	state = 0;
}
/*Description:
 * a function that is responsible for displaying buzzer a theif string if the user entered a wrong password
 * for three times.
 */
void buzzerForBurgulars(void)
{

	LCD_clearScreen();
	LCD_displayStringRowColumn(0 , 0 ,"theeeeeif!!!");

	Timer0_setCallBack(buzzerForBurgularsCallBack);
	Timer0_init(&timer_config);
	while(state == 0);

	LCD_clearScreen();
	state = 0 ;
}





