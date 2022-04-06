/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Main		                                             */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/


// ### Basic includes ###
//#include "p33FJ256GP710A.h"
#include "config.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"


// ### Programm includes ###
#include "osc.h"
#include "timer.h"
#include "ic.h"
#include "uart.h"
#include "port_config.h"
#include "system_configuration.h"
#include "synchronization.h"
#include "failures.h"


// ### Definitions ###

//** CAM_delay **
#define edges_beetween_shift_CAM_delay_definition  6


// ### Globas variables ###

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
char sensortype_CRK; // c = CPDD  h = hall sensor 

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
int number_teeth_CAM[2] = {0, 0};
double filter_time_CAM[2];
double CAM_edges[2][24];
double distance_gap_to_CAM_edge[2][24];
double first_edge_to_tdc0[2] = {0, 0};
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
unsigned int edge_count_CAM[2] = {0, 0};
unsigned int edge_validation_counter_CAM[2] = {0, 0};
unsigned int edge_position_counter_CAM[2] = {0, 0};
unsigned int former_edge_position_CAM[2] = {0, 0};
unsigned int edge_validation_counter_CAM_ahead[2] = {0, 0};
unsigned int edge_position_counter_CAM_ahead[2] = {0, 0};
unsigned int former_edge_position_CAM_ahead[2] = {0, 0};
double gap_to_edge;
double gap_to_edge_ahead;
double gap_to_first_edge[2] = {0, 0};
double gap_to_first_edge_difference[2] = {0, 0};
double tolerance_window_CAM[2];
bool CAM_tolerance_switch[2] = {false, false};
bool CAM_CRK_synch_status = false;
bool CAM_CRK_synch_status_ahead =  false;
bool CAM_CRK_synch_ahead[2] = {false, false};
bool CAM_signal[2] = {false, false};
bool CRK_CAM_synch[2] = {false, false};
bool CAM_config = false;
int teeth_count_overall = 0;


//***************** Communication validation ************
bool communication_active = false;
bool communication_ready = false;
bool communication_validation = false;

//********** Failure treatment **************
char failure_identify = '0';
//0: No failure
//1: CRK_NO_SIG
//2: CAM_NO_SIG
//3: CAM/CRK_NO_SIG
//4: CRK_RUN_OUT
//5: CAM_PER
//6: CRK_TOOTH_PER
//7: CAM_TOOTH_OFF
//8: CAM_SYN
//9: CAM_SYN_CRK
//a: CAM_REF_CRK
//b: CRK_SHO_LEVEL
//f: CRK_TOOTH_NR

int active_cam_failure = 0;
//0: Failur is active on CAM1 
//1: Failur is active on CAM2 
//2: Failur is active on CAM1 and CAM2 

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
unsigned int counter_CAM_PER[2] = {0,0};
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
unsigned int number_processing_edges_CAM_delay[2] = {0, 0};
const unsigned int edges_beetween_shift_CAM_delay = 6;
unsigned int shift_counter_CAM_delay[2][edges_beetween_shift_CAM_delay_definition];
double angle_to_edge_CAM_delay[2][edges_beetween_shift_CAM_delay_definition];
double delay_angle_CAM_delay;
double delay_factor_CAM_delay = 1.0;
bool timer_active_CAM_delay[2] = {false, false};
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
unsigned int active_CAM_edges_counter[2] = {0,0};

//** SC_CAM_CRK **
unsigned int sc_type_SC_CAM_CRK = 0;


//***************** UART ********************
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
char message[14] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'z', 'x', 'y'};
//1: COM-error
//2: CRK-configuration ready
//3: CAM-configuration ready
//4: CRK-synchronization ready
//5: CRK-synchronization lost
//6: CAM/CRK-synchronization ready
//7: CAM/CRK-synchronization lost
//8: Failure active
//9: Failure passive
//a: Failure CAM blank out active
//b: Failure CAM blank out passive
//z: Communication validation
//x: Communication receive ready
//y: Communication receive not ready

