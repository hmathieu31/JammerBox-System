/**
 ******************************************************************************
 * @file    	  synchronization.h
 * @brief		  Synchronisation of signals on the STM32
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


#ifndef _SYNCHRONIZATION_H_
#define _SYNCHRONIZATION_H_

//### CRK Synchronisation Function ###	
	
	void sync_CRK(void); 

//### CAM_CRK Synchronisation Function ###
	
	void sync_CAM_CRK (int); 

//### Stalling Detection Function ###

	void Stalling_detection(void);

//### CRK Stalling Detection Function ###

	void Stalling_detection_CRK(void);
//### CAM Stalling Detection Function ###

	void Stalling_detection_CAM(int);    
    
    
// ## CRK synchronisation preparation

	void sync_CRK_preparation(void); 

// ## CAM_CRK synchronisation preparation

	void sync_CAM_CRK_preparation (void); 

// ## Gap to edge calculation

	void gap_to_edge_calculation(void);

// ## Reset CAM_CRK_synch

	void CAM_CRK_synch_reset(int);

// ## Reset CAM_CRK_synch_ahead

	void CAM_CRK_synch_ahead_reset(int);

// ## Set CAM_CRK_synch

	void CAM_CRK_synch_set(int);

// ## IC overflow check

	void IC_overflow_check();


#endif
/*****************************************************************************/
/*****************************************************************************/

