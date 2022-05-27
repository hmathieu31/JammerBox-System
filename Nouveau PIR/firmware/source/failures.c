/**
 ******************************************************************************
 * @file    	  failures.c
 * @brief   	  Implementation of all failures cases.
 * 				  Project name	: STM32-Jammerbox
 * 				  Controller	: STM32F103RB
 * @date		  24.05.2022
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

/* Basic includes ------------------------------------------------------------*/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Hardware includes ---------------------------------------------------------*/
#include "stm32f1xx_hal.h"


/* Program includes ----------------------------------------------------------*/
#include "failures.h"
#include "tim.h"

/* Variables -----------------------------------------------------------------*/

extern bool CRK_signal;
extern bool CAM_signal[2];

/* Synchronisation variables */
extern unsigned long timer_overflow_CRK;
extern unsigned long T_TOOTH_RAW;
extern unsigned int teeth_count_CAM_CRK_synch;
extern unsigned int teeth_count_CAM_CRK_synch_ahead;
extern unsigned int teeth_count_CRK;
extern unsigned int number_real_teeth;
extern unsigned int number_teeth_between_gaps;
extern unsigned int number_segments_CRK;
extern unsigned int first_seg_start_tooth;
extern int number_teeth_CRK;
extern int number_gap;
extern int number_miss_teeth;
extern int number_teeth_CAM;
extern double tdc_to_gap;
extern double first_seg_angle;
extern double revolution_CRK;
extern bool engine_start;
extern bool CRK_synch;
extern bool CRK_CAM_synch;
extern bool CAM_CRK_synch_ahead[2];
extern char active_CAM_edges[2];
extern int teeth_count_overall;

//** CAM variables **
extern double filter_time_CAM[2];

//** Timer overflow values for CRK and CAM - failures **
extern unsigned long timer_overflow_CRK_failure;
extern unsigned long timer_overflow_CAM_failure;
extern unsigned long timer_overflow_CAM_REF_CRK;

//** Failure treatment **
extern char failure_identify;
extern int active_cam_failure;

//** Labels indicating failure status **
extern bool failure_active;
extern bool failure_active_CAM_blank_out;
extern bool failure_set;
extern bool failure_passed;
extern bool failure_waiting;

//** CRK_RUN_OUT **
extern char sc_type_CRK_RUN_OUT;
extern unsigned int teeth_counter_CRK_RUN_OUT;
extern unsigned int angle_to_start_failure_CRK_RUN_OUT;
extern unsigned int failure_period_CRK_RUN_OUT;
extern unsigned int counter_TDC0;
extern int period_counter_CRK_RUN_OUT;
extern double difference_to_edge_TDC0;
extern double difference_to_edge_failure_start;
extern bool detected_TDC0;
extern bool counter_ready;
extern bool counter_reset;
extern bool TDC_on_edge;
extern bool start_on_edge_CRK_RUN_OUT;

//** CAM_PER **
extern unsigned int number_edges_CAM_PER;
extern unsigned int counter_CAM_PER[2];
extern double microsecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER;
extern bool all_active_edges_CAM_PER;
extern char active_edges_CAM_PER;

//** CRK_TOOTH_PER **
extern unsigned int start_tooth_CRK_TOOTH_PER;
extern unsigned int number_pulses_CRK_TOOTH_PER;
extern unsigned int engine_revolutions_CRK_TOOTH_PER;
extern unsigned int teeth_counter_CRK_TOOTH_PER;
extern unsigned int revolution_counter_CRK_TOOTH_PER;
extern long double const milli_second_per_timer_tick_CRK;
extern double mycrosecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER;
extern double calculation_factor_CRK_TOOTH_PER;

//** CAM_DELAY(CAM_TOOTH_OFF / CAM_REF_CRK / CAM_SYN / CAM_SYN_CRK) **
extern unsigned int number_processing_edges_CAM_delay[2];
extern unsigned int shift_counter_CAM_delay[2][6];
extern const int edges_beetween_shift_CAM_delay;
extern double angle_to_edge_CAM_delay[2][6];
extern double delay_angle_CAM_delay;
extern double delay_factor_CAM_delay;
extern bool timer_active_CAM_delay[2];
extern bool interrupt_check_CAM_delay[2];

//** CAM_REF_CRK **
extern unsigned int delay_counter_CAM_REF_CRK;
extern long double angle_time_to_start_failure_CAM_REF_CRK;  // Value Delay (ms or �CRK)
extern double difference_to_edge_failure_start_CAM_REF_CRK;
extern char delay_type_CAM_REF_CRK;  // t: time / c: �CRK

//** CRK_TOOTH_OFF **
extern unsigned int number_tooth_off;
extern unsigned int number_teeth_between_tooth_off;
extern unsigned int teeth_counter_CRK_TOOTH_OFF;
extern unsigned int counter_tooth_off;               // counts the number of tooth that were skipped
extern unsigned int counter_gap_left_CRK_TOOTH_OFF;  // counts the number of gap left before a full CRK rotation

