/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  UART		                                             */
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
		GPIO_StructInit(&GPIOA_Struct);
		GPIOA_Struct.GPIO_Pin=GPIO_Pin_All;
		GPIOA_Struct.GPIO_Speed=GPIO_Speed_2MHz;
		GPIOA_Struct.GPIO_Mode=GPIO_Mode_Out_PP;			
	}
	
	void PORT_B_Config(void)
	{
		GPIO_InitTypeDef GPIOB_Struct;
		GPIO_StructInit(&GPIOB_Struct);
		GPIOB_Struct.GPIO_Pin=GPIO_Pin_All;
		GPIOB_Struct.GPIO_Speed=GPIO_Speed_2MHz;
		GPIOB_Struct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	}
/*****************************************************************************/
/*****************************************************************************/
