/**
 ******************************************************************************
 * @file    	  system_configuration.h
 * @brief   	  Configuration of the system for the input signals
 * 				  Project name	: STM32-Jammerbox
 * 				  Controller	: STM32F103RB
 * @date		  25 May 2022
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

#ifndef _SYSTEM_CONFIGURATION_H_
#define _SYSTEM_CONFIGURATION_H_

/* Private includes --------------------------------------------------------*/
// ### Standard includes ###
#include <stdbool.h>

//### CRK Configuration Function ###	

void CRK_configuration(void);

//### CAM_CRK Configuration Function ###

void CAM_CRK_configuration(void);

//### CAM Configuration Function ###

void CAM_configuration(void);

//### Input Signal Observation ###

void Input_signal_observe(bool output_set);

//### Configuration of Clock Trees for all peripherals ###
void Config_clock_tree(void);

#endif
/*****************************************************************************/
/*****************************************************************************/