//** CRK_GAP_NOT_DET **
extern unsigned int teeth_counter_CRK_GAP_NOT_DET;
extern unsigned int timer_Counter_CRK_GAP_NOT_DET;

//** SEG_ADP_ER_LIM **
extern unsigned int teeth_counter_SEG_ADP_ER_LIM;
extern unsigned int timer_Counter_SEG_ADP_ER_LIM;
extern double crk_delay_SEG_ADP_ER_LIM;

//** CRK_PLS_ORNG **
extern double crk_pulse_duration_CRK_PLS_ORNG;

//** POSN_ENG_STST_LOSS **
extern unsigned int crk_teeth_off_POSN_ENG_STST;
extern unsigned int counter_POSN_ENG_STST;

//** CAM_PAT_ERR **
extern unsigned int active_CAM_edges_counter[2];

//** SC_CAM_CRK **
extern unsigned int sc_type_SC_CAM_CRK;

// TIM5 variables
extern int tim5_Counting;
extern int tim5_CounterOverflow;

/* Public functions -------------------------------------------------------- */

//## Output Function CRK
void output_CRK(char failure_ident)  // processed at each CRK edge
{
    switch (failure_ident) {
        case '1': {
            break;
        }
        case '2': {
            break;
        }
        case '3': {
            break;
        }
        case '4':  // CRK_RUN_OUT
        {
            output_CRK_RUN_OUT();
            break;
        }
        case '6':  // CRK_TOOTH_PER
        {
            output_CRK_TOOTH_PER();

            break;
        }
        case '7':  // CAM_TOOTH_OFF
        {
            CAM_delay_counter(active_cam_failure);

            break;
        }
        case '8':  // CAM_PAT_ERR
        {
            break;
        }
        case '9':  // CAM_SYN_CRK
        {
            if (active_cam_failure == 2) {
                CAM_delay_counter(0);  // for CAM1
                CAM_delay_counter(1);  // for CAM2
            } else if (active_cam_failure == 1) {
                CAM_delay_counter(1);  // for CAM2
            } else {
                CAM_delay_counter(0);  // for CAM1
            }
            break;
        }
        case 'a':  //
        {
            break;
        }
        case 'b':  //
        {
            break;
        }
        case 'f':  //
        {
            break;
        }
        case 'h':  // CRK_TOOTH_OFF
        {
            output_CRK_TOOTH_OFF();
            break;
        }
        case 'i':  // CRK_GAP_NOT_DET
        {
            output_CRK_GAP_NOT_DET();
            break;
        }
        case 'j':  // SEG_ADP_ER_LIM
        {
            output_SEG_ADP_ER_LIM();
            break;
        }
        case 'k':  // CRK_pulse_duration
        {
            output_CRK_pulse_duration();
            break;
        }
        case 'l':  // POSN_ENG_STST
        {
            output_POSN_ENG_STST();
            break;
        }
        case 'm':  // SC_CAM_CRK
        {
            output_SC_CAM_CRK(active_cam_failure);
            break;
        }
        default:
            break;
    }
}

//## Output Function CAM
void output_CAM(char failure_ident, int cam_id) {
    if ((cam_id == active_cam_failure) || active_cam_failure == 2) {
        switch (failure_ident) {
            case '0':  // NO_FAILURE
            {
                output_CAM_no_failure(cam_id);  // no failure to be put out on CAM
                break;
            }
            case '1':  // CRK_NO_SIG
            {
                output_CAM_no_failure(cam_id);  // no failure to be put out on CAM
                break;
            }
            case '2':  // CAM_NO_SIG
            {
                output_CAM_no_failure(cam_id);
                break;
            }
            case '3':  // CRK/CAM_NO_SIG
            {
                output_CAM_no_failure(cam_id);
                break;
            }
            case '4':  // CRK_RUN_OUT
            {
                output_CAM_no_failure(cam_id);  // no failure to be put out on CAM
                break;
            }
            case '5':  // CAM_PER
            {
                output_CAM_no_failure(cam_id);
                output_CAM_PER(cam_id);
                break;
            }
            case '6':  // CRK_TOOTH_PER
            {
                output_CAM_no_failure(cam_id);  // no failure to be put out on CAM
                break;
            }
            case '7':  //
            {
                break;
            }
            case '8':  // CAM_PAT_ERR
            {
                output_CAM_PAT_ERR(cam_id);
                break;
            }
            case '9':  // CAM_SYN_CRK
            {
                Output_CAM_delay(cam_id);
                break;
            }
            case 'a':  //
            {
                break;
            }
            case 'b':  // CRK_SHO_LEVEL
            {
                output_CAM_no_failure(cam_id);  // no failure to be put out on CAM
                break;
            }
            case 'f':  // CRK_TOOTH_NR
            {
                output_CAM_no_failure(cam_id);  // no failure to be put out on CAM
                break;
            }
            case 'h':  // CRK_TOOTH_OFF
            {
                output_CAM_no_failure(cam_id);
                break;
            }
            case 'i':  // CRK_Gap_Not_Det
            {
                output_CAM_no_failure(cam_id);
                break;
            }
            case 'j':  // SEG_ADP_ER_LIM
            {
                output_CAM_no_failure(cam_id);
                break;
            }
            case 'k':  // CRK_pulse_duration
            {
                output_CAM_no_failure(cam_id);
                break;
            }
            case 'l':  // POSN_ENG_STST
            {
                output_CAM_no_failure(cam_id);
                break;
            }
            case 'm':  // SC_CAM_CRK
            {
                output_SC_CAM_CRK(cam_id);
                break;
            }
            default:
                break;
        }
    } else {
        output_CAM_no_failure(cam_id);  // no failure to be put out on CAM
    }
}

