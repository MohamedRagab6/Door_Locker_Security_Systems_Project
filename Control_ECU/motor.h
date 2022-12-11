/*
 * motor.h
 *
 *  Created on: May 24, 2022
 *      Author: Mohamed Ragab
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* The two motor pins*/
#define MOTOR_PINS_PORT_ID                 PORTB_ID
#define IN1                                PIN3_ID
#define IN2                                PIN4_ID
typedef enum
{
	STOP,C_W,A_CW
}DcMotor_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the Motor
 */
void DcMotor_Init(void);
/*
 * Description :
 * Control Motor Movement
 */
void DcMotor_Rotate(DcMotor_State state);

#endif /* MOTOR_H_ */

