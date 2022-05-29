/**
 ******************************************************************************
 * @file    	  timer.h
 * @brief   	  Timer management functions and implementation of the software
 * 				  timer.
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

#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

/* External variables --------------------------------------------------------*/
extern int TIM_Soft_CounterOverflow;
extern int TIM_Soft_Counting;

/* Private functions ---------------------------------------------------------*/

// Set period of Systick timer
void Systick_SetPeriod(float);

void SysTickInit(void);

void TIM1_Reset(void);

void TIM2_Reset(void);

void TIM_Soft_Start(void);

void TIM_Soft_Stop(void);

void TIM_Soft_Reset(void);

int TIM_Soft_GetCounter(void);

int GetTimestamp(void);

#endif