//## Output_CRK no Failure Function
/**
 * @brief This function outputs the CRK signal in its normal state (no failure).
 * This simply consists in reproducing the CRK signal as is.
 *
 */
void output_CRK_no_failure(void) {
    if (CRK_signal == true) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    }
}

//## Output_CAM no Failure Function
void output_CAM_no_failure(int cam_id) {
    if (CAM_signal[cam_id] == true) {
        if (cam_id == 0) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
        }
    } else {
        if (cam_id == 0) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
        } else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
        }
    }
}

//### Output CRK: RUN_OUT ###
void output_CRK_RUN_OUT(void) {
    if (CRK_signal == true) {
        if (teeth_count_CRK != number_teeth_between_gaps) {  // count the teeths on th rising edge
            teeth_counter_CRK_RUN_OUT = teeth_count_CRK + 1;
        } else if (teeth_count_CRK == number_teeth_between_gaps) {  // if we reched a gap
            teeth_counter_CRK_RUN_OUT = 1;
        }
    }

    if (failure_active == true) {                                                                                                 // if failure is active
        if ((teeth_counter_CRK_RUN_OUT * revolution_CRK) >= (failure_period_CRK_RUN_OUT + angle_to_start_failure_CRK_RUN_OUT)) {  // once we have reached the failure end
            failure_active = false;
            failure_passed = true;
        } else {  // if failure is active
            if (sc_type_CRK_RUN_OUT == 'g') {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);  // set CRK as low
            } else if (sc_type_CRK_RUN_OUT == 'b') {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);  // set CRK as hight
            }
        }
    } else if (failure_passed == true) {  // once the failure finished have a normal output
        if (teeth_count_CRK == number_teeth_between_gaps) {
            failure_passed = false;
        }
        teeth_counter_CRK_RUN_OUT = 1;
        output_CRK_no_failure();
    } else {
        if ((angle_to_start_failure_CRK_RUN_OUT < (teeth_counter_CRK_RUN_OUT * revolution_CRK)) && ((teeth_counter_CRK_RUN_OUT * revolution_CRK) < (angle_to_start_failure_CRK_RUN_OUT + failure_period_CRK_RUN_OUT))) {  // if we are past the the angle of fairue start and still in the failure period
            failure_active = true;
        } else {
        }
        output_CRK_no_failure();
    }
}

//### CRK_RUN_OUT_reset ###
void CRK_RUN_OUT_reset(void) {
    failure_active = false;
    failure_passed = false;
    period_counter_CRK_RUN_OUT = 0;
}

//## Output CAM: CAM_PER
void output_CAM_PER(int cam_id) {
    if (active_edges_CAM_PER == 'b') {
        if (cam_id == 0) {          // For CAM1
            HAL_TIM_Base_Stop(&htim3); // Enable Timer3 (formerly Timer6 on microchip)
            __HAL_TIM_SET_AUTORELOAD(&htim3, (filter_time_CAM[cam_id] / 2.0 - 5) / microsecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER);
        } else {                    // For CAM2
            HAL_TIM_Base_Stop(&htim4);  // Enable Timer4 (formerly Timer7 on microchip)
            __HAL_TIM_SET_AUTORELOAD(&htim4, (filter_time_CAM[cam_id] / 2.0 - 5) / microsecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER);
        }
    } else if (active_edges_CAM_PER == 'f' && CAM_signal[cam_id] == false) {
        if (cam_id == 0) {          // For CAM1
            HAL_TIM_Base_Stop(&htim3);  // Enable Timer3 (formerly Timer6 on microchip)
            __HAL_TIM_SET_AUTORELOAD(&htim3, (filter_time_CAM[cam_id] / 2.0 - 5) / microsecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER);
        } else {                    // For CAM2
            HAL_TIM_Base_Stop(&htim4);  // Enable Timer4 (formerly Timer7 on microchip)
            __HAL_TIM_SET_AUTORELOAD(&htim4, (filter_time_CAM[cam_id] / 2.0 - 5) / microsecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER);
        }
    } else if (active_edges_CAM_PER == 'r' && CAM_signal[cam_id] == true) {
        if (cam_id == 0) {          // For CAM1
            HAL_TIM_Base_Stop(&htim3);   // Enable Timer3 (formerly Timer6 on microchip)
            __HAL_TIM_SET_AUTORELOAD(&htim3, (filter_time_CAM[cam_id] / 2.0 - 5) / microsecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER);
        } else {                    // For CAM2
            HAL_TIM_Base_Stop(&htim4); // Enable Timer4 (formerly Timer7 on microchip)
            __HAL_TIM_SET_AUTORELOAD(&htim4, (filter_time_CAM[cam_id] / 2.0 - 5) / microsecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER);
        }
    }
}