//### Main Function ###

int main(void) {

    // ## Initialisierung ##

    OSCInit();

    Timer1Init();

    Timer2Init();

    Timer3Init();

    Timer4Init();

    Timer5Init();

    Timer6Init();

    Timer7Init();

    Timer8Init();

    Timer9Init();

    IC1Init();

    IC2Init();

    IC3Init();

    IC4Init();
    
    IC5Init();

    IC6Init();

    Port_G_config();

    Uart2Init();


    TRISAbits.TRISA9 = 0;

    LATAbits.LATA9 = 0;

    // ## Main loop ##
    while (1) {
        //failure processing
        if (configuration_complete){
            Failure_processing(failure_identify);
        }

        //process the received message
        if (message_received == true && com_error == false) {
            UART_receive();
        }

        //reset all values when CRK stalling is detected
        if ((timer_overflow_CRK > 10))// || (timer_overflow_CAM > 5))
        {
            //Stalling_detection();
            Stalling_detection_CRK();
            LATAbits.LATA9 = 1;
        }
        //reset all values when CAM stalling is detected //was not here before
        if ((timer_overflow_CAM > 5)) {
            Stalling_detection_CAM(0);
            Stalling_detection_CAM(1);
            LATAbits.LATA9 = 1;
        }


        //send failure configuration status
        UART_send_failure_configuration_status(failure_identify, failure_configured, failure_configured_CAM_blank_out);

        //check input signal level and set corresponding output level
        Input_signal_observe(output_level_setting);
        
        
        if (CRK_synch) {
            LATAbits.LATA0 = 1;
            LATAbits.LATA3 = 0;
        } else {
            LATAbits.LATA0 = 0;
        }

        if (CRK_synch_temp) {
            LATAbits.LATA1 = 1;
        } else {
            LATAbits.LATA1 = 0;
        }

        if (CRK_synch) {
            LATAbits.LATA9 = 1;
        }
        else{
            LATAbits.LATA9 = 0;
        }
    };
}



// ### Interrupt Functions ###

//## Capture Event rising edge --CRK--

void __attribute__((__interrupt__, no_auto_psv)) _IC1Interrupt(void) {

    CRK_signal = true; //Set actual signal level

    if (failure_active == false) //Set CRK-output
    {
        Output_CRK_no_failure();
    } else if (failure_identify != '1' && failure_identify != '4' && failure_identify != 'f'
            && failure_identify != 'b' && failure_identify != 'i' && failure_identify != 'j' 
            && failure_identify != 'k' && failure_identify != 'l' && failure_identify != 'm')
    {
        Output_CRK_no_failure();
    }

    low_time_CRK = (unsigned long) IC1BUF; //Set actual low time of CRK signal

    Output_CRK(failure_identify); //CRK Output
    timer_overflow_CRK=0; //edge was detected, so no stalling
    IFS0bits.IC1IF = 0; //Clear IC1 Interrupt Flag

}

//## Capture Event falling edge --CRK--

void __attribute__((__interrupt__, no_auto_psv)) _IC2Interrupt(void) {


    CRK_signal = false; //Set actual signal level

    if (failure_active == false) //Set CRK-output
    {
        Output_CRK_no_failure();
    } else if (failure_identify != '1' && failure_identify != '4' && failure_identify != 'f' 
            && failure_identify != 'h' && failure_identify != 'i' && failure_identify != 'j'
            && failure_identify != 'k' && failure_identify != 'l' && failure_identify != 'm')
    {
        Output_CRK_no_failure();
    }

    sync_CRK_preparation(); //CRK synchronisation preparation

    Output_CRK(failure_identify); //CRK Output
    if (configuration_complete == true) {
        sync_CRK(); //CRK synchronization
    }
    timer_overflow_CRK=0; //edge was detected, so no stalling
    IFS0bits.IC2IF = 0; //Clar IC2 Interrupt Flag
}

