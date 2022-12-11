/*
 * app2.h
 *
 *  Created on: Jul 14, 2022
 *      Author: Mohamed Ragab
 */

#ifndef APP2_H_
#define APP2_H_

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
 * a function to receive password from HMI_ECU
 */
void receivePassword( uint8 *pass_ptr);

/*Description:
 * a function to store password in eeprom
 */
void storePassword(uint16 address , uint8 *pass_ptr);


/*Description:
 * a function to get password from eeprom
 */
void getPasswordFromEeprom(uint16 address , uint8 *pass_ptr);

/*Description:
 * a function to check password enterned by the user with the password saved in eeprom
 */
uint8 checkPassword(uint8 *eeprom_pass , uint8 *entered_pass);

/*Description:
 * a function that is responsible for controling door completely if the suer choose to open the door and entered the password
 */
void doorControl(void);
/*Description:
 * a function that is responsible making  a buzzer alarm when a burgular tries to enter the house
 */
void buzzerForBurgulars(void);

#endif /* APP2_H_ */