//## CAM_PER_reset
void CAM_PER_reset(void) {
    if (HAL_TIM_Base_GetState(&htim3) == HAL_TIM_STATE_BUSY)  // if TIM3 is busy
    {
        HAL_TIM_Base_Stop_IT(&htim3);
        __HAL_TIM_SET_COUNTER(&htim3, 0);  // disable and reset the timer
    }

    if (HAL_TIM_Base_GetState(&htim3) == HAL_TIM_STATE_BUSY)  // if timer4 is enabled
    {
        HAL_TIM_Base_Stop_IT(&htim4);
        __HAL_TIM_SET_COUNTER(&htim4, 0);  // disable and reset the timer
    }

	MX_TIM3_Init();
	MX_TIM4_Init();
    counter_CAM_PER[0] = 0;
    counter_CAM_PER[1] = 0;
}

//## Output CRK: CRK_TOOTH_PER
void output_CRK_TOOTH_PER(void) {
    if (CRK_signal == false) {
        HAL_TIM_Base_Start(&htim3); // Enable timer3 (formerly Timer6 on microchip)     
    }
}

//## CRK_TOOTH_PER_reset
void CRK_TOOTH_PER_reset(void) {
    if (HAL_TIM_Base_GetState(&htim3) == HAL_TIM_STATE_BUSY)  // if timer3 is enabled
    {
        HAL_TIM_Base_Stop(&htim3);
        __HAL_TIM_SET_COUNTER(&htim3,0);// disable and reset the timer

    }

    if (HAL_TIM_Base_GetState(&htim4) == HAL_TIM_STATE_BUSY)  // if timer4 is enabled
    {
        HAL_TIM_Base_Stop(&htim4);
        __HAL_TIM_SET_COUNTER(&htim4,0);  // disable and reset the timer
    }

    failure_set = false;
    failure_active = false;
}

//## Output CAM_delay: CAM_TOOTH_OFF / CAM_REF_CRK / CAM_SYN / CAM_SYN_CRK
void Output_CAM_delay(int cam_id) {
    if (failure_identify == '9') {
        switch (active_CAM_edges[cam_id]) {
            case ('b'): {
                if (engine_start == true) {
                    HAL_ResumeTick();  // Enable the SysTick (formerly Timer8 on microchip) till the first falling CRK_edge
                    timer_active_CAM_delay[cam_id] = true;
                } else {
                    output_CAM_no_failure(cam_id);
                }

                break;
            }
            case ('f'): {
                if (CAM_signal[cam_id] == false) {
                    if (engine_start == true) {
                        HAL_ResumeTick();  // Enable the SysTick (formerly Timer8 on microchip) till the first falling CRK_edge
                        timer_active_CAM_delay[cam_id] = true;

                        if (failure_active == false) {
                            failure_active = true;
                        }
                    } else {
                        output_CAM_no_failure(cam_id);
                    }
                } else if (CAM_signal[cam_id] == true && failure_active == false) {
                    if (cam_id == 0) {
                        // Toggle GPIOA11
                        if (HAL_GPIO_ReadPin(GPIOA, 11) == GPIO_PIN_RESET) {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                        } else {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                        }

                    } else if (cam_id == 1) {
                        // Toggle GPIOA6
                        if (HAL_GPIO_ReadPin(GPIOA, 6) == GPIO_PIN_RESET) {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                        } else {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
                        }
                    }
                }
                break;
            }
            case ('r'): {
                if (CAM_signal[cam_id] == true) {
                    if (engine_start == true) {
                        HAL_ResumeTick();  // Enable the SysTick (formerly Timer8 on microchip) till the first falling CRK_edge
                        timer_active_CAM_delay[cam_id] = true;

                        if (failure_active == false) {
                            failure_active = true;
                        }
                    } else {
                        output_CAM_no_failure(cam_id);
                    }
                } else if (CAM_signal[cam_id] == false && failure_active == false) {
                    if (cam_id == 0) {
                        // Toggle GPIO5
                        if (HAL_GPIO_ReadPin(GPIOA, 11) == GPIO_PIN_RESET) {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                        } else {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                        }
                    } else if (cam_id == 1) {
                        // Toggle GPIO6
                        if (HAL_GPIO_ReadPin(GPIOA, 6) == GPIO_PIN_RESET) {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                        } else {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
                        }
                    }
                }
                break;
            }
            default: {
                output_CAM_no_failure(cam_id);
                break;
            }
        }
    } else {
        output_CAM_no_failure(cam_id);
    }
}