//## Capture Event rising edge --CAM1--

void __attribute__((__interrupt__, no_auto_psv)) _IC3Interrupt(void) {

    CAM_signal[0] = true; //Set actual signal level

    Output_CAM(failure_identify, 0); //CAM1 Output

    if (configuration_complete == true) {
        sync_CAM_CRK(0); //CAM_CRK synchronization
    }
    timer_overflow_CAM = 0; //edge was detected, so no stalling
    IFS2bits.IC3IF = 0; //Clear IC3 Interrupt Flag
}


//## Capture Event falling edge --CAM1--

void __attribute__((__interrupt__, no_auto_psv)) _IC4Interrupt(void) {

    CAM_signal[0] = false; //Set actual signal level

    Timer3Reset();
    
    Output_CAM(failure_identify, 0); //CAM1 Output

    if (configuration_complete == true) {
        sync_CAM_CRK(0); //CAM_CRK synchronization
    }
    timer_overflow_CAM=0; //edge was detected, so no stalling
    IFS2bits.IC4IF = 0; //Clear IC4 Interrupt Flag
}


//## Capture Event rising edge --CAM2--

void __attribute__((__interrupt__, no_auto_psv)) _IC5Interrupt(void) {
    if(number_of_CAM == 2)
    {
        CAM_signal[1] = true; //Set actual signal level

        Output_CAM(failure_identify, 1); //CAM2 Output

        if (configuration_complete == true) {
            sync_CAM_CRK(1); //CAM_CRK synchronization
        }
        timer_overflow_CAM=0; //edge was detected, so no stalling  
    }
    IFS2bits.IC5IF = 0; //Clear IC5 Interrupt Flag
}


//## Capture Event falling edge --CAM2--

void __attribute__((__interrupt__, no_auto_psv)) _IC6Interrupt(void) {
    if(number_of_CAM == 2)
    {
        CAM_signal[1] = false; //Set actual signal level

        Timer3Reset();

        Output_CAM(failure_identify, 1); //CAM2 Output

        if (configuration_complete == true) {
            sync_CAM_CRK(1); //CAM_CRK synchronization
        }
        timer_overflow_CAM=0; //edge was detected, so no stalling
    }
    IFS2bits.IC6IF = 0; //Clear IC6 Interrupt Flag
}



//## Timer 1 Interrupt: Communication validation

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void) {
    if (communication_active == true) {
        UART_send(message[11]);

        if (communication_validation == true) {
            if (communication_ready == true) {
                communication_ready = false;
            } else {
                failure_identify = '0';
                configuration_complete = false;
                CRK_config = false;
                CAM_config = false;
                communication_active = false;
                communication_validation = false;
                T1CONbits.TON = 0;
                TMR1 = 0x00;
                Stalling_detection();
            }
        }

        if (communication_active == true) {
            communication_validation = !communication_validation;
        }
    }

    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
}

// ********************** Personal part ****************************************************************************************
//? Comments preceded by "//?" will be used to indicate code understanding comments and will be removed when the code is released.
//? Replaced old code will be commented with //§
// *****************************************************************************************************************************

//## Timer 2 Interrupt CRK tooth time

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {

    // all overflows between the events
    timer_overflow_CRK++;

    //§ IFS0bits.T2IF = 0; // Clear Timer2 Interrupt Flag
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);

}

//## Timer 3 Interrupt CAM tooth time

void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void) {

    // all overflows between the events
    //test
    timer_overflow_CAM++;

    //§ IFS0bits.T3IF = 0; // Clear Timer3 Interrupt Flag
    TIM_ClearFlag(TIM3,TIM_FLAG_Update);

}

//## Timer 4 Interrupt: CRK failure circuit-entering

