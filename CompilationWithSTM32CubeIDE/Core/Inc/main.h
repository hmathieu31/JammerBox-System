/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CRK_synch_Pin GPIO_PIN_0
#define CRK_synch_GPIO_Port GPIOA
#define CRK_synch_temp_Pin GPIO_PIN_1
#define CRK_synch_temp_GPIO_Port GPIOA
#define first_CRK_synch_Pin GPIO_PIN_2
#define first_CRK_synch_GPIO_Port GPIOA
#define second_CRK_synch___CAM_Overflow___CRK_Overflow_Pin GPIO_PIN_3
#define second_CRK_synch___CAM_Overflow___CRK_Overflow_GPIO_Port GPIOA
#define CRK_TOOTH_PER___CRK_SHO_LEVEL___SEG_ADP_ER_LIM___CrkPlsOrng___CRK_GAP_NOT_DET_Pin GPIO_PIN_4
#define CRK_TOOTH_PER___CRK_SHO_LEVEL___SEG_ADP_ER_LIM___CrkPlsOrng___CRK_GAP_NOT_DET_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define CAM_PER_cam_spk_Pin GPIO_PIN_6
#define CAM_PER_cam_spk_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
