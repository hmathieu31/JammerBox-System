/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Main		                                             */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

// ### Basic includes ###
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// ### Hardware specific includes ###
#include "stm32f1xx_hal_conf.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_tim.h"
#include "stm32f1xx_hal_usart.h"

// ### Program includes ###
#include "failures.h"

#include "gpio.h"
#include "main.h"
#include "synchronization.h"
#include "system_configuration.h"
#include "tim.h"
#include "timer.h"
#include "usart.h"

// ### Definitions ###

//** CAM_delay **
#define edges_beetween_shift_CAM_delay_definition 6

// ### Global variables ###

//***************** CRK ********************
//** User config **
int number_teeth_CRK = 0;
int number_miss_teeth = 0;
int number_gap = 0;
double tdc_to_gap = 0;
double first_seg_angle = 0;
int number_cylinder = 0;
unsigned int first_seg_start_tooth = 0;
double gap_ratio_CRK_DET = 0; // Typical Value for C_CRK_GAP_DET = 1.375
// Gap ratio CRK for Gap Validation
double gap_ratio_CRK_VLD = 0; // Typical Value for C_CRK_GAP_VLD = 3
char sensortype_CRK;          // c = CPDD  h = hall sensor

// Variables to replace the input capture buffer
unsigned long IC1BUF;
unsigned long IC2BUF;
unsigned long IC3BUF;
unsigned long IC4BUF;
unsigned long IC5BUF;
unsigned long IC6BUF;

//** Calculation variables **
unsigned long T_TOOTH_RAW_2 = 0;
unsigned long T_TOOTH_RAW_1 = 0;
unsigned long T_TOOTH_RAW = 0;
unsigned long T_TOOTH_RAW_2_old = 0;
unsigned long T_TOOTH_RAW_1_old = 0;
unsigned long T_TOOTH_RAW_old = 0;
unsigned long low_time_CRK = 0;
unsigned long timer_overflow_CRK = 0;
unsigned int teeth_count_CRK = 0;
unsigned int teeth_count_CAM_CRK_synch = 0;
unsigned int teeth_count_CAM_CRK_synch_ahead = 0;
unsigned int number_real_teeth = 0;
unsigned int number_teeth_between_gaps = 0;
unsigned int delay_counter_CRK = 0;
unsigned int segment_counter_CRK = 0;
unsigned int number_segments_CRK = 0;
unsigned int shift_counter_CRK = 0;
unsigned int start_delay = 100;
unsigned int engine_start_counter = 0;
unsigned int engine_start_counter_limit = 2;
double revolution_CRK = 0;
bool CRK_synch = false;
bool CRK_synch_temp = false;
bool delay_off = false;
bool CRK_signal = false;
bool CRK_config = false;
bool engine_start = false;
bool synch_times_valid = false;

//***************** CAM ********************
//** User config **
unsigned int number_active_edges_CAM[2];
int number_teeth_CAM[2] =
    {0, 0};
double filter_time_CAM[2];
double CAM_edges[2][24];
double distance_gap_to_CAM_edge[2][24];
double first_edge_to_tdc0[2] =
    {0, 0};
char active_CAM_edges[2]; // f: falling; r: rising; b: both
char sensortype_CAM[2];
int number_of_CAM = 1;
int cam_setup_counter = 0;

//***************** CAM/CRK - configuration completion and output port setting ********************
bool configuration_complete = false;
bool output_level_setting = false;

//***************** CAM/CRK ****************
//** Calculation variables **
unsigned long timer_overflow_CAM = 0;
unsigned long segment_time_CAM = 0;
unsigned int edge_count_CAM[2] =
    {0, 0};
unsigned int edge_validation_counter_CAM[2] =
    {0, 0};
unsigned int edge_position_counter_CAM[2] =
    {0, 0};
unsigned int former_edge_position_CAM[2] =
    {0, 0};
unsigned int edge_validation_counter_CAM_ahead[2] =
    {0, 0};
unsigned int edge_position_counter_CAM_ahead[2] =
    {0, 0};
unsigned int former_edge_position_CAM_ahead[2] =
    {0, 0};
double gap_to_edge;
double gap_to_edge_ahead;
double gap_to_first_edge[2] =
    {0, 0};
double gap_to_first_edge_difference[2] =
    {0, 0};
double tolerance_window_CAM[2];
bool CAM_tolerance_switch[2] =
    {false, false};
