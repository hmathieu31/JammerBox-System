
#include "Tim5.h"
#include "stm32f10x_tim.h"
#include "timer.h"
#include "stm32f10x.h"

int tim5_StartTick = 0;
int tim5_StopTick = 0;
int tim5_CounterOverflow = 0;
int tim5_Counting = 0; //boolean
int tim5_TicksCounted = 0;

void Tim5_Start(void){
    if (tim5_Counting){} //Dont do anything
    else {
        tim5_StartTick = TIM_GetCounter(TIM1);
        tim5_Counting = 1;
    }
}

void Tim5_Stop(void){
    if (tim5_Counting){    
        tim5_Counting = 0;
        tim5_StopTick = TIM1->CNT;
        tim5_TicksCounted += ((tim5_StopTick - tim5_StartTick) + 
            tim5_CounterOverflow*(TIM1->ARR))%TIM1->ARR;
        tim5_CounterOverflow = 0;
    }
}

void Tim5_Reset(void){
    tim5_StartTick = 0;
    tim5_StopTick = 0;
    tim5_TicksCounted = 0;
    tim5_CounterOverflow = 0;
}

int Tim5_GetCounter(void){
    if (tim5_Counting){
        return ((TIM1->CNT - tim5_StartTick) + 
            tim5_CounterOverflow*(TIM1->ARR))%TIM1->ARR;
    } else {
        return tim5_TicksCounted;
    }
    
}