//## CAM_delay: CAM_TOOTH_OFF / CAM_REF_CRK / CAM_SYN / CAM_SYN_CRK
void CAM_delay(int cam_id) {
    if (tim5_Counting) {
        double former_teeth_time;
        former_teeth_time = former_teeth_time_calculation(T_TOOTH_RAW,
                                                          teeth_count_CRK, number_miss_teeth);
        if (((double)TIM_Soft_GetCounter() / former_teeth_time) * revolution_CRK >= (revolution_CRK / 2.0)) {
            if (cam_id == 0) {
                if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET)
                {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                } else {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                }
            } else if (cam_id == 1) {
                if (HAL_GPIO_ReadPin(GPIOA, 6) == GPIO_PIN_SET) {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
                } else {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                }
            }
            TIM_Soft_Stop();
            TIM_Soft_Reset();
        }
    }

    if (timer_active_CAM_delay[cam_id] == true && number_processing_edges_CAM_delay[cam_id] == 0) {
        interrupt_check_CAM_delay[cam_id] = false;

        double former_teeth_time;
        former_teeth_time = former_teeth_time_calculation(T_TOOTH_RAW,
                                                          teeth_count_CRK, number_miss_teeth);

        if (((double)HAL_GetTick() / former_teeth_time) * revolution_CRK >= (delay_angle_CAM_delay * delay_factor_CAM_delay)) {
            HAL_ResumeTick();
            uwtick = (2 ^ 24) - 1;  //TODO: Handle systick here
            timer_active_CAM_delay[cam_id] = false;

            if (interrupt_check_CAM_delay[cam_id] == false) {
                if (cam_id == 0) {
                    if (HAL_GPIO_ReadPin(GPIOA, 11) == GPIO_PIN_RESET) {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                    } else {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                    };
                } else if (cam_id == 1) {
                    if (HAL_GPIO_ReadPin(GPIOA, 6) == GPIO_PIN_RESET) {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
                    } else {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                    };
                }

                if (active_CAM_edges[cam_id] == 'r' || active_CAM_edges[cam_id] == 'f') {
                    HAL_ResumeTick();
                }
            }
        }
    } else if (number_processing_edges_CAM_delay[cam_id] > 0) {
        int i = 0;
        int count = 0;

        double former_teeth_time;
        former_teeth_time = former_teeth_time_calculation(T_TOOTH_RAW,
                                                          teeth_count_CRK, number_miss_teeth);

        for (i = 0; i < edges_beetween_shift_CAM_delay; i++) {
            if (count == number_processing_edges_CAM_delay[cam_id]) {
                break;
            }

            if (shift_counter_CAM_delay[cam_id][i] != 0) {
                if (angle_to_edge_CAM_delay[cam_id][i] + ((double)(shift_counter_CAM_delay[cam_id][i] - 1) + ((double)(TIM_Soft_GetCounter() + timer_overflow_CRK * (unsigned long)(TIM2->ARR))) / former_teeth_time) * revolution_CRK >= (delay_angle_CAM_delay * delay_factor_CAM_delay))  // Aurait été plus propre avec un getAutoreload
                {
                    shift_counter_CAM_delay[cam_id][i] = 0;
                    angle_to_edge_CAM_delay[cam_id][i] = 0;
                    number_processing_edges_CAM_delay[cam_id]--;
                    if (cam_id == 0) {
                        if (HAL_GPIO_ReadPin(GPIOA, 11) == GPIO_PIN_RESET) {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                        } else {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                        };
                    } else if (cam_id == 1) {
                        if (HAL_GPIO_ReadPin(GPIOA, 6) == GPIO_PIN_RESET) {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
                        } else {
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                        };
                    }

                    if (active_CAM_edges[cam_id] == 'r' || active_CAM_edges[cam_id] == 'f') {
                        TIM_Soft_Start();
                    }

                    break;
                }

                count++;
            }
        }
    }
}