void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void) {
    // all overflows between the events
    timer_overflow_CRK_failure++;

    //§ TMR4 = 0;//? Reset timer (TMR4 contains least significant word of the count for the register pair TMR5:TMR4)
    TIM_SetCounter(TIM4,0);
    //§ IFS1bits.T4IF = 0; // Clear Timer4 Interrupt Flag
    TIM_ClearFlag(TIM4,TIM_FLAG_Update);

}

//## Timer 5 Interrupt: CAM failure circuit-entering

void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void) {

    // all overflows between the events
    timer_overflow_CAM_failure++;

    //§ TMR5 = 0;//? Reset timer (TMR5 contains most significant word of the count for the register pair TMR5:TMR4)
    TIM_SetCounter(TIM5,0);
    //§ IFS1bits.T5IF = 0; // Clear Timer5 Interrupt Flag
    TIM_ClearFlag(TIM5,TIM_FLAG_Update);
}

//## Timer 6 Interrupt: CAM_PER - start value

void __attribute__((__interrupt__, no_auto_psv)) _T6Interrupt(void) {
    //T7CONbits.TON = 1;

    if (failure_identify == '5') { //CAM_PER //?CAM_PER is the error identified by '5'

        //§ LATGbits.LATG7 = !LATGbits.LATG7; //? Inverse pin RG7 value
        if (GPIO_ReadInputDataBit(GPIOG,7)==1)
        {
            GPIO_SetBits(GPIOG,7);
        }
        else if (GPIO_ReadInputDataBit(GPIOG,7)==0)
        {
            GPIO_ResetBits(GPIOG,7);    
        };

        counter_CAM_PER[0]  ++; //? Number of times we lost CAM with timer 6 ?
        if(counter_CAM_PER[0] == 2 ){
            //§ T6CONbits.TON = 0; //? Stop Timer 6
            TIM_Cmd(TIM6,DISABLE);
            counter_CAM_PER[0] = 0; //? Reset timer 6 CAM lost counter
        }

        //§ TMR6 = 0;  // reset the timers counter 
        TIM_SetCounter(TIM6,0);

    } else if (failure_identify == '6') { //CRK_TOOTH_PER

        //§ PR7 = 0x005C;	    // Load the period value 20us  here
        //? Période du timer = Période_Horloge * (PSC+1) * (ARR+1)
        //? Le mieux est d'avoir PSC le plus petit possible
        //? Mais ARR doit pas dépasser (2^16)-1 = 65535
        //? 72Mhz*PSC+1*ARR+1
        TIM_PrescalerConfig(TIM7,0,TIM_PSCReloadMode_Immediate); //? Define PSC value
        TIM_SetAutoreload(TIM7,1439); //? Define ARR value

        //§T7CONbits.TON = 1;//? Activate Timer 7
        TIM_Cmd(TIM7,ENABLE);

        //§ LATGbits.LATG6 = !LATGbits.LATG6;//? Inverse pin LATG6 value
        if (GPIO_ReadInputDataBit(GPIOG,6)==1)
        {
            GPIO_SetBits(GPIOG,6);
        }
        else if (GPIO_ReadInputDataBit(GPIOG,6)==0)
        {
            GPIO_ResetBits(GPIOG,6);    
        };
        
        //§ T6CONbits.TON = 0; //? Stop Timer 6
        TIM_Cmd(TIM6,DISABLE);

    } else if (failure_identify == 'b') { //CRK_SHO_LEVEL

        //§ LATGbits.LATG6 = 1; // set back the CRK level after period //? Write 1 on pin LATG6
        GPIO_SetBits(GPIOG,6);

        //§ T6CONbits.TON = 0;//?Stop timer 6
        TIM_Cmd(TIM6,DISABLE);
    }

    //§ IFS2bits.T6IF = 0; // Clear Timer6 Interrupt Flag
     TIM_ClearFlag(TIM6,TIM_FLAG_Update);
}

//## Timer 7 Interrupt: CAM_PER - pulse duration

