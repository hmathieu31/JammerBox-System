/**
  ******************************************************************************
  * @file    stm32f1xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-February-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32f1xx_it.h"

/* Hardware includes ---------------------------------------------------------*/
#include "failures.h"

/** @addtogroup IO_Toggle
  * @{
  */

/* External variables --------------------------------------------------------*/
extern bool failure_active;
extern char failure_identify;
extern char sensortype_CRK;
extern unsigned long T_TOOTH_RAW;
extern unsigned int timer_Counter_CRK_GAP_NOT_DET;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                          */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    if (failure_identify == 'i')
    { // CRK_GAP_NOT_DET
        timer_Counter_CRK_GAP_NOT_DET++;
        switch (timer_Counter_CRK_GAP_NOT_DET)
        {
        case 1: {
            GPIO_ResetBits(GPIOA, 4);

            if (sensortype_CRK == 'c')
            {
                //§ PR8 = 0x001D;   // 29 * 1.73us = 50.1us
                SysTick_Config(3600); //? 72MHz*50us
            }
            else if (sensortype_CRK == 'h')
            {
                SysTick_Config((T_TOOTH_RAW / 2) - 1);
            }
            else
            {
                SysTick_Config(1);
            }
            break;
        }
        case 2: {
            GPIO_SetBits(GPIOA, 4);

            SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

            timer_Counter_CRK_GAP_NOT_DET = 0;
            failure_active = false;
            break;
        }
        default: {
            GPIO_SetBits(GPIOA, 4);

            SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
            timer_Counter_CRK_GAP_NOT_DET = 0;
            failure_active = false;
            break;
        }
        }
    }
    else if (failure_identify == 'j') // SEG_ADP_ER_LIM
    {
        output_CRK_no_failure();
        SEG_ADP_ER_LIM_reset();
    }
    SysTick->VAL = (2^24)-1;  //clear systick count
}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_md.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