//## CAM_delay_counter: CAM_TOOTH_OFF / CAM_REF_CRK / CAM_SYN / CAM_SYN_CRK
void CAM_delay_counter(int cam_id) {
    if ((failure_identify == '9') && CRK_signal == false) {
        interrupt_check_CAM_delay[cam_id] = true;

        if (timer_active_CAM_delay[cam_id] == true) {
            int i = 0;
            int count = 0;

            if (number_processing_edges_CAM_delay[cam_id] != 0) {
                for (i = 0; i < edges_beetween_shift_CAM_delay; i++)  // edges_beetween_shift_CAM_delay = 6
                {
                    if (count == number_processing_edges_CAM_delay[cam_id]) {
                        break;
                    }

                    if (shift_counter_CAM_delay[cam_id][i] != 0) {
                        if (teeth_count_CRK == number_teeth_between_gaps) {
                            shift_counter_CAM_delay[cam_id][i] =
                                shift_counter_CAM_delay[cam_id][i] + number_miss_teeth + 1;
                        } else {
                            shift_counter_CAM_delay[cam_id][i]++;
                        }

                        count++;
                    }
                }
            }

            i = 0;

            double former_teeth_time;
            former_teeth_time = former_teeth_time_calculation_output(
                T_TOOTH_RAW, teeth_count_CRK, number_miss_teeth);

            for (i = 0; i < edges_beetween_shift_CAM_delay; i++) {
                if (shift_counter_CAM_delay[cam_id][i] == 0) {
                    shift_counter_CAM_delay[cam_id][i] = 1;
                    angle_to_edge_CAM_delay[cam_id][i] =
                        ((double)(HAL_GetTick()) / former_teeth_time) * revolution_CRK;
                    HAL_SuspendTick(); //TODO: Systick
                    SysTick->VAL = (2 ^ 24) - 1;
                    timer_active_CAM_delay[cam_id] = false;
                    number_processing_edges_CAM_delay[cam_id]++;
                    break;
                }
            }
        } else if (number_processing_edges_CAM_delay[cam_id] != 0) {
            int count = 0;
            int i = 0;

            for (i = 0; i < edges_beetween_shift_CAM_delay; i++) {
                if (count == number_processing_edges_CAM_delay[cam_id]) {
                    break;
                }

                if (shift_counter_CAM_delay[cam_id][i] != 0) {
                    if (teeth_count_CRK == number_teeth_between_gaps) {
                        shift_counter_CAM_delay[cam_id][i] =
                            shift_counter_CAM_delay[cam_id][i] + number_miss_teeth + 1;
                    } else {
                        shift_counter_CAM_delay[cam_id][i]++;
                    }

                    count++;
                }
            }
        }
    }
}

//## CAM_delay reset
void CAM_delay_reset(void) {
    failure_active = false;
    failure_set = false;
    HAL_SuspendTick();  // disable SysTick
    SysTick->VAL = (2 ^ 24) - 1;            // clear systick counter
    TIM_Soft_Stop();
    TIM_Soft_Reset();

    number_processing_edges_CAM_delay[0] = 0;
    number_processing_edges_CAM_delay[1] = 0;
    timer_active_CAM_delay[0] = false;
    timer_active_CAM_delay[1] = false;
    delay_counter_CAM_REF_CRK = 0;

    int i;

    for (i = 0; i < edges_beetween_shift_CAM_delay; i++) {
        shift_counter_CAM_delay[0][i] = 0;
        shift_counter_CAM_delay[1][i] = 0;
    }

    i = 0;

    for (i = 0; i < edges_beetween_shift_CAM_delay; i++) {
        angle_to_edge_CAM_delay[0][i] = 0;
        angle_to_edge_CAM_delay[1][i] = 0;
    }
}

//##Output_CRK_TOOTH_OFF
void output_CRK_TOOTH_OFF(void) {
    number_teeth_between_tooth_off = number_teeth_between_gaps / number_tooth_off;

    // only count a tooth when CRK rising edge
    if (CRK_signal == true) {
        if (teeth_count_CRK != number_teeth_between_gaps) {
            teeth_counter_CRK_TOOTH_OFF = teeth_count_CRK + 1;
        } else if (teeth_count_CRK == number_teeth_between_gaps) {
            teeth_counter_CRK_TOOTH_OFF = 1;
            counter_gap_left_CRK_TOOTH_OFF++;
            counter_tooth_off = 0;  // reset at every gap

            if (counter_gap_left_CRK_TOOTH_OFF == number_gap) {  // if we made a full rotation
                counter_gap_left_CRK_TOOTH_OFF = 0;
            }
        }
    }

    if (failure_active == true) {
        if (CRK_signal == false) {  // if failure active and the Crk is set to 0 set Crk output at 1 to miss a tooth
            failure_passed = true;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        } else if (failure_passed == true) {  // a tooth has been skiped
            failure_passed = false;
            failure_active = false;
            counter_tooth_off++;
        }

    } else {
        if (((teeth_counter_CRK_TOOTH_OFF % number_teeth_between_tooth_off) == ((number_teeth_between_tooth_off / 2) + 1)) && (CRK_signal == true)) {  // if we passed a tooth and this tooth is separated by the number_teeth_between_tooth_off
            if ((counter_gap_left_CRK_TOOTH_OFF == 0) && (counter_tooth_off < ((number_tooth_off / number_gap) + (number_tooth_off % number_gap)))) {
                failure_active = true;
            } else if (counter_tooth_off < (number_tooth_off / number_gap)) {
                failure_active = true;
            } else {
                output_CRK_no_failure();
            }

        } else {
        }
    }
}

//##CRK_TOOTH_OFF_reset
void CRK_TOOTH_OFF_reset(void) {
    failure_active = false;
    number_teeth_between_tooth_off = 0;
}

