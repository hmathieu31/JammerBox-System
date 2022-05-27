/**
 ******************************************************************************
 * @file    	  synchronization.c
 * @brief		  Implements the synchronisation of signals on the STM32
 * 				  Project name	: STM32-Jammerbox
 * 				  Controller	: STM32F103RB
 * @date		  May 25, 2022
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

/* Private includes ----------------------------------------------------------*/
#include "synchronization.h"
// ### Basic includes ###
#include <stdbool.h>

// ### Hardware specific includes ###
#include "tim.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "stm32f1xx_hal_usart.h"
#include "usart.h"

// ### Program includes ###
#include "timer.h"
#include "usart_soft.h"
#include "failures.h"

// ### Variables ###

//***************** CRK ********************
//** User config **
extern int number_teeth_CRK;
extern int number_miss_teeth;
extern int number_gap;
extern double gap_ratio_CRK_DET;
extern double gap_ratio_CRK_VLD;

// variables to replace input capture buffer
extern unsigned long IC1BUF;
extern unsigned long IC2BUF;

//** Calculation variables **
extern unsigned long T_TOOTH_RAW_2;
extern unsigned long T_TOOTH_RAW_1;
extern unsigned long T_TOOTH_RAW;
extern unsigned long T_TOOTH_RAW_2_old;
extern unsigned long T_TOOTH_RAW_1_old;
extern unsigned long T_TOOTH_RAW_old;
extern unsigned long low_time_CRK;
extern unsigned long timer_overflow_CRK;
extern unsigned int teeth_count_CRK;
extern unsigned int teeth_count_CAM_CRK_synch;
extern unsigned int teeth_count_CAM_CRK_synch_ahead;
extern unsigned int number_real_teeth;
extern unsigned int number_teeth_between_gaps;
extern unsigned int delay_counter_CRK;
extern unsigned int segment_counter_CRK;
extern unsigned int number_segments_CRK;
extern unsigned int shift_counter_CRK;
extern unsigned int start_delay;
extern unsigned int engine_start_counter;
extern unsigned int engine_start_counter_limit;
extern double revolution_CRK;
extern bool CRK_synch;
extern bool CRK_synch_temp;
extern bool delay_off;
extern bool engine_start;
extern bool synch_times_valid;

//***************** CAM ********************
//** User config **
extern int number_teeth_CAM[2];
extern double CAM_edges[2][24];
extern double distance_gap_to_CAM_edge[2][24];
extern double first_edge_to_tdc0[2];
extern char active_CAM_edges[2];
extern char sensortype_CAM[2];

//***************** CAM/CRK - output port setting ********************
extern bool output_level_setting;

//***************** CAM/CRK ****************
//** Calculation variables **
extern unsigned long timer_overflow_CAM;
extern unsigned long segment_time_CAM;
extern unsigned int edge_count_CAM[2];
extern unsigned int edge_validation_counter_CAM[2];
extern unsigned int edge_position_counter_CAM[2];
extern unsigned int former_edge_position_CAM[2];
extern unsigned int edge_validation_counter_CAM_ahead[2];
extern unsigned int edge_position_counter_CAM_ahead[2];
extern unsigned int former_edge_position_CAM_ahead[2];
extern double gap_to_edge;
extern double gap_to_edge_ahead;
extern double gap_to_first_edge[2];
extern double gap_to_first_edge_difference[2];
extern double tolerance_window_CAM[2];
extern bool CAM_tolerance_switch[2];
extern bool CAM_CRK_synch_status;
extern bool CAM_CRK_synch_status_ahead;
extern bool CAM_CRK_synch_ahead[2];
extern bool CAM_signal[2];
extern bool CRK_CAM_synch[2];
extern int teeth_count_overall;

//***************** USART-Send **************
extern char message[];

//***************** Failure Reset values ***
extern char failure_identify;

//### Functions ###

