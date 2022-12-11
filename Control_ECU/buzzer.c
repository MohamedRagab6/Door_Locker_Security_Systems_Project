/*
 * buzzer.c
 *
 *  Created on: Jul 14, 2022
 *      Author: Mohamed Ragab
 */


#include "buzzer.h"
#include "gpio.h"


/* Description:
 * a function to setup buzzer and setup directions of buzzer pins
 */
void Buzzer_Init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/* Description:
 * a function to turn the buzzer on
 */


void Buzzer_On(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

 /* Description:
  * a function to turn the buzzer off
  */



void Buzzer_Off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

