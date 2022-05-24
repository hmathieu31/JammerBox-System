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
void Systick_SetPeriod(float Duration_us) {
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