// ## CRK Synchronisation
void sync_CRK(void)
{
    // Set label that indicates engine start
    if (engine_start_counter < engine_start_counter_limit && engine_start == false)
    {
        engine_start_counter++;
    }
    else if (engine_start == false)
    {
        engine_start_counter = 0;
        engine_start = true;
    }
    teeth_count_overall++;

    // Wait for completed start delay
    if ((delay_counter_CRK < start_delay) && delay_off == false)
    {
        delay_counter_CRK++;
    }
    else if (delay_off == false)
    {
        delay_off = true;
        delay_counter_CRK = 0;
    }

    if (delay_off == true)
    {
        if (CRK_synch == true)
        {
            // Teeth Counter CRK
            if ((teeth_count_CRK < number_teeth_between_gaps))
            {
                // 360�CRK for one gap; 180� for two gaps; 120� for three gaps
                // test
                // teeth_count_CRK++;

                // 720�CRK for CAM CRK synchronization
                teeth_count_CAM_CRK_synch++;
                teeth_count_CAM_CRK_synch_ahead++;
            }
            else
            {
                // test
                // teeth_count_CRK = 1;

                if (segment_counter_CRK == number_segments_CRK && (CAM_CRK_synch_status == true && CAM_CRK_synch_status_ahead == true))
                {

                    if (shift_counter_CRK == number_gap - 1)
                    {
                        shift_counter_CRK = 0;

                        teeth_count_CAM_CRK_synch = 1;
                        teeth_count_CAM_CRK_synch_ahead = 1 + number_teeth_between_gaps + number_miss_teeth;
                    }
                    else
                    {
                        shift_counter_CRK++;
                    }

                    if (shift_counter_CRK == 1)
                    {
                        teeth_count_CAM_CRK_synch = 2 * number_teeth_between_gaps + 2 * number_miss_teeth + 1;
                        teeth_count_CAM_CRK_synch_ahead = 3 * number_teeth_between_gaps + 3 * number_miss_teeth + 1;
                    }
                    else if (shift_counter_CRK == 2)
                    {
                        teeth_count_CAM_CRK_synch = 4 * number_teeth_between_gaps + 4 * number_miss_teeth + 1;
                        teeth_count_CAM_CRK_synch_ahead = 5 * number_teeth_between_gaps + 5 * number_miss_teeth + 1;
                    }

                    CAM_CRK_synch_status = false;
                    CAM_CRK_synch_status_ahead = false;
                }
                else
                {
                    // counter 1
                    if (teeth_count_CAM_CRK_synch == (number_teeth_CRK + number_real_teeth))
                    {
                        teeth_count_CAM_CRK_synch = 1;
                    }
                    else if (teeth_count_CAM_CRK_synch < (number_teeth_CRK + number_real_teeth))
                    {
                        teeth_count_CAM_CRK_synch = teeth_count_CAM_CRK_synch + number_miss_teeth + 1;
                    }

                    // counter 2
                    if (teeth_count_CAM_CRK_synch_ahead == (number_teeth_CRK + number_real_teeth))
                    {
                        teeth_count_CAM_CRK_synch_ahead = 1;
                    }
                    else if (teeth_count_CAM_CRK_synch_ahead < (number_teeth_CRK + number_real_teeth))
                    {
                        teeth_count_CAM_CRK_synch_ahead = teeth_count_CAM_CRK_synch_ahead + number_miss_teeth + 1;
                    }
                }

                if (segment_counter_CRK < number_segments_CRK)
                {
                    segment_counter_CRK++;
                }
                else
                {
                    segment_counter_CRK = 1;
                }
            }

            // Check reference gap in specified range
            if (teeth_count_CRK == 2)
            {
                // if(!(gap_ratio_CRK_VLD < ((double)(T_TOOTH_RAW_1 * T_TOOTH_RAW_1)/(double)(T_TOOTH_RAW_2 * T_TOOTH_RAW))))
                // if(!(3 < ((T_TOOTH_RAW_1 * T_TOOTH_RAW_1)/(T_TOOTH_RAW_2 * T_TOOTH_RAW))))
                if (T_TOOTH_RAW_1 < T_TOOTH_RAW * 2)
                // if(!(3 < ((pow(T_TOOTH_RAW_1))/(T_TOOTH_RAW_2 * T_TOOTH_RAW))))
                {
                    CRK_synch = false;

                    CRK_synch_temp = false;

                    // Send CRK-sycnhronization status
                    HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[4]), 1);

                    CRK_CAM_synch[0] = false;
                    CRK_CAM_synch[1] = false;

                    // Send CRK_CAM-sycnhronization status
                    HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[6]), 1);

                    // Reset actual failure scenarios
                    failure_synch_reset(failure_identify);

                    edge_position_counter_CAM[0] = 0;
                    edge_validation_counter_CAM[0] = 0;
                    former_edge_position_CAM[0] = 0;
                    edge_position_counter_CAM_ahead[0] = 0;
                    edge_validation_counter_CAM_ahead[0] = 0;
                    former_edge_position_CAM_ahead[0] = 0;

                    edge_position_counter_CAM[1] = 0;
                    edge_validation_counter_CAM[1] = 0;
                    former_edge_position_CAM[1] = 0;
                    edge_position_counter_CAM_ahead[1] = 0;
                    edge_validation_counter_CAM_ahead[1] = 0;
                    former_edge_position_CAM_ahead[1] = 0;

                    CAM_CRK_synch_status = false;
                    CAM_CRK_synch_status_ahead = false;
                    CAM_CRK_synch_ahead[0] = false;
                    CAM_CRK_synch_ahead[1] = false;
                    shift_counter_CRK = 0;
                    teeth_count_CRK = 0;
                    teeth_count_CAM_CRK_synch = 0;
                    teeth_count_CAM_CRK_synch_ahead = 0;
                }
            }
        } // CRK_synch == true - END
        else
        {
            // Check reference gap for the first time
            if (synch_times_valid)
            {
                // if(CRK_synch_temp == true && gap_ratio_CRK_VLD < ((double)(T_TOOTH_RAW_1 * T_TOOTH_RAW_1)/(double)(T_TOOTH_RAW_2 * T_TOOTH_RAW)))
                // if(CRK_synch_temp == true && 3 < ((T_TOOTH_RAW_1 * T_TOOTH_RAW_1)/(T_TOOTH_RAW_2 * T_TOOTH_RAW)))
                if (CRK_synch_temp == true && (T_TOOTH_RAW_2 < T_TOOTH_RAW_1 * 2))
                {
                    teeth_count_CRK = 2;
                    teeth_count_CAM_CRK_synch = 2;
                    teeth_count_CAM_CRK_synch_ahead = 2 + number_teeth_between_gaps + number_miss_teeth;
                    segment_counter_CRK = 1;
                    CRK_synch = true;

                    // Send CRK-sycnhronization status
                    HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[3]), 1);
                }
                else
                {
                    CRK_synch_temp = false;
                }

                // if(gap_ratio_CRK_DET < ((double)(T_TOOTH_RAW/T_TOOTH_RAW_1)))
                if (2 < ((T_TOOTH_RAW / T_TOOTH_RAW_1)))
                {
                    CRK_synch_temp = true;
                }
            }
        }

        // set former tooth times
        T_TOOTH_RAW_2 = T_TOOTH_RAW_1;
        T_TOOTH_RAW_1 = T_TOOTH_RAW;

        if (synch_times_valid == false)
        {
            synch_times_valid = true;
        }

    } // delay_off == true - END
}

