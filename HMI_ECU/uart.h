 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Ragab
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	MODE_5_BIT,MODE_6_BIT,MODE_7_BIT,MODE_8_BIT,MODE_9_BIT = 7
}Uart_DataBitsMode;

typedef enum
{
	DISABLED,EVEN_PARITY = 2, ODD_PARITY = 3
}Uart_ParityBitType;
typedef enum
{
	STOP_BIT_1,STOP_BIT_2
}Uart_StopBits;
typedef struct
{
	uint32 baud_rate;
	Uart_DataBitsMode data_bit;
	Uart_ParityBitType parity;
	Uart_StopBits stop_bit;
}Uart_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const Uart_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
