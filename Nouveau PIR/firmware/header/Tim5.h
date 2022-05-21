#ifndef _TIM5_H_
#define _TIM5_H_


/* Rajoute dans TIM2 interruption handler
  if (tim5_Counting){
        tim5_CounterOverflow++;;
    }
*/

extern int tim5_CounterOverflow;
extern int tim5_Counting;



void Tim5_Start(void);

void Tim5_Stop(void);

void Tim5_Reset(void);

int Tim5_GetTicks(void);

#endif