// ## CAM_CRK Synchronisation
void sync_CAM_CRK(int camId)
{
    // increase CAM edges counter
    if (CAM_tolerance_switch[camId] == false)
    {
        edge_count_CAM[camId]++;
    }

    // change tolerance window for CAM/CRK synchronization when the edge counter has achieved the defined maximum(10)
    if (edge_count_CAM[camId] > 10)
    {
        CAM_tolerance_switch[camId] = true;
        edge_count_CAM[camId] = 0;
        tolerance_window_CAM[camId] = 2.0 * revolution_CRK; // was 1
    }

    // execute CAM_CRK synchronization if CRK synchronization is done
    if (CRK_synch == true)
    {
        if (CRK_CAM_synch[camId] == false) // CAM_CRK synchronization
        {
            // CAM_CRK_synch_ahead[camId] = true;
            // CAM_CRK_synch_set(camId);

            // CAM_CRK synchronization for both active edges(falling edge)
            if (CAM_signal[camId] == false && active_CAM_edges[camId] == 'b')
            {
                gap_to_edge_calculation();

                int i;
                int j;

                double difference;
                double difference_ahead;

                // counter 2
                for (j = 0; j < number_teeth_CAM[camId] * 2; j += 2)
                {

                    difference_ahead = distance_gap_to_CAM_edge[camId][j] - gap_to_edge_ahead;

                    if ((difference_ahead < tolerance_window_CAM[camId]) && (difference_ahead > -tolerance_window_CAM[camId]))
                    {
                        edge_position_counter_CAM_ahead[camId] = j + 1;

                        if ((edge_validation_counter_CAM_ahead[camId] == number_teeth_CAM[camId] * 2) && (edge_position_counter_CAM_ahead[camId] == 1) && (former_edge_position_CAM_ahead[camId] == (number_teeth_CAM[camId] * 2)))
                        {
                            CAM_CRK_synch_ahead[camId] = true;

                            CAM_CRK_synch_set(camId);

                            break;
                        }

                        if (edge_position_counter_CAM_ahead[camId] == 1)
                        {
                            edge_validation_counter_CAM_ahead[camId] = 1;
                        }
                        else if (edge_validation_counter_CAM_ahead[camId] > 0 && (former_edge_position_CAM_ahead[camId] == edge_position_counter_CAM_ahead[camId] - 1) && (edge_validation_counter_CAM_ahead[camId] != 1))
                        {
                            edge_validation_counter_CAM_ahead[camId]++;
                        }

                        former_edge_position_CAM_ahead[camId] = edge_position_counter_CAM_ahead[camId];

                        break;
                    }

                    else if (j == (number_teeth_CAM[camId] * 2 - 2))
                    {
                        CAM_CRK_synch_ahead_reset(camId);
                    }
                }

                // counter 1
                if (CRK_CAM_synch[camId] == false)
                {

                    for (i = 0; i < number_teeth_CAM[camId] * 2; i += 2)
                    {
                        difference = distance_gap_to_CAM_edge[camId][i] - gap_to_edge;

                        if ((difference < tolerance_window_CAM[camId]) && (difference > -tolerance_window_CAM[camId]))
                        {
                            edge_position_counter_CAM[camId] = i + 1;

                            if ((edge_validation_counter_CAM[camId] == number_teeth_CAM[camId] * 2) && (edge_position_counter_CAM[camId] == 1) && (former_edge_position_CAM[camId] == (number_teeth_CAM[camId] * 2)))
                            {
                                CAM_CRK_synch_ahead[camId] = false;

                                CAM_CRK_synch_set(camId);

                                break;
                            }

                            if (edge_position_counter_CAM[camId] == 1)
                            {
                                edge_validation_counter_CAM[camId] = 1;
                            }
                            else if (edge_validation_counter_CAM[camId] > 0 && (former_edge_position_CAM[camId] == edge_position_counter_CAM[camId] - 1) && (edge_validation_counter_CAM[camId] != 1))
                            {
                                edge_validation_counter_CAM[camId]++;
                            }

                            former_edge_position_CAM[camId] = edge_position_counter_CAM[camId];

                            break;
                        }

                        else if (i == (number_teeth_CAM[camId] * 2 - 2))
                        {
                            CAM_CRK_synch_reset(camId);
                        }
                    }
                }
            }

            // CAM CRK synchronization for both active edges(rising edge)
            if (CAM_signal[camId] == true && active_CAM_edges[camId] == 'b')
            {
                gap_to_edge_calculation();

                int i;
                int j;

                double difference;
                double difference_ahead;

                // counter 2
                for (j = 1; j < number_teeth_CAM[camId] * 2; j += 2)
                {
                    difference_ahead = distance_gap_to_CAM_edge[camId][j] - gap_to_edge_ahead;

                    if ((difference_ahead < tolerance_window_CAM[camId]) && (difference_ahead > -tolerance_window_CAM[camId]))
                    {
                        edge_position_counter_CAM_ahead[camId] = j + 1;

                        if (edge_validation_counter_CAM_ahead[camId] > 0 && (former_edge_position_CAM_ahead[camId] == edge_position_counter_CAM_ahead[camId] - 1))
                        {
                            edge_validation_counter_CAM_ahead[camId]++;
                        }

                        former_edge_position_CAM_ahead[camId] = edge_position_counter_CAM_ahead[camId];

                        break;
                    }
                    else if (j > (number_teeth_CAM[camId] * 2 - 2))
                    {
                        CAM_CRK_synch_ahead_reset(camId);
                    }
                }

                // counter 1
                for (i = 1; i < number_teeth_CAM[camId] * 2; i += 2)
                {
                    difference = distance_gap_to_CAM_edge[camId][i] - gap_to_edge;

                    if ((difference < tolerance_window_CAM[camId]) && (difference > -tolerance_window_CAM[camId]))
                    {
                        edge_position_counter_CAM[camId] = i + 1;

                        if (edge_validation_counter_CAM[camId] > 0 && (former_edge_position_CAM[camId] == edge_position_counter_CAM[camId] - 1))
                        {
                            edge_validation_counter_CAM[camId]++;
                        }

                        former_edge_position_CAM[camId] = edge_position_counter_CAM[camId];

                        break;
                    }

                    else if (i > (number_teeth_CAM[camId] * 2 - 2))
                    {
                        CAM_CRK_synch_reset(camId);
                    }
                }
            }

            // CAM CRK synchronization for either falling or rising active edges
            if ((CAM_signal[camId] == true && active_CAM_edges[camId] == 'r') || (CAM_signal[camId] == false && active_CAM_edges[camId] == 'f'))
            {
                gap_to_edge_calculation();

                int i;
                int j;

                double difference;
                double difference_ahead;

                // counter 2
                for (j = 0; j < number_teeth_CAM[camId]; j++)
                {
                    difference_ahead = distance_gap_to_CAM_edge[camId][j] - gap_to_edge_ahead;

                    if ((difference_ahead < tolerance_window_CAM[camId]) && (difference_ahead > -tolerance_window_CAM[camId]))
                    {
                        edge_position_counter_CAM_ahead[camId] = j + 1;

                        if ((edge_validation_counter_CAM_ahead[camId] == number_teeth_CAM[camId]) && (edge_position_counter_CAM_ahead[camId] == 1) && (former_edge_position_CAM_ahead[camId] == number_teeth_CAM[camId]))
                        {
                            CAM_CRK_synch_ahead[camId] = true;

                            CAM_CRK_synch_set(camId);

                            break;
                        }

                        if (edge_position_counter_CAM_ahead[camId] == 1)
                        {
                            edge_validation_counter_CAM_ahead[camId] = 1;
                        }
                        else if (edge_validation_counter_CAM_ahead[camId] > 0 && (former_edge_position_CAM_ahead[camId] == edge_position_counter_CAM_ahead[camId] - 1))
                        {
                            edge_validation_counter_CAM_ahead[camId]++;
                        }

                        former_edge_position_CAM_ahead[camId] = edge_position_counter_CAM_ahead[camId];

                        break;
                    }

                    else if (j == (number_teeth_CAM[camId] - 1))
                    {
                        CAM_CRK_synch_ahead_reset(camId);
                    }
                }

                // counter 1
                if (CRK_CAM_synch == false)
                {
                    for (i = 0; i < number_teeth_CAM[camId]; i++)
                    {
                        difference = distance_gap_to_CAM_edge[camId][i] - gap_to_edge;

                        if ((difference < tolerance_window_CAM[camId]) && (difference > -tolerance_window_CAM[camId]))
                        {
                            edge_position_counter_CAM[camId] = i + 1;

                            if ((edge_validation_counter_CAM[camId] == number_teeth_CAM[camId]) && (edge_position_counter_CAM[camId] == 1) && (former_edge_position_CAM[camId] == number_teeth_CAM[camId]))
                            {
                                CAM_CRK_synch_ahead[camId] = false;

                                CAM_CRK_synch_set(camId);

                                break;
                            }

                            if (edge_position_counter_CAM[camId] == 1)
                            {
                                edge_validation_counter_CAM[camId] = 1;
                            }
                            else if (edge_validation_counter_CAM[camId] > 0 && (former_edge_position_CAM[camId] == edge_position_counter_CAM[camId] - 1))
                            {
                                edge_validation_counter_CAM[camId]++;
                            }

                            former_edge_position_CAM[camId] = edge_position_counter_CAM[camId];

                            break;
                        }
                        else if (i == (number_teeth_CAM[camId] - 1))
                        {
                            CAM_CRK_synch_reset(camId);
                        }
                    }
                }
            }

        } // CRK_CAM_synch[camId] == false - END
    }     // CRK_synch == true - END
}