bool CAM_CRK_synch_status = false;
bool CAM_CRK_synch_status_ahead = false;
bool CAM_CRK_synch_ahead[2] =
    {false, false};
bool CAM_signal[2] =
    {false, false};
bool CRK_CAM_synch[2] =
    {false, false};
bool CAM_config = false;
int teeth_count_overall = 0;

//***************** Communication validation ************
bool communication_active = false;
bool communication_ready = false;
bool communication_validation = false;

//********** Failure treatment **************
char failure_identify = '0';
// 0: No failure
// 1: CRK_NO_SIG
// 2: CAM_NO_SIG
// 3: CAM/CRK_NO_SIG
// 4: CRK_RUN_OUT
// 5: CAM_PER
// 6: CRK_TOOTH_PER
// 7: CAM_TOOTH_OFF
// 8: CAM_SYN
// 9: CAM_SYN_CRK
// a: CAM_REF_CRK
// b: CRK_SHO_LEVEL
// f: CRK_TOOTH_NR

int active_cam_failure = 0;
// 0: Failur is active on CAM1
// 1: Failur is active on CAM2
// 2: Failur is active on CAM1 and CAM2

//** Labels indicating failure status **
bool failure_active = false;
bool failure_active_CAM_blank_out = false;
bool failure_set = false;
bool failure_passed = false;
bool failure_waiting = false;

//** Labels indicating failure configuration status response to user interface **
bool failure_configured = false;
bool failure_configured_CAM_blank_out = false;

//** Timer overflow values for CRK and CAM - failures
unsigned long timer_overflow_CRK_failure = 0;
unsigned long timer_overflow_CAM_failure = 0;
unsigned long timer_overflow_CAM_REF_CRK = 0;

//** CRK_RUN_OUT **
char sc_type_CRK_RUN_OUT;
unsigned int teeth_counter_CRK_RUN_OUT = 0;
unsigned int angle_to_start_failure_CRK_RUN_OUT;
unsigned int failure_period_CRK_RUN_OUT;
unsigned int counter_TDC0;
int period_counter_CRK_RUN_OUT;
double difference_to_edge_TDC0;
double difference_to_edge_failure_start;
bool detected_TDC0;
bool TDC_on_edge;
bool counter_ready = false;
bool counter_reset = true;

//** CAM_PER **
unsigned int counter_CAM_PER[2] =
    {0, 0};
unsigned int number_edges_CAM_PER;
double filter_time_CAM_PER;
double microsecond_per_timer_tick_CAM_PER__CRK_TOOTH_PER = 0.217;
bool all_active_edges_CAM_PER = false;
char active_edges_CAM_PER; // f: falling; r: rising; b: both

//** CRK_TOOTH_PER **
unsigned int start_tooth_CRK_TOOTH_PER;
unsigned int number_pulses_CRK_TOOTH_PER;
unsigned int engine_revolutions_CRK_TOOTH_PER;
unsigned int teeth_counter_CRK_TOOTH_PER;
unsigned int revolution_counter_CRK_TOOTH_PER;
double calculation_factor_CRK_TOOTH_PER;

//** CAM_DELAY(CAM_TOOTH_OFF / CAM_REF_CRK / CAM_SYN / CAM_SYN_CRK) **
unsigned int number_processing_edges_CAM_delay[2] =
    {0, 0};
const unsigned int edges_beetween_shift_CAM_delay = 6;
unsigned int shift_counter_CAM_delay[2][edges_beetween_shift_CAM_delay_definition];
double angle_to_edge_CAM_delay[2][edges_beetween_shift_CAM_delay_definition];
double delay_angle_CAM_delay;
double delay_factor_CAM_delay = 1.0;
bool timer_active_CAM_delay[2] =
    {false, false};
bool interrupt_check_CAM_delay[2];

//** CAM_REF_CRK **
unsigned int delay_counter_CAM_REF_CRK;
long double angle_time_to_start_failure_CAM_REF_CRK; // Value Delay (ms or �CRK)
double difference_to_edge_failure_start_CAM_REF_CRK;
char delay_type_CAM_REF_CRK; // t: time / c: �CRK

//** CRK_TOOTH_OFF **
unsigned int number_tooth_off = 0;
unsigned int number_teeth_between_tooth_off = 0;
unsigned int counter_tooth_off = 0;
unsigned int teeth_counter_CRK_TOOTH_OFF = 0;
unsigned int counter_gap_left_CRK_TOOTH_OFF = 0;

