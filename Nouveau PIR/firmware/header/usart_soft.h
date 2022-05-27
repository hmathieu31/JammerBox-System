/**
 ******************************************************************************
 * @file    	  usart_soft.h
 * @brief		  Functions to use the USART specific to the Jammerbox Project
 * 				  Project name	: STM32-Jammerbox
 * 				  Controller	: STM32F103RB
 * @date		  May 27, 2022
 ******************************************************************************
 * @attention
 *
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


#ifndef _USART_H_
#define _USART_H_

// ### Functions ###

	// ## Usart1 Init ##

	void Usart1Init(void);

	//### USART Receive Function ###

	void USART_receive(void);

	//### USART Send Configuration Status Function ###
	
	void USART_send_failure_configuration_status(char, bool, bool);

	//## USART Reset temporary char-arrays

	void Reset_temp_arrays(void);

	//## USART COM Error Function

	void USART_COM_error(void);
	
#endif
/*****************************************************************************/
/*****************************************************************************/