// ## Stalling Detection Function
void Stalling_detection(void)
{
    TIM1_Reset();
    TIM2_Reset();
    TIM_Soft_Reset();

    // check all IC-buffers for overflow
    IC_overflow_check();

    T_TOOTH_RAW_2 = 0;
    T_TOOTH_RAW_1 = 0;
    T_TOOTH_RAW = 0;
    synch_times_valid = false;

    low_time_CRK = 0;

    delay_off = false;
    delay_counter_CRK = 0;
    teeth_count_CRK = 0;
    teeth_count_CAM_CRK_synch = 0;
    teeth_count_CAM_CRK_synch_ahead = 0;
    edge_count_CAM[0] = 0;
    edge_count_CAM[1] = 0;
    edge_validation_counter_CAM[0] = 0;
    edge_validation_counter_CAM[1] = 0;
    edge_position_counter_CAM[0] = 0;
    edge_position_counter_CAM[1] = 0;
    former_edge_position_CAM[0] = 0;
    former_edge_position_CAM[1] = 0;
    edge_validation_counter_CAM_ahead[0] = 0;
    edge_validation_counter_CAM_ahead[1] = 0;
    edge_position_counter_CAM_ahead[0] = 0;
    edge_position_counter_CAM_ahead[1] = 0;
    former_edge_position_CAM_ahead[0] = 0;
    former_edge_position_CAM_ahead[1] = 0;
    segment_counter_CRK = 0;
    shift_counter_CRK = 0;
    CAM_tolerance_switch[0] = false;
    CAM_tolerance_switch[1] = false;
    CAM_CRK_synch_status = false;
    CAM_CRK_synch_status_ahead = false;
    CAM_CRK_synch_ahead[0] = false;
    CAM_CRK_synch_ahead[1] = false;
    tolerance_window_CAM[0] = 2.0 * revolution_CRK;
    tolerance_window_CAM[1] = 2.0 * revolution_CRK;

    // Reset CRK and CAM_CRK synchronization
    if (CRK_synch == true)
    {
        HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[4]), 1);  // CRK synchronization lost

    }

    if (CRK_CAM_synch[0] == true)
    {
         HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[6]), 1); // CAM_CRK synchronization lost
    }
    if (CRK_CAM_synch[1] == true)
    {
         HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[6]), 1); // CAM_CRK synchronization lost
    }

    CRK_synch = false;
    CRK_synch_temp = false;
    CRK_CAM_synch[0] = false;
    CRK_CAM_synch[1] = false;
    teeth_count_overall = 0;

    // Output signal level treatment
    output_level_setting = false;

    engine_start = false;
    engine_start_counter = 0;
}

