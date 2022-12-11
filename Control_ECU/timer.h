/*
 * timer.h
 *
 *  Created on: Jul 13, 2022
 *      Author: Mohamed Ragab
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	OVF_MODE = 0,COMP_MODE = 0x08
}TIMER_Mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}TIMER_Prescaler;

typedef struct
{
	TIMER_Mode mode;
	TIMER_Prescaler prescaler;
	uint8 initial_value;
	uint8 compare_value;
}TIMER_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
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
void Timer0_init(TIMER_ConfigType * Config_Ptr);
/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void));
/*
 * Description: Function to disable the Timer0
 */
void Timer0_DeInit(void);
#endif /* TIMER_H_ */
