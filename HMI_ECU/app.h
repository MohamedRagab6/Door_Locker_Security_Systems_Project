/*
 * app.h
 *
 *  Created on: Jul 14, 2022
 *      Author: Mohamed Ragab
 */

#ifndef APP_H_
#define APP_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define SIZE_OF_PASSWORD                     5
#define PASSWORDS_ARE_MATCHED                0
#define PASSWORDS_ARE_NOT_MATCHED            1
#define MC_READY                           0x10
#define MC2_READY                          0x20
#define DOOR_UNLOCKING                     0x30
#define BURGULAR                           0x40


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Description:
 * a function to display the first string that asks the user to enter their new password
 */
void displayWelcomeString(void);

/*Description:
 * a function to display a string that asks the user
 * to repeat their password so that we can check if the password is correct
 */
void displayRepeatPasswordString(void);

/*Description:
 * a function to display main options in LCD
 */
void displayMainOptions(void);

/*Description:
 * a function to display string that asks the user to enter their existing password
 */
void displayMainOptionsEnterPass(void);

/*Description:
 * a function that is responsible for taking password from keypad and storing it in an array
 */
void displayPasswordOnKeypad(void);

/*Description:
 * a function that is responsible for displaying door opening and closing strings in lcd and their timing
 */
void doorControl(void);

/*Description:
 * a function that is responsible for displaying buzzer a theif string if the user entered a wrong password
 * for three times.
 */
void buzzerForBurgulars(void);

#endif /* APP_H_ */
