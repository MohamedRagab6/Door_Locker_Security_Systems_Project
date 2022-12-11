/*
 * buzzer.h
 *
 *  Created on: Jul 14, 2022
 *      Author: Mohamed Ragab
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID				PORTB_ID
#define BUZZER_PIN_ID				PIN5_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description:
 * a function to setup buzzer and setup directions of buzzer pins
 */
void Buzzer_Init(void);

/* Description:
 * a function to turn the buzzer on
 */

void Buzzer_On(void);

/* Description:
 * a function to turn the buzzer off
 */

void Buzzer_Off(void);



#endif /* BUZZER_H_ */