//** CRK_GAP_NOT_DET **
unsigned int teeth_counter_CRK_GAP_NOT_DET = 0;
unsigned int timer_Counter_CRK_GAP_NOT_DET = 0;

//** SEG_ADP_ER_LIM **
unsigned int teeth_counter_SEG_ADP_ER_LIM = 0;
unsigned int timer_Counter_SEG_ADP_ER_LIM = 0;
double crk_delay_SEG_ADP_ER_LIM = 0;

//** CRK_PLS_ORNG **
double crk_pulse_duration_CRK_PLS_ORNG = 0;

//** POSN_ENG_STST_LOSS **
unsigned int crk_teeth_off_POSN_ENG_STST = 0;
unsigned int counter_POSN_ENG_STST = 0;

//** CAM_PAT_ERR **
unsigned int active_CAM_edges_counter[2] =
    {0, 0};

//** SC_CAM_CRK **
unsigned int sc_type_SC_CAM_CRK = 0;

//***************** USART ********************
//** Receive **
int char_counter = 0;
int data_counter = 0;
char in;
char start_char = '!';
char end_char = '%';
char input_chars[250];
char input[250];
int input_char_counter = 0;
char temp_chars_1[21];
char temp_chars_2[21];
char temp_chars_3[21];
char temp_chars_4[21];
char temp_chars_5[21];
char temp_chars_6[21];
char temp_chars_7[21];
char temp_chars_8[21];
char temp_chars_9[21];
char temp_chars_10[21];
bool receiving = false;
bool message_received = false;
bool com_error = false;
char message_identify;

//** Send **
char message[14] =
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'z', 'x', 'y'};
// 1: COM-error
// 2: CRK-configuration ready
// 3: CAM-configuration ready
// 4: CRK-synchronization ready
// 5: CRK-synchronization lost
// 6: CAM/CRK-synchronization ready
// 7: CAM/CRK-synchronization lost
// 8: Failure active
// 9: Failure passive
// a: Failure CAM blank out active
// b: Failure CAM blank out passive
// z: Communication validation
// x: Communication receive ready
// y: Communication receive not ready

//### Main Function ###

int main1(void)
{
    Config_clock_tree();
    // ## Initialising ##

    TIM1Init(); //? We probabaly can replace the Timer 2 by the watchdog timer (and use timer 2 for timer 4) (some refactoring time incoming)

    TIM2Init();

    Timer3Init();

    Timer4Init();

    SysTickInit();

    EXTI8Init();

    EXTI9Init();

    EXTI14Init();

    EXTI11Init();

    EXTI12Init();

    EXTI13Init();

    PORT_A_Config();

    PORT_B_Config();

    Usart1Init();

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

    // ## Main loop ##
    while (1)
    {
        // failure processing
        if (configuration_complete)
        {
            failure_processing(failure_identify);
        }

        // process the received message
        if (message_received == true && com_error == false)
        {
            USART_ProcessMessage();
        }

        // reset all values when CRK stalling is detected
        if ((timer_overflow_CRK > 10)) // || (timer_overflow_CAM > 5))
        {
            // Stalling_detection();
            Stalling_detection_CRK();
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
        }
        // reset all values when CAM stalling is detected //was not here before
        if ((timer_overflow_CAM > 5))
        {
            Stalling_detection_CAM(0);
            Stalling_detection_CAM(1);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
        }

        // send failure configuration status
        USART_send_failure_configuration_status(failure_identify, failure_configured, failure_configured_CAM_blank_out);

        // check input signal level and set corresponding output level
        Input_signal_observe(output_level_setting);
        if (CRK_synch)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
        }

        if (CRK_synch_temp)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
        }

        if (CRK_synch)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
        }
    }
}

