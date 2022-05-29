/**
 ******************************************************************************
 * @file    	  timer.c
 * @brief   	  Timer management functions and implementation of the software
 * 				  timer
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

/* Private includes ---------------------------------------------------------*/
#include "../../JammerBox_Source/header/timer.h"

#include <stdbool.h>
#include <stdint.h>

// ### Hardware includes ###
#include "tim.h"

#define SYSTICK_US_PERIOD 120000


/* External variables -------------------------------------------------------*/
extern unsigned long timer_overflow_CRK;
extern unsigned long timer_overflow_CAM;
extern unsigned long timer_overflow_CRK_failure;
extern unsigned long timer_overflow_CAM_failure;
extern unsigned long timer_overflow_CAM_REF_CRK;

/* Private variables --------------------------------------------------------*/
int TIM_Soft_StartTick = 0;
int TIM_Soft_StopTick = 0;
int TIM_Soft_CounterOverflow = 0;
int TIM_Soft_Counting = 0; //boolean TODO: Convert use correct type
int TIM_Soft_TicksCounted = 0;

/* Private functions --------------------------------------------------------*/

// Returns the computed value, 0 if impossible
/**
 * @brief This function sets the different parameters to set the period of the systic.
 * 
 * @param Duration_us Duration of the systic period in microseconds
 */
void Systick_SetPeriod(float Duration_us)
{
	uint32_t Nb_Reload;
	float Nb_Reload_Float;
	float Real_Duration_us;
	float In_Freq;

	In_Freq = SystemCoreClock;

	Nb_Reload_Float = Duration_us * In_Freq / 1000000.0;
	Nb_Reload = (float) Nb_Reload_Float;
	Real_Duration_us = ((float) Nb_Reload) / In_Freq * 1000000.0;

	// Limit testing
	// No prescaler
	SysTick->CTRL = (SysTick->CTRL) | 1 << 2;
	if (Nb_Reload_Float >= 16777215.0)  // 2^24-1 max
	{
		// Fix the prescaler to 8
		SysTick->CTRL = (SysTick->CTRL) & ~(1 << 2);
		Nb_Reload_Float = Duration_us * In_Freq / 8000000.0;
		Nb_Reload = (float) Nb_Reload_Float;
		Real_Duration_us = ((float) Nb_Reload) / In_Freq * 8000000.0;
	}

	if (Nb_Reload_Float >= 16777215.0)  // 2^24-1 max
	{
		Real_Duration_us = 0.0;
	}

	SysTick->LOAD = Nb_Reload;
}

/**
 * @brief This function initialise the systic timer. 
 * Using a presacler of 64. It is used for CRK_RUN_OUT and CAM-delay
 * 
 */
void SysTickInit(void)
{
	// FCPU with PLL = 73,7 MHz
	// Fcy: 36,85 MHz
	// 36,85 Mhz/ 64 = 575,78 kHz = 1.73 µs

	// Disable timer
	SysTick->CTRL &= ~1;
	// Systick is not subject to any idle mode
	SysTick->VAL = (2 ^ 24) - 1; // Clear Systick count (Systick is count down and on 24 bits)
	// Set to a 105ms period
	Systick_SetPeriod(105000.0);
	NVIC_SetPriority(SysTick_IRQn, 2);  // Set Systick interrupt priority
	// No need to reset flag in systick
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;  // Enable Systick interrupt
}

/**
 * @brief This function resets the Timer 1. 
 * Using a presacler of 64. It is used for CRK Synchronization and tooth time
 */
void TIM1_Reset(void)
{
	HAL_TIM_Base_Stop_IT(&htim1);
	__HAL_TIM_SET_COUNTER(&htim1, 0); // Reset TIM1 counter value
	HAL_TIM_Base_Start_IT(&htim1);
	
}

//## TIM2_Reset **Prescaler: 256; CAM Synchronization; segment time**
/**
 * @brief This function resets the Timer 1. 
 * Using a presacler of 256. It is used for CAM Synchronization and segment time.
 */
void TIM2_Reset(void)
{
	HAL_TIM_Base_Stop_IT(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2, 0); // Reset TIM2 counter value
	HAL_TIM_Base_Start_IT(&htim2);
	timer_overflow_CAM = 0;
}

/**
 * @brief This function starts the soft timer, the software encoded timer based on the systic
 * 
 */
void TIM_Soft_Start(void)
{
	if (TIM_Soft_Counting == false)
	{
		TIM_Soft_StartTick = HAL_GetTick(); // Systick is used as based
		// for the software-encoded timer
		TIM_Soft_Counting = 1;
	}
}

/**
 * @brief   This function stops the soft timer.
 * 
 */
void TIM_Soft_Stop(void)
{
	if (TIM_Soft_Counting)
	{
		TIM_Soft_Counting = 0;
		TIM_Soft_StopTick =  HAL_GetTick();
		TIM_Soft_TicksCounted += ((TIM_Soft_StopTick - TIM_Soft_StartTick)
				+ TIM_Soft_CounterOverflow * 62999)
				% 62999;
		TIM_Soft_CounterOverflow = 0;
	}
}

/**
 * @brief This function resets the soft timer parameters.
 * 
 */
void TIM_Soft_Reset(void)
{
	TIM_Soft_StartTick = 0;
	TIM_Soft_StopTick = 0;
	TIM_Soft_TicksCounted = 0;
	TIM_Soft_CounterOverflow = 0;
}

/**
 * @brief This function returns the value of the counter of the soft timer.
 * 
 * @return int : TIM_Soft_TicksCounted : Number of ticks counted.
 */
int TIM_Soft_GetCounter(void)
{
	if (TIM_Soft_Counting)
	{
		return ((TIM_Soft_StopTick - TIM_Soft_StartTick)
				+ TIM_Soft_CounterOverflow * 62999)
				% 62999;
	}
	else
	{
		return TIM_Soft_TicksCounted;
	}
}

/**
 * @brief Get the Timestamp object
 * 
 * @return uint32_t : returns a timestamp in microseconds
 */
static inline uint32_t GetTimestamp() {
    uint32_t nb_of_periods;
    uint32_t val;
    uint32_t load;

	nb_of_periods = HAL_GetTick();
	val = SysTick->VAL;
	load = SysTick->LOAD;

    // Do not factorize for precision purposes
    return nb_of_periods * SYSTICK_US_PERIOD + (load + 1 - val) * SYSTICK_US_PERIOD / (load + 1);
}
