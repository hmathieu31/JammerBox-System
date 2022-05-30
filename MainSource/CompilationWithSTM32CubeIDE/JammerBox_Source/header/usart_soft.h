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

#include <stdbool.h>

/* Public functions ----------------------------------------------------------*/

/**
 * @brief Processes the received message. Called in some cases by the main loop and in other cases by the USART interrupt.
 *
 */
void USART_ProcessMessage(void);
/**
 * @brief Send the configuration status through USART
 *
 * @param failure_ident
 * @param failure_conf
 * @param failure_conf_CAM_blank_out
 */
void USART_send_failure_configuration_status(char failure_ident,
		bool failure_conf, bool failure_conf_CAM_blank_out);
/**
 * @brief Reset all 10 temporary char-arrays to '\0'
 *
 */
void Reset_temp_arrays(void);
/**
 * @brief USART Communication error routine. Send error message.
 *
 */
void USART_COM_error(void);

#endif
