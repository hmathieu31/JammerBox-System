/**
 ******************************************************************************
 * @file    	  failures.h
 * @brief   	  Implementation of all failures cases.
 * 				  Project name	: STM32-Jammerbox
 * 				  Controller	: STM32F103RB
 * @date		  May 24, 2022
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


#ifndef INC_FAILURES_H_
#define INC_FAILURES_H_

void output_CRK_no_failure(void);
void output_CAM_no_failure(int);
void output_CRK(char);
void output_CAM(char ,int);
void failure_processing(char);
void CRK_RUN_OUT(void);
void output_CRK_RUN_OUT(void);
void CRK_RUN_OUT_reset(void);
void output_CAM_PER(int);
void CAM_PER_reset(void);
void output_CRK_TOOTH_PER(void);
void CRK_TOOTH_PER(void);
void CRK_TOOTH_PER_reset(void);
void output_CRK_TOOTH_OFF(void);
void CRK_TOOTH_OFF_reset(void);
void output_CRK_GAP_NOT_DET(void);
void CRK_GAP_NOT_DET_reset(void);
void output_SEG_ADP_ER_LIM(void);
void SEG_ADP_ER_LIM_reset(void);
void output_CRK_pulse_duration(void);
void CRK_pulse_duration_reset(void);
void output_POSN_ENG_STST(void);
void POSN_ENG_STST_reset(void);
void output_SC_CAM_CRK(int);
void SC_CAM_CRK_reset(void);
void output_CAM_PAT_ERR(int);
void CAM_PAT_ERR_reset();
void Output_CAM_delay (int);
void CAM_delay (int);
void CAM_delay_counter(int);
void CAM_delay_reset (void);
void failure_reset(void);
void failure_synch_reset(char);
double former_teeth_time_calculation(long, unsigned int, int);
double former_teeth_time_calculation_output(long, unsigned int, int);

#endif /* INC_FAILURES_H_ */