//##Output_CRK_GAP_NOT_DET
void output_CRK_GAP_NOT_DET(void) {
    if (CRK_signal == true) {
        if (teeth_count_CRK != number_teeth_between_gaps) {
            teeth_counter_CRK_GAP_NOT_DET = teeth_count_CRK + 1;
        } else if (teeth_count_CRK == number_teeth_between_gaps) {
            teeth_counter_CRK_GAP_NOT_DET = 1;
        }
    }

    if (CRK_synch == false) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    } else if (CRK_synch == true) {
        output_CRK_no_failure();

        if ((teeth_counter_CRK_GAP_NOT_DET == number_teeth_between_gaps) && failure_active == false) {
            failure_active = true;
            SysTick_SetPeriod(T_TOOTH_RAW * 1.5);  // to be in the midle of the gap

        } else if ((failure_active == true) && (CRK_signal == true)) {
            HAL_ResumeTick();
        }
    }
}

//## CRK_GAP_NOT_DET_reset
void CRK_GAP_NOT_DET_reset(void) {
    failure_active_CAM_blank_out = false;
    failure_active = false;
    SysTickInit();
}

//## Output_SEG_ADP_ER_LIM
void output_SEG_ADP_ER_LIM(void) {
    if (CRK_signal == true) {
        if (teeth_count_CRK != number_teeth_between_gaps) {
            teeth_counter_SEG_ADP_ER_LIM = teeth_count_CRK + 1;
        } else if (teeth_count_CRK == number_teeth_between_gaps) {
            teeth_counter_SEG_ADP_ER_LIM = 1;
        }
    }

    if ((failure_active == true) && (CRK_signal == false)) {  // on the falling edge of the CRK start the delay timer
        HAL_TIM_Base_Start(&htim4);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    } else if ((failure_active == true) && (CRK_signal == true)) {
        if (failure_passed == true) {  // if failure on the falling edge of the CRK is already set
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
            HAL_TIM_Base_Start(&htim4);
        } else {  // if failure on the falling edge of the CRK is still not set, this happens a lot on lower frquency
            failure_waiting = true;
        }
    } else {
        output_CRK_no_failure();
    }

    if (teeth_counter_SEG_ADP_ER_LIM == (((720 / (number_segments_CRK * revolution_CRK)) + (first_seg_angle / revolution_CRK) + (int)(tdc_to_gap / revolution_CRK) + 1))) {  // if we are one tooth befor the end of the first segment
        double delayTimer = crk_delay_SEG_ADP_ER_LIM * (T_TOOTH_RAW / revolution_CRK);
        __HAL_TIM_SET_AUTORELOAD(&htim4, 18 * ((delayTimer * 8) + 1) - 1); // PR7 =  delayTimer * 8
        // set de delay for the timer, times 8 because the timer 7 has a prescale of 1:8 and T_TOOTH_RAW has 1:64
        failure_active = true;
    }
}

//## SEG_ADP_ER_LIM_reset
void SEG_ADP_ER_LIM_reset(void) {
    failure_active = false;
    failure_passed = false;
    failure_waiting = false;
    Timer4Init();
    SysTickInit();
    timer_Counter_SEG_ADP_ER_LIM = 0;
}

//## Output_CRK_pulse_duration
void output_CRK_pulse_duration(void) {
    if (CRK_signal == false) {
        HAL_TIM_Base_Start(&htim4); // start the timer4 (formerly TIM7 on microchip)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    }
}

//## CRK_PLS_ORNG_reset
void CRK_pulse_duration_reset(void) {
    MX_TIM3_Init();
    failure_active = false;
}

//## Output_POSN_ENG_STST
void output_POSN_ENG_STST(void) {
    if ((CRK_signal == false) && (failure_active == true)) {
        counter_POSN_ENG_STST++;  // counte the teeth'
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);   // skip the tooth

        if (counter_POSN_ENG_STST >= crk_teeth_off_POSN_ENG_STST) {  // if number of teeth skip is done stop failure
            failure_active = false;
            counter_POSN_ENG_STST = 0;
        }
    } else if (failure_active == false) {
        output_CRK_no_failure();
    }
}

//## POSN_ENG_STST_LOSS_reset
void POSN_ENG_STST_reset(void) {
    failure_active = false;
}

//## Output_CAM_PAT_ERR

