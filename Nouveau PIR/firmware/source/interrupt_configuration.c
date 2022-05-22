/*********************************************************************
 * \file   interrupt_configuration.c                                 *
 * \brief  Configuration of the interrupts used						 *
 *                                                                   *
 * \author Hugo Mathieu                                              *
 * \date   May 2022													 *
 ********************************************************************/

#include "interrupt_configuration.h"

// ### Hardware specific includes ###
#include "misc.h"

// ### Static variables ###

static NVIC_InitTypeDef NVIC_InitStructure_timer1 = {
        
    .NVIC_IRQChannel = TIM1_UP_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    // An interrupt on every timer is not preemptable
    .NVIC_IRQChannelSubPriority = 1,
    .NVIC_IRQChannelCmd = ENABLE
};

static NVIC_InitTypeDef NVIC_InitStructure_timer2 = {
    .NVIC_IRQChannel = TIM2_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    // An interrupt on every timer is not preemptable
    .NVIC_IRQChannelSubPriority = 1,
    .NVIC_IRQChannelCmd = ENABLE
};

static NVIC_InitTypeDef NVIC_InitStructure_timer3 = {
    .NVIC_IRQChannel = TIM3_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    // An interrupt on every timer is not preemptable
    .NVIC_IRQChannelSubPriority = 1,
    .NVIC_IRQChannelCmd = ENABLE
};

static NVIC_InitTypeDef NVIC_InitStructure_timer4 = {
    .NVIC_IRQChannel = TIM4_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    // An interrupt on every timer is not preemptable
    .NVIC_IRQChannelSubPriority = 1,
    .NVIC_IRQChannelCmd = ENABLE 
};


// ### Functions ###

void interrupt_enable_timer1(void)
{
    NVIC_Init(&NVIC_InitStructure_timer1);
}

void interrupt_enable_timer2(void)
{
    NVIC_Init(&NVIC_InitStructure_timer2);
}

void interrupt_enable_timer3(void)
{
    NVIC_Init(&NVIC_InitStructure_timer3);
}

void interrupt_enable_timer4(void)
{
    NVIC_Init(&NVIC_InitStructure_timer4);
}