void __attribute__((__interrupt__, no_auto_psv)) _T7Interrupt(void) {

    if (failure_identify == '5') // CAM_PER --> Cam_Spk
    {
        //§ LATGbits.LATG8 = !LATGbits.LATG8;//? Inverse pin RG8 value
        if (GPIO_ReadInputDataBit(GPIOG,8)==1)
        {
            GPIO_SetBits(GPIOG,8);
        }
        else if (GPIO_ReadInputDataBit(GPIOG,8)==0)
        {
            GPIO_ResetBits(GPIOG,8);    
        };

        counter_CAM_PER[1] ++;//? Number of times we lost CAM with timer 7 ?
        if(counter_CAM_PER[1] == 2 ){

            //§ T7CONbits.TON = 0; //?Stop timer 7
            TIM_Cmd(TIM7,DISABLE);

            counter_CAM_PER[1] = 0;//?Reset timer 7 CAM counter
        }
        //§ TMR7 = 0;  // reset the timers counter
        TIM_SetCounter(TIM7,0);
    }
    else if (failure_identify == '6')  // CRK_TOOTH_PER
    {
        //§ LATGbits.LATG6 = !LATGbits.LATG6;//? Inverse pin RG6 value
        if (GPIO_ReadInputDataBit(GPIOG,6)==1)
        {
            GPIO_SetBits(GPIOG,6);
        }
        else if (GPIO_ReadInputDataBit(GPIOG,6)==0)
        {
            GPIO_ResetBits(GPIOG,6);    
        };

        //§ T7CONbits.TON = 0;//?Stop timer 7
        TIM_Cmd(TIM7,DISABLE);

    }
    else if (failure_identify == 'j') // SEG_ADP_ER_LIM
    {
        timer_Counter_SEG_ADP_ER_LIM ++;
        switch(timer_Counter_SEG_ADP_ER_LIM)
        {
            case 1:
            { // failure for the falling edge

                //§ LATGbits.LATG6 = 0; //? Write 0 on pin RG6
                GPIO_ResetBits(GPIOG,6);

                if(failure_waiting == true)
                { // if the rising edge has already happen
                    if(sensortype_CRK == 'c') //sensor is cpdd
                    {
                        //§ PR8 = 0x001D;   // 29 * 1.73us = 50.1us //? Period register 8 value set to 50.1 us
                        TIM_PrescalerConfig(TIM8,0,TIM_PSCReloadMode_Immediate);
                        TIM_SetAutoreload(TIM8,3599);
                    }
                    else if(sensortype_CRK == 'h'){ // all the others 
                        //§ PR8 = T_TOOTH_RAW /2;  //? When the sensor is not CPDD, pulse size should be half the previous one (calculated in synchronization)
                        TIM_PrescalerConfig(TIM8,0,TIM_PSCReloadMode_Immediate);
                        TIM_SetAutoreload(TIM8,(T_TOOTH_RAW /2)-1); //? If setted period is more than 910 us PSC should be set higher
                    }
                    else
                    {
                        //§ PR8 = 0x0001; //if sensor typ not set, shouldn't happen
                        TIM_PrescalerConfig(TIM8,0,TIM_PSCReloadMode_Immediate);
                        TIM_SetAutoreload(TIM8,1); 
                    } 

                    //§ T8CONbits.TON = 1;//? Start timer 8
                    TIM_Cmd(TIM8,ENABLE);

                }
                failure_passed = true;
                break;
            }
            case 2:
            { // failure for the rising edge
                //? TODO: #23 Implement SEG_ADP_ER_LIM_reset
                SEG_ADP_ER_LIM_reset();//?SEG_... failure_inactive, passed and waiting =false, init timer 7 & 8, SEG_...error counter reset 
                break;
            } 
        }
        //§ T7CONbits.TON = 0; //?Stop timer 7
        TIM_Cmd(TIM7,DISABLE);

    }
    else if (failure_identify == 'k') // CrkPlsOrng
    {
        //§ LATGbits.LATG6 = 1; //? Write 1 on pin RG6
        GPIO_SetBits(GPIOG,6);

        //§ T7CONbits.TON = 0;//? Stop timer 7
        TIM_Cmd(TIM7,DISABLE);
    }
    else {
        //§ T7CONbits.TON = 0;
        TIM_Cmd(TIM7,DISABLE);
    }//? Stop timer 7
    
    //§ IFS3bits.T7IF = 0; // Clear Timer7 Interrupt Flag
    TIM_ClearFlag(TIM7,TIM_FLAG_Update);


}
/*****************************************************************************/
/*****************************************************************************/