// ### EXTI Callback functions ###

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == 8) // Capture Event rising edge --CRK--
    {
        CRK_signal = true; // Set actual signal level

        if (failure_active == false) // Set CRK-output
        {
            output_CRK_no_failure();
        }
        else if (failure_identify != '1' && failure_identify != '4' && failure_identify != 'f' && failure_identify != 'b' && failure_identify != 'i' && failure_identify != 'j' && failure_identify != 'k' && failure_identify != 'l' && failure_identify != 'm')
        {
            output_CRK_no_failure();
        }

        low_time_CRK = IC1BUF; // Set actual low time of CRK signal

        output_CRK(failure_identify); // CRK Output
        timer_overflow_CRK = 0;       // edge was detected, so no stalling
    }

    if (GPIO_Pin == 9) //## Capture Event falling edge --CRK--
    {
        CRK_signal = false; // Set actual signal level

        if (failure_active == false) // Set CRK-output
        {
            output_CRK_no_failure();
        }
        else if (failure_identify != '1' && failure_identify != '4' && failure_identify != 'f' && failure_identify != 'h' && failure_identify != 'i' && failure_identify != 'j' && failure_identify != 'k' && failure_identify != 'l' && failure_identify != 'm')
        {
            output_CRK_no_failure();
        }

        sync_CRK_preparation(); // CRK synchronisation preparation

        output_CRK(failure_identify); // CRK Output
        if (configuration_complete == true)
        {
            sync_CRK(); // CRK synchronisation
        }
        timer_overflow_CRK = 0; // edge was detected, so no stalling
    }

    if (GPIO_Pin == 14) //## Capture Event rising edge --CAM1--
    {

        CAM_signal[0] = true; // Set actual signal level

        output_CAM(failure_identify, 0); // CAM1 Output

        if (configuration_complete == true)
        {
            sync_CAM_CRK(0); // CAM_CRK Synchronisation
        }
        timer_overflow_CAM = 0; // edge was detected, so no stalling
    }

    if (GPIO_Pin == 11) //## Capture Event falling edge --CAM1--
    {
        CAM_signal[0] = false; // Set actual signal level

        TIM2_Reset();

        output_CAM(failure_identify, 0); // CAM1 Output

        if (configuration_complete == true)
        {
            sync_CAM_CRK(0); // CAM_CRK Synchronisation
        }
        timer_overflow_CAM = 0; // edge was detected, so no stalling
    }

    if (GPIO_Pin == 12) //## Capture Event rising edge --CAM2--
    {
        CAM_signal[1] = true; // Set actual signal level

        output_CAM(failure_identify, 1); // CAM2 Output

        if (configuration_complete == true)
        {
            sync_CAM_CRK(1); // CAM_CRK Synchronisation
        }
        timer_overflow_CAM = 0; // edge was detected, so no stalling
    }

    if (GPIO_Pin == 13) //## Capture Event falling edge --CAM2--
    {
        if (number_of_CAM == 2)
        {
            CAM_signal[1] = false; // Set actual signal level

            TIM2_Reset();

            output_CAM(failure_identify, 1); // CAM2 Output

            if (configuration_complete == true)
            {
                sync_CAM_CRK(1); // CAM_CRK Synchronisation
            }
            timer_overflow_CAM = 0; // edge was detected, so no stalling
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim1)
    {
        TIM1_PeriodElapsedCallback();
    }
    if (htim == &htim2)
    {
        TIM2_PeriodElapsedCallback();
    }
    if (htim == &htim3)
    {
        TIM3_PeriodElapsedCallback();
    }
    if (htim == &htim4)
    {
        TIM4_PeriodElapsedCallback();
    }
}

//## Timer 1 Interrupt CRK tooth time (previously timer2)

void TIM1_PeriodElapsedCallback(void)
{

    // all overflows between the events
    timer_overflow_CRK++;
}

//## Timer 2 Interrupt CAM tooth time (previously timer3)

void TIM2_PeriodElapsedCallback(void)
{
    // all overflows between the events
    // test
    timer_overflow_CAM++;
}
//## Timer 3 Interrupt: CAM_PER - start value

void TIM3_PeriodElapsedCallback(void)
{

    if (failure_identify == '5')
    { // CAM_PER: error identified by '5'

        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == 1)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
        }

        counter_CAM_PER[0]++; // Number of times we lost CAM with timer 6
        if (counter_CAM_PER[0] == 2)
        {
            HAL_TIM_Base_Stop(&htim3);
            counter_CAM_PER[0] = 0; // Reset timer 6 CAM lost counter
        }
        __HAL_TIM_SET_COUNTER(&htim3, 0); // reset the timers counter
    }
    else if (failure_identify == '6')
    { // CRK_TOOTH_PER

        // Load the period value 20us  here
        // Timer period = Clock_Period * (PSC+1) * (ARR+1)
        // ideally we want the lowest possible PSC
        // But ARR must not exceed (2^16)-1 = 65535
        // 72Mhz*PSC+1*ARR+1

        __HAL_TIM_SET_AUTORELOAD(&htim4, 1439); // Define ARR value 20us*72Mhz = 1440 (PSC=0 pour TIM7)

        HAL_TIM_Base_Stop(&htim4);

        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        }

        HAL_TIM_Base_Stop(&htim3);
    }
    else if (failure_identify == 'b')
    { // CRK_SHO_LEVEL

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        HAL_TIM_Base_Stop(&htim3);
    }
}

