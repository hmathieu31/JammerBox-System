/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    	  main.c
 * @brief   	  Main program
 * 				  Project name	: STM32-Jammerbox
 * 				  Controller	: STM32F103RB
 * @date		  25 May 2022
 ******************************************************************************
 * @attention
 *
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_hal_gpio.h"

#include "synchronization.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ### EXTI Callback functions ###
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == 8) // Capture Event rising edge --CRK--
	{
		CRK_signal = true; // Set actual signal level

		if (failure_active == false) // Set CRK-output
		{
			output_CRK_no_failure();
		}
		else if (failure_identify != '1' && failure_identify != '4'
				&& failure_identify != 'f' && failure_identify != 'b'
				&& failure_identify != 'i' && failure_identify != 'j'
				&& failure_identify != 'k' && failure_identify != 'l'
				&& failure_identify != 'm')
		{
			output_CRK_no_failure();
		}

		low_time_CRK = IC1BUF; // Set actual low time of CRK signal

		output_CRK(failure_identify); // CRK Output
		timer_overflow_CRK = 0;       // edge was detected, so no stalling

	}

	if (GPIO_Pin == 9) //## Capture Event falling edge --CRK--
	{
		CRK_signal = false; // Set actual signal level

		if (failure_active == false) // Set CRK-output
		{
			output_CRK_no_failure();
		}
		else if (failure_identify != '1' && failure_identify != '4'
				&& failure_identify != 'f' && failure_identify != 'h'
				&& failure_identify != 'i' && failure_identify != 'j'
				&& failure_identify != 'k' && failure_identify != 'l'
				&& failure_identify != 'm')
		{
			output_CRK_no_failure();
		}

		sync_CRK_preparation(); // CRK synchronisation preparation

		output_CRK(failure_identify); // CRK Output
		if (configuration_complete == true)
		{
			sync_CRK(); // CRK synchronisation
		}
		timer_overflow_CRK = 0; // edge was detected, so no stalling
	}

	if (GPIO_Pin == 14) //## Capture Event rising edge --CAM1--
	{

		CAM_signal[0] = true; // Set actual signal level

		output_CAM(failure_identify, 0); // CAM1 Output

		if (configuration_complete == true)
		{
			sync_CAM_CRK(0); // CAM_CRK Synchronisation
		}
		timer_overflow_CAM = 0; // edge was detected, so no stalling
	}

	if (GPIO_Pin == 11)	//## Capture Event falling edge --CAM1--
	{
		CAM_signal[0] = false;	// Set actual signal level

		TIM2_Reset();

		output_CAM(failure_identify, 0);	// CAM1 Output

		if (configuration_complete == true)
		{
			sync_CAM_CRK(0); // CAM_CRK Synchronisation
		}
		timer_overflow_CAM = 0; // edge was detected, so no stalling
	}

	if (GPIO_Pin == 12) //## Capture Event rising edge --CAM2--
	{
		CAM_signal[1] = true; // Set actual signal level

		output_CAM(failure_identify, 1); // CAM2 Output

		if (configuration_complete == true)
		{
			sync_CAM_CRK(1); // CAM_CRK Synchronisation
		}
		timer_overflow_CAM = 0; // edge was detected, so no stalling
	}

	if (GPIO_Pin == 13) //## Capture Event falling edge --CAM2--
	{
		if (number_of_CAM == 2)
		{
			CAM_signal[1] = false; // Set actual signal level

			TIM2_Reset();

			output_CAM(failure_identify, 1); // CAM2 Output

			if (configuration_complete == true)
			{
				sync_CAM_CRK(1); // CAM_CRK Synchronisation
			}
			timer_overflow_CAM = 0; // edge was detected, so no stalling
		}
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_USART1_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
