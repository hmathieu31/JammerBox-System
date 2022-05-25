/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  USART		                                             */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  18.09.2012                                             */
/* Author          :  Christian Ringlstetter/Thomas Pichler                  */
/*****************************************************************************/

// ### Basic includes ###
	#include "stm32f10x.h"
	#include "stm32f10x_gpio.h"
	#include "port_config.h"	

// ### Functions ###

	void PORT_A_Config(void)
	{	
		GPIO_InitTypeDef GPIOA_Struct;
		GPIOA_Struct.GPIO_Pin=GPIO_Pin_All;
		GPIOA_Struct.GPIO_Speed=GPIO_Speed_2MHz;
		GPIOA_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_StructInit(&GPIOA_Struct);

		GPIO_InitTypeDef USART_TX_Struct;
		USART_TX_Struct.GPIO_Pin = GPIO_Pin_9;
		USART_TX_Struct.GPIO_Speed=GPIO_Speed_2MHz;
		USART_TX_Struct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_StructInit(&USART_TX_Struct);

		GPIO_InitTypeDef USART_RX_Struct;
		USART_RX_Struct.GPIO_Pin = GPIO_Pin_10;
		USART_RX_Struct.GPIO_Speed=GPIO_Speed_2MHz;
		USART_RX_Struct.GPIO_Mode=GPIO_Mode_AIN;
		GPIO_StructInit(&USART_RX_Struct);
	}
	
	void PORT_B_Config(void)
	{
		// We use PORT B as Alternate Input for the EXTI handling
		GPIO_InitTypeDef GPIOB_Struct;
		GPIOB_Struct.GPIO_Pin=GPIO_Pin_All;
		GPIOB_Struct.GPIO_Speed=GPIO_Speed_2MHz;
		GPIOB_Struct.GPIO_Mode=GPIO_Mode_AIN;
		GPIO_StructInit(&GPIOB_Struct);
	}
/*****************************************************************************/
/*****************************************************************************/
