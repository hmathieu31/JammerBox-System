#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
/*!!!!! Rajoute dans TIM2 Handler:
    if (tim5_Counting){
        tim5_CounterOverflow++;;
    }
*/
int tim4_StartTime;
int tim4_StopTime;
int tim4_CounterOverflow;
int tim4_Counting; //boolean
int tim4_TicksCounted ;

struct TIMER {
   int CNT;
   int Arr;
   int PSC;
}TIMER;

struct TIMER TIM2;

void tim4_Start(void){
    tim4_StartTime = TIM2.CNT;
    tim4_Counting = 1;
}

void tim4_Stop(void){
    tim4_Counting = 0;
    tim4_StopTime = TIM2.CNT;
    tim4_TicksCounted = ((tim4_StopTime - tim4_StartTime) + tim4_CounterOverflow*(TIM2.Arr))%TIM2.Arr;
}

void Tim4_Reset(){
    tim4_StartTime = 0;
    tim4_StopTime = 0;
    tim4_TicksCounted = 0;
    tim4_CounterOverflow = 0;
}

int Tim4_GetTicks(){
    if (tim4_Counting){
        return ((TIM2.CNT - tim4_StartTime) + tim4_CounterOverflow*(TIM2.Arr));
    } else {
        return tim4_TicksCounted;
    }
    
}

int run = 1;

void *myThreadFun(void *vargp)
{
    while (run){
        usleep(100);
        TIM2.CNT ++;//= (TIM2.CNT + 1)%TIM2.Arr;
    }
    printf("Done thread\n");
    return NULL;
}
   
int main()
{
    TIM2.Arr = 62999;
    TIM2.PSC = 479;

    pthread_t thread_id;

    pthread_create(&thread_id, NULL, myThreadFun, NULL);

    Tim4_Reset();
    tim4_Start();
    sleep(3);
    tim4_Stop();

    printf("Ticks: %i\n", Tim4_GetTicks());
    run = 0;
    
    return 0;
}
