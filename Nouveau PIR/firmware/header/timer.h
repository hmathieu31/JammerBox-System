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

<<<<<<< HEAD
// ### Functions ###

	// ## Timer1 Init **Prescaler: 256; Communication validation** 

	void Timer1Init(void);

	// ## Timer2 Init **Prescaler: 64; CRK Synchronization; tooth time** 

	void Timer2Init(void);

	// ## Timer3 Init **Prescaler: 256; CAM Synchronization; segment time** 

	void Timer3Init(void); 

	// ## Timer4 Init **Prescaler: 64; CRK_NO_SIG/CAM_delay**
	
	void Timer4Init(void);

	// ## Timer5 Init **CAM Prescaler: 256; CAM_NO_SIG**
	
	void Timer5Init(void);

	// ## Timer6 Init **Prescaler: 8; CAM_PER/CRK_TOOTH_PER(start-value)**

	void Timer6Init(void);

	// ## Timer7 Init **Prescaler: 8; CAM_PER/CRK_TOOTH_PER(pulse duration)**

	void Timer7Init(void);

	// ## Timer8 Init **Prescaler: 64; CRK_RUN_OUT/CAM_delay**

	void Timer8Init(void);

	// ## Timer9 Init **Prescaler: 64; CAM_delay**
	
	void Timer9Init(void);

	//## Timer2Reset **Prescaler: 64; CRK Synchronization; tooth time** 

	void Timer2Reset(void);

	//## Timer3Reset **Prescaler: 256; CAM Synchronization; segment time** 

	void Timer3Reset(void); 

	//## Timer4Reset **Prescaler: 64; CRK_NO_SIG/CAM_delay** 

	void Timer4Reset(void);

	//## Timer5Reset **CAM Prescaler: 256; CAM_NO_SIG** 

	void Timer5Reset(void);

	//## Timer9Reset **Prescaler: 64; CAM_delay** 

	void Timer9Reset(void);

#endif
/*****************************************************************************/
/*****************************************************************************/
=======
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

#endif

>>>>>>> 80b24cb2 (⚡ Implement the STM32 software  (#157))