// ## Stalling Detection Function
void Stalling_detection_CRK(void)
{
    TIM1_Reset();
    //		Timer4Reset();	// Is this necessary as well?

    // check all IC-buffers for overflow
    IC_overflow_check();

    T_TOOTH_RAW_2 = 0;
    T_TOOTH_RAW_1 = 0;
    T_TOOTH_RAW = 0;
    synch_times_valid = false;

    low_time_CRK = 0;

    delay_off = false;
    delay_counter_CRK = 0;
    teeth_count_CRK = 0;
    segment_counter_CRK = 0;
    shift_counter_CRK = 0;
    tolerance_window_CAM[0] = 2.0 * revolution_CRK;
    tolerance_window_CAM[1] = 2.0 * revolution_CRK;

    // Reset CRK and CAM_CRK synchronization
    if (CRK_synch == true)
    {
         HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[4]), 1); // CRK synchronization lost
    }

    CRK_synch = false;
    CRK_synch_temp = false;
    teeth_count_overall = 0;

    // Output signal level treatment
    output_level_setting = false;

    engine_start = false;
    engine_start_counter = 0;
}

// ## Stalling Detection Function
void Stalling_detection_CAM(int camId)
{
    TIM2_Reset();
    // Timer5Reset(); // TODO: Is this reset warranted?
    // check all IC-buffers for overflow
    IC_overflow_check();

    teeth_count_CAM_CRK_synch = 0;
    teeth_count_CAM_CRK_synch_ahead = 0;
    edge_count_CAM[camId] = 0;
    edge_validation_counter_CAM[camId] = 0;
    edge_position_counter_CAM[camId] = 0;
    former_edge_position_CAM[camId] = 0;
    edge_validation_counter_CAM_ahead[camId] = 0;
    edge_position_counter_CAM_ahead[camId] = 0;
    former_edge_position_CAM_ahead[camId] = 0;
    CAM_tolerance_switch[camId] = false;
    CAM_CRK_synch_status = false;
    CAM_CRK_synch_status_ahead = false;
    CAM_CRK_synch_ahead[camId] = false;
    tolerance_window_CAM[camId] = 2.0 * revolution_CRK;

    if (CRK_CAM_synch[camId] == true)
    {
         HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[6]), 1);// CAM_CRK synchronization lost
    }

    CRK_CAM_synch[camId] = false;

    // Output signal level treatment
    output_level_setting = false;

    engine_start = false;
    engine_start_counter = 0;
}