//## Timer 4 Interrupt: CAM_PER - pulse duration

void TIM4_PeriodElapsedCallback(void)
{

    if (failure_identify == '5') // CAM_PER --> Cam_Spk
    {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 1)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
        }

        counter_CAM_PER[1]++; // Number of times we lost CAM with timer 7
        if (counter_CAM_PER[1] == 2)
        {

            HAL_TIM_Base_Stop(&htim4);

            counter_CAM_PER[1] = 0; // Reset timer 7 CAM counter
        }

        __HAL_TIM_SET_COUNTER(&htim4, 0);
    }
    else if (failure_identify == '6') // CRK_TOOTH_PER
    {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        }

        HAL_TIM_Base_Stop(&htim4);
    }
    else if (failure_identify == 'j')
    { // SEG_ADP_ER_LIM

        timer_Counter_SEG_ADP_ER_LIM++;
        switch (timer_Counter_SEG_ADP_ER_LIM)
        {
        case 1: { // failure for the falling edge
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
            if (failure_waiting == true)
            {                              // if the rising edge has already happen
                if (sensortype_CRK == 'c') // sensor is cpdd
                {
                    SysTick_Config(3600); // 72MHz*50us=3600
                }
                else if (sensortype_CRK == 'h')
                { // all the others
                    SysTick_Config((T_TOOTH_RAW / 2) - 1);
                }
                else
                {
                    // if sensor type not set, shouldn't happen
                    SysTick_Config(1);
                }

                // Start timer 8
                SysTick->CTRL |= SysTick_CTRL_ENABLE; // TODO: Check these systick commands
            }
            failure_passed = true;
            break;
        }
        case 2: {                   // failure for the rising edge
            SEG_ADP_ER_LIM_reset(); // SEG_... failure_inactive, passed and waiting =false, init timer 7 & 8, SEG_...error counter reset
            break;
        }
        }
        HAL_TIM_Base_Stop(&htim4);
    }
    else if (failure_identify == 'k') // CrkPlsOrng
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

        HAL_TIM_Base_Stop(&htim4);
    }
    else
    {
        HAL_TIM_Base_Stop(&htim4);
    }

    // ### USART Receive Callback function ###
    void HAL_USART_RxCpltCallback(USART_HandleTypeDef * husart) // Likely similar to an interrupt triggering whenever a char is received as all the receptions we will get are of size 1 char
        if (husart == &husart1)
        {
            // UART Receive
            in = USART_ProcessMessage(USART1);

            // PERR : parity error status bit 1 if error detected 0 i no error detected
            if (USART_GetFlagStatus(USART1, USART_FLAG_PE) == SET || USART_GetFlagStatus(USART1, USART_FLAG_FE == SET))
            {
                UART_COM_error(); //? FERR : Framing Error Status bit 1 if error detected 0 if no error detected

                //? OERR : Receive Buffer Overrun Error Status bit  1 = Receive buffer has overflowed
            }
            else if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) == SET)
            {
                UART_COM_error(); //? 0 = Receive buffer has not overflowed. Clearing a previously set OERR bit (1 → 0 transition) will reset

                //? the receiver buffer and the UxRSR to the empty state
                USART_ProcessMessage(USART1);
            }
            else
            {
                char_counter++;

                if (com_error == false && receiving == true && in != end_char)
                {
                    input_chars[char_counter - 2] = in; // write received char in array
                }
                else if (com_error == false && in == end_char && receiving == true && char_counter > 2)
                {
                    input_chars[char_counter - 2] = '\0'; // set length of array

                    char_counter = 0;        // reset counter value
                    receiving = false;       // reset label that indicates receiving status
                    message_received = true; // set label that indicates succesfully received message
                }
                else if (in == start_char && char_counter == 1)
                {

				char_counter = 0;        // reset counter value
				receiving = false; // reset label that indicates receiving status
				message_received = true; // set label that indicates succesfully received message
			}
			else if (in == start_char && char_counter == 1)
			{
				HAL_USART_Transmit_IT(&husart1, message[13], 1);
				receiving = true;  // set label that indicates receiving status
				com_error = false; // reset COM error, due to received start char
			}
			else
			{
				UART_COM_error(); // send failure message
			}
		}
		USART_ProcessMessage(USART1);
	}
}