void output_CAM_PAT_ERR(int cam_id) {
    switch (active_CAM_edges[cam_id]) {
        case 'b': {
            active_CAM_edges_counter[cam_id]++;
            if (active_CAM_edges_counter[cam_id] >= 7) {  // after an abitrary number of CAM edges skip the next falling edge to generate the failure
                if (CAM_signal[cam_id] == false) {
                    if (cam_id == 0) {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                    } else {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                    }
                } else if (CAM_signal[cam_id] == true) {
                    if (cam_id == 0) {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                    } else {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
                    }
                }
                active_CAM_edges_counter[cam_id] = 0;
            } else {
                output_CAM_no_failure(cam_id);
            }
            break;
        }
        case 'f': {
            if (CAM_signal[cam_id] == false) {
                active_CAM_edges_counter[cam_id]++;
                if (active_CAM_edges_counter[cam_id] >= 7) {  // after an abitrary number of CAM edges skip this edge in output to generate the failure
                    active_CAM_edges_counter[cam_id] = 0;
                    if (cam_id == 0) {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                    } else {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                    }
                } else {
                    output_CAM_no_failure(cam_id);
                }
            }
            break;
        }
        case 'r': {
            if (CAM_signal[cam_id] == true) {
                active_CAM_edges_counter[cam_id]++;
                if (active_CAM_edges_counter[cam_id] >= 7) {  // after an abitrary number of CAM edges skip this edge in output to generate the failure
                    active_CAM_edges_counter[cam_id] = 0;
                    if (cam_id == 0) {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                    } else {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
                    }
                } else {
                    output_CAM_no_failure(cam_id);
                }
            }
            break;
        }
    }
}

//## CAM_PAT_ERR_reset

void CAM_PAT_ERR_reset() {
    active_CAM_edges_counter[0] = 0;  // reset counter for CAM1
    active_CAM_edges_counter[1] = 0;  // reset counter for CAM2
    output_CAM_no_failure(0);         // reset CAM1
    output_CAM_no_failure(1);         // reset CAM2
}

//## Output_SC_CAM_CRK
void output_SC_CAM_CRK(int cam_id) {
    if (failure_active == true) {
        switch (sc_type_SC_CAM_CRK) {
            case (1):  // CrkScg
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                output_CAM_no_failure(cam_id);
                break;
            }
            case (2):  // CrkScb
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
                output_CAM_no_failure(cam_id);
                break;
            }
            case (3):  // CamScg
            {
                if (cam_id == 0) {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                } else {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
                }
                output_CRK_no_failure();
                break;
            }
            case (4):  // CamScb
            {
                if (cam_id == 0) {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                } else {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                }
                output_CRK_no_failure();
                break;
            }
        }
    } else if (failure_active == false) {
        output_CRK_no_failure();
        output_CAM_no_failure(cam_id);
    }
}

//## POSN_ENG_STST_LOSS_reset
void SC_CAM_CRK_reset(void) {
    failure_active = false;
    output_CRK_no_failure();
    output_CAM_no_failure(0);  // reset CAM1
    output_CAM_no_failure(1);  // reset CAM2
}

//### Failure Processing ###
void failure_processing(char failure_ident) {
    switch (failure_ident) {
        case '1': {
            break;
        }
        case '2': {
            break;
        }
        case '3': {
            break;
        }
        case '4': {
            // CRK_RUN_OUT();
            break;
        }
        case '7': {
            break;
        }
        case '8': {
            break;
        }
        case '9':  // Cam delay
        {
            if (active_cam_failure == 2) {
                CAM_delay(0);  // for CAM1
                CAM_delay(1);  // for CAM2
            } else if (active_cam_failure == 1) {
                CAM_delay(1);  // for CAM2
            } else {
                CAM_delay(0);  // for CAM1
            }
            break;
        }
        case 'a': {
            break;
        }
            //            case 'b': //
            //				{
            //					break;
            //				}
        case 'f': {
            break;
        }
        case 'h': {
            break;
        }
        case 'i': {
            break;
        }
        case 'j': {
            break;
        }
        case 'k': {
            break;
        }
        case 'l': {
            break;
        }
        case 'm': {
            break;
        }
        default: {
            break;
        }
    }
}

//### Failure Synchronization Reset ###
void failure_synch_reset(char failure_ident) {
    switch (failure_ident) {
        case '4': {
            // CRK_RUN_OUT
            CRK_RUN_OUT_reset();
            break;
        }
        case '6': {
            // CRK_TOOTH_PER
            CRK_TOOTH_PER_reset();
            break;
        }
        case '7': {
            // CAM_DELAY(CAM_TOOTH_OFF)
            CAM_delay_reset();
            break;
        }
        default:
            break;
    }
}

//### Former teeth time calculation ###
double former_teeth_time_calculation(long t_tooth, unsigned int teeth_count,
                                     int numb_miss_teeth) {
    double form_teeth_time;

    form_teeth_time = (double)t_tooth;

    if (teeth_count == 1) {
        form_teeth_time = form_teeth_time / (double)(numb_miss_teeth + 1);
    }

    return (form_teeth_time);
}

//### Former teeth time calculation output ###
double former_teeth_time_calculation_output(long t_tooth,
                                            unsigned int teeth_count, int numb_miss_teeth) {
    double form_teeth_time;

    form_teeth_time = (double)t_tooth;

    if (teeth_count == number_teeth_between_gaps) {
        form_teeth_time = form_teeth_time / (double)(numb_miss_teeth + 1);
    }

    return (form_teeth_time);
}