// ## CRK synchronisation preparation
void sync_CRK_preparation(void)
{
    // Read Timer value from IC3-buffer
    T_TOOTH_RAW = IC2BUF;

    // Calculate tooth time
    T_TOOTH_RAW = T_TOOTH_RAW + timer_overflow_CRK * htim2.Init.Period;

    // test
    if (delay_off == true)
    {
        if (CRK_synch == true)
        {
            // Teeth Counter CRK
            if ((teeth_count_CRK < number_teeth_between_gaps))
            {
                // 360�CRK for one gap; 180� for two gaps; 120� for three gaps
                teeth_count_CRK++;
            }
            else
            {
                teeth_count_CRK = 1;
            }
        }
    }

    // reset timer 2
    TIM1_Reset();
}

// ## CAM_CRK synchronisation preparation
void sync_CAM_CRK_preparation(void)
{
    // Calculate segment time if falling edge has occured
    // segment_time_CAM = (unsigned long)IC4BUF;
    // segment_time_CAM = segment_time_CAM + timer_overflow_CAM * (unsigned long)PR3;

    // reset timer 3
    TIM2_Reset();
}

// ## Gap to edge calculation
void gap_to_edge_calculation(void)
{
    // calculate angles between reference gap and CAM-edges when synchronization is not yet done PR2: Timer periode value, TMR2 TMR counter at that moment
    gap_to_edge = (((double)teeth_count_CAM_CRK_synch - 1.0) + (double)(((unsigned long)(__HAL_TIM_GET_COUNTER(&htim2)) + timer_overflow_CRK * __HAL_TIM_GET_AUTORELOAD(&htim2)) / T_TOOTH_RAW)) * revolution_CRK;

    gap_to_edge_ahead = (((double)teeth_count_CAM_CRK_synch_ahead - 1.0) + (double)(((unsigned long)(__HAL_TIM_GET_COUNTER(&htim2)) + timer_overflow_CRK * __HAL_TIM_GET_AUTORELOAD(&htim2)) / T_TOOTH_RAW)) * revolution_CRK;
}

