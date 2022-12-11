/*
 * timer.c
 *
 *  Created on: Jul 13, 2022
 *      Author: Mohamed Ragab
 */
#include "timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use Timer0 Registers */
#include <avr/interrupt.h> /* For OVF mode and COMP mode ISR */
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the timer finished counting using either overflow mode or compare mode */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the timer finished counting using either overflow mode or compare mode */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the Timer driver
 * 	1. set the timer initial value.
 * 	2. Set the timer mode.
 * 	3. set the required clock (prescaler).
 * 	4. enable overflow mode interrupt if selected
 * 	6. set compare value if compare mode was selected
 * 	7. enable compare mode interrupt if compare mode was selected
 * 	8. enable global interrupt
 */
void Timer0_init(TIMER_ConfigType * Config_Ptr)
{
	TCNT0 = Config_Ptr->initial_value; // Set Timer0 initial value

	TCCR0 = (1<<FOC0);   // Non PWM mode FOC0=1

	TCCR0 |= Config_Ptr->mode; // configure mode either overflow mode or compare mode

	TCCR0 |= Config_Ptr->prescaler; // configuration of prescaler

	if(Config_Ptr->mode == OVF_MODE)
	{
		TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
	}
	else if (Config_Ptr->mode == COMP_MODE)
	{
		OCR0 = Config_Ptr->compare_value; // configuration of compare value if comapre mode was selected
		TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
	}

	SREG |= (1<<7); //enable global interrupt
}

/*
 * Description: Function to set the Call Back function address.
*/

void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to disable the Timer0
 */

void Timer0_DeInit(void)
{
	TCCR0 = 0;

}
