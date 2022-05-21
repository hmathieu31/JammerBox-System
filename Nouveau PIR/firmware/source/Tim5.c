#include "Tim5.h"

int tim5_StartTick = 0;
int tim5_StopTick = 0;
int tim5_CounterOverflow = 0;
int tim5_Counting = 0; //boolean
int tim5_TicksCounted = 0;

void tim5_Start(void){
    if (tim5_Counting){} //Dont do anything
    else {
        tim5_StartTick = TIM1->CNT;
        tim5_Counting = 1;
    }
}

void tim5_Stop(void){
    if (tim5_Counting){    
        tim5_Counting = 0;
        tim5_StopTick = TIM1->CNT;
        tim5_TicksCounted += ((tim5_StopTick - tim5_StartTick) + 
            tim5_CounterOverflow*(TIM1->Arr))%TIM1->Arr;
        tim5_CounterOverflow = 0;
    }
}

void Tim5_Reset(){
    tim5_StartTick = 0;
    tim5_StopTick = 0;
    tim5_TicksCounted = 0;
    tim5_CounterOverflow = 0;
}

int Tim5_GetCounter(){
    if (tim5_Counting){
        return ((TIM1->CNT - tim5_StartTick) + 
            tim5_CounterOverflow*(TIM1->Arr))%TIM1->Arr;
    } else {
        return tim5_TicksCounted;
    }
    
}

void TIM1_init(){
    TIM1->Arr = 62999;
    TIM1->PSC = 479;
}
