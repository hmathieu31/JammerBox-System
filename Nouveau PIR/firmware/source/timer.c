/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Timer                                                  */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

// ### Hardware includes ###
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

// ### Basic includes ###
#include "Tim5.h"
#include "interrupt_configuration.h"
#include "timer.h"

// ### Variables ###

extern unsigned long timer_overflow_CRK;
extern unsigned long timer_overflow_CAM;
extern unsigned long timer_overflow_CRK_failure;
extern unsigned long timer_overflow_CAM_failure;
extern unsigned long timer_overflow_CAM_REF_CRK;

// ### Functions ###
// Returns the computed value, 0 if impossible
float Systick_SetPeriod(float Duration_us) {
    vu32 Nb_Reload;
    float Nb_Reload_Float;
    float Real_Duration_us;
    float In_Freq;

    In_Freq = SystemCoreClock;

    Nb_Reload_Float = Duration_us * In_Freq / 1000000.0;
    Nb_Reload = (float)Nb_Reload_Float;
    Real_Duration_us = ((float)Nb_Reload) / In_Freq * 1000000.0;

    // Limit testing
    // No prescaler
    SysTick->CTRL = (SysTick->CTRL) | 1 << 2;
    if (Nb_Reload_Float >= 16777215.0)  // 2^24-1 max
    {
        // Fix the prescaler to 8
        SysTick->CTRL = (SysTick->CTRL) & ~(1 << 2);
        Nb_Reload_Float = Duration_us * In_Freq / 8000000.0;
        Nb_Reload = (float)Nb_Reload_Float;
        Real_Duration_us = ((float)Nb_Reload) / In_Freq * 8000000.0;
    }

    if (Nb_Reload_Float >= 16777215.0)  // 2^24-1 max
    {
        Real_Duration_us = 0.0;
    }

    SysTick->LOAD = Nb_Reload;

    return Real_Duration_us;
}

// ## Timer2 Init **Prescaler: 64; CRK Synchronization; tooth time**
void TIM1Init(void) {
    if (tim5_Counting) {
        tim5_CounterOverflow++;
    }
    // Aim: resolution of < 2 �s;
    // FCPU with PLL = 73,7 MHz
    // Fcy: 36,85 MHz
    // 36,85 Mhz/ 64 = 575,78 kHz = 1,7367744624683038660599534544444�s
    TIM_Cmd(TIM1, DISABLE);  // Disable Timer1
    // No idle mode handling necessary on STM32
    TIM_ITConfig(TIM1, TIM_IT_Trigger, DISABLE);  // Disable Trigger Interrupt (called Gated Timer mode on Microchip)
    TIM_InternalClockConfig(TIM1);                // Tell the STM32 to use the internal clock (ticking at 72MHz)
    TIM_SetCounter(TIM1, 0);                      // Clear Timer1 counter
    // TIM_period = (1/72MHz) * (PSC+1) *(ARR+1)
    // (1/72MHz) * (119+1) * (62999+1) = 105ms
    TIM_PrescalerConfig(TIM1, 119, TIM_PSCReloadMode_Immediate);
    TIM_SetAutoreload(TIM1, 62999);

    interrupt_enable_timer1();                  // Enable the Timer1 Interrupt in the NVIC
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);       // Clear Timer1 Interrupt Flag
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);  // Enable Timer1 interrupt
    TIM_Cmd(TIM1, ENABLE);                      // Start Timer
}

// ## Timer3 Init **CAM Synchronization; segment time**
void TIM2Init(void) {
    // Aim: high timer duration
    // FCPU with PLL = 73,7 MHz
    // Fcy: 36,85 MHz
    // 36,85 Mhz/ 256 = 143,95 kHz = 6.946 �s
    TIM_Cmd(TIM2, DISABLE);  // Disable Timer2
    // No idle mode handling necessary on STM32
    TIM_ITConfig(TIM2, TIM_IT_Trigger, DISABLE);  // Disable Trigger Interrupt (called Gated Timer mode on Microchip)
    TIM_InternalClockConfig(TIM2);                // Tell the STM32 to use the internal clock (ticking at 72MHz)
    TIM_SetCounter(TIM2, 0);                      // Clear Timer2 counter
    // TIM_period = (1/72MHz) * (PSC+1) *(ARR+1)
    // (1/72MHz) * (479+1) * (62999+1) = 420ms
    TIM_PrescalerConfig(TIM2, 479, TIM_PSCReloadMode_Immediate);
    TIM_SetAutoreload(TIM2, 62999);

    interrupt_enable_timer2();                  // Enable the Timer2 Interrupt in the NVIC
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);       // Clear Timer2 Interrupt Flag
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // Enable Timer2 interrupt
    TIM_Cmd(TIM2, ENABLE);                      // Start Timer
}