// ## Reset CAM_CRK_synch
void CAM_CRK_synch_reset(int camId)
{
    edge_position_counter_CAM[camId] = 0;
    edge_validation_counter_CAM[camId] = 0;
    former_edge_position_CAM[camId] = 0;

    // set teeth_count_CAM_CRK_synch to one after the next reference gap
    CAM_CRK_synch_status = true;
}

// ## Reset CAM_CRK_synch_ahead
void CAM_CRK_synch_ahead_reset(int camId)
{
    edge_position_counter_CAM_ahead[camId] = 0;
    edge_validation_counter_CAM_ahead[camId] = 0;
    former_edge_position_CAM_ahead[camId] = 0;

    // set teeth_count_CAM_CRK_synch to one after the next reference gap
    CAM_CRK_synch_status_ahead = true;
}

// ## Set CAM_CRK_synch
void CAM_CRK_synch_set(int camId)
{
    CRK_CAM_synch[camId] = true;

    // Send CRK_CAM-sycnhronization status
     HAL_USART_Transmit_IT(&husart1, &((uint8_t)message[6]), 1);

    CAM_CRK_synch_status = false;
    CAM_CRK_synch_status_ahead = false;
    shift_counter_CRK = 0;
}

// ## IC overflow check
void IC_overflow_check()
{
    IC1BUF = 0;
    IC2BUF = 0;
}