//## Timer 8 Interrupt

void __attribute__((__interrupt__, no_auto_psv)) _T8Interrupt(void) {
    
    if(failure_identify == 'i') { // CRK_GAP_NOT_DET
        timer_Counter_CRK_GAP_NOT_DET++;
        switch(timer_Counter_CRK_GAP_NOT_DET){
            case 1:{   
                LATGbits.LATG6 = 0; 
             
                if(sensortype_CRK == 'c'){
                   PR8 = 0x001D;   // 29 * 1.73us = 50.1us
                }
                else if(sensortype_CRK == 'h'){
                   PR8 = T_TOOTH_RAW /2; 
                }
                else
                {
                   PR8 = 0x0001; //if sensor typ not set, shouldn't happen 
                }
                break;
            }
            case 2:{
                LATGbits.LATG6 = 1;
                T8CONbits.TON = 0;
                timer_Counter_CRK_GAP_NOT_DET = 0;
                failure_active = false;                    
                break;
            }
            default:{
                LATGbits.LATG6 = 1;
                T8CONbits.TON = 0;
                timer_Counter_CRK_GAP_NOT_DET = 0;
                failure_active = false;                    
                break;
            }
        }
    }
    else if (failure_identify == 'j') // SEG_ADP_ER_LIM
    {
        Output_CRK_no_failure();
        SEG_ADP_ER_LIM_reset();
    }  
    TMR8 = 0x00;
    IFS3bits.T8IF = 0; // Clear Timer8 Interrupt Flag
}

//## Timer 9 Interrupt: CAM_PER - pulse duration

void __attribute__((__interrupt__, no_auto_psv)) _T9Interrupt(void) {
    timer_overflow_CAM_REF_CRK++;

    IFS3bits.T9IF = 0; // Clear Timer9 Interrupt Flag
}


//## UART Receive Interrupt

void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void) {

    in = U2RXREG;

    if (U2STAbits.PERR == 1 || U2STAbits.FERR == 1) {
        UART_COM_error();
    } else if (U2STAbits.OERR == 1) {
        UART_COM_error();

        U2STAbits.OERR = 0;
    } else {
        char_counter++;

        if (com_error == false && receiving == true && in != end_char) {
            input_chars[char_counter - 2] = in; //write received char in array
        } else if (com_error == false && in == end_char && receiving == true && char_counter > 2) {
            input_chars[char_counter - 2] = '\0'; //set length of array

            char_counter = 0; //reset counter value
            receiving = false; //reset label that indicates receiving status
            message_received = true; //set label that indicates succesfully received message
        } else if (in == start_char && char_counter == 1) {
            UART_send(message[13]); //send communication receive status
            receiving = true; //set label that indicates receiving status
            com_error = false; //reset COM error, due to received start char
        } else {
            UART_COM_error(); //send failure message
        }
    }

    IFS1bits.U2RXIF = 0; //Clear U2RX Interrupt flag

}


//## UART Transmit Interrupt

void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt(void) {
    IFS1bits.U2TXIF = 0;
}


//## Default Interrupt

void __attribute__((__interrupt__, no_auto_psv)) _DefaultInterrupt(void) {
    while (1);
}


/*****************************************************************************/
/*****************************************************************************/