// ## Timer6 Init **CAM_PER/CRK_TOOTH_PER(start-value)//CRK_SHO_LEVEL pulse duration**
void Timer3Init(void) {
    // Aim: Timer ticks < 1 �s
    // FCPU with PLL = 73,7 MHz
    // Fcy: 36,85 MHz
    // 36,85 Mhz/ 8 = 4606 kHz = 0.217 �s
    TIM_Cmd(TIM3, DISABLE);  // Disable Timer3
    // No idle mode handling necessary on STM32
    TIM_ITConfig(TIM3, TIM_IT_Trigger, DISABLE);  // Disable Trigger Interrupt (called Gated Timer mode on Microchip)
    TIM_InternalClockConfig(TIM3);                // Tell the STM32 to use the internal clock (ticking at 72MHz)
    TIM_SetCounter(TIM3, 0);                      // Clear Timer3 counter
    // TIM_period = (1/72MHz) * (PSC+1) *(ARR+1)
    // (1/72MHz) * (15+1) * (62999+1) = 14ms
    TIM_PrescalerConfig(TIM3, 15, TIM_PSCReloadMode_Immediate);
    TIM_SetAutoreload(TIM3, 62999);

    interrupt_enable_timer3();                  // Enable the Timer3 Interrupt in the NVIC
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);       // Clear Timer3 Interrupt Flag
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  // Enable Timer3 interrupt
}

// ## Timer4 Init **Prescaler: 8; CAM_PER/CRK_TOOTH_PER(pulse duration)**
void Timer4Init(void) {
    // Aim: Timer ticks < 1 �s
    // FCPU with PLL = 73,7 MHz
    // Fcy: 36,85 MHz
    // 36,85 Mhz/ 8 = 4606 kHz = 0.217 �s
    TIM_Cmd(TIM4, DISABLE);  // Disable Timer4
    // No idle mode handling necessary on STM32
    TIM_ITConfig(TIM4, TIM_IT_Trigger, DISABLE);  // Disable Trigger Interrupt (called Gated Timer mode on Microchip)
    TIM_InternalClockConfig(TIM4);                // Tell the STM32 to use the internal clock (ticking at 72MHz)
    TIM_SetCounter(TIM4, 0);                      // Clear Timer4 counter
    // TIM_period = (1/72MHz) * (PSC+1) *(ARR+1)
    // (1/72MHz) * (0+1) * (719+1) = 10µs
    TIM_PrescalerConfig(TIM4, 0, TIM_PSCReloadMode_Immediate);
    TIM_SetAutoreload(TIM4, 719);

    interrupt_enable_timer4();                  // Enable the Timer4 Interrupt in the NVIC
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);       // Clear Timer4 Interrupt Flag
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  // Enable Timer4 interrupt
}

// ## SysTick Timer Init **Prescaler: 64; CRK_RUN_OUT/CAM_delay**
void SysTickInit(void) {
    // FCPU with PLL = 73,7 MHz
    // Fcy: 36,85 MHz
    // 36,85 Mhz/ 64 = 575,78 kHz = 1.73 µs

    // Disable timer
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
    // Systick is not subject to any idle mode
    SysTick->VAL = (2 ^ 24) - 1;  // Clear Systick count (Systick is count down and on 24 bits)
    // Set to a 120ms period
    Systick_SetPeriod(120000.0);
    NVIC_SetPriority(SysTick_IRQn, 2);  // Set Systick interrupt priority
    // No need to reset flag in systick
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;  // Enable Systick interrupt
}

//## Timer2Reset **Prescaler: 64; CRK Synchronization; tooth time**
void TIM1Reset(void) {
    TIM_SetCounter(TIM1, 0);  // Reset Timer2 sur l'ancien PIR, TIM1 pour nous
    timer_overflow_CRK = 0;
}

//## TIM2Reset **Prescaler: 256; CAM Synchronization; segment time**
void TIM2Reset(void) {
    TIM_SetCounter(TIM2, 0);  // Reset Timer3
    timer_overflow_CAM = 0;
}

/*****************************************************************************/
/*****************************************************************************/
