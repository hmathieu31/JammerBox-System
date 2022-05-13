/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Input capture                                          */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

// ### Basic includes ###
	#include "ic.h"
	#include "stm32f10x.h"
	#include "stm32f10x_exti.h"
// ### Functions ###

	// ## Input capture 1 Init  ** CRK ** rising edge
	void IC1Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line8;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Rising;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);
	}

	// ## Input capture 2 Init ** CRK ** falling edge 
	void IC2Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line9;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);
	}

	// ## Input capture 2 Init  ** CAM1 ** rising edge
	void IC3Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line10;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Rising;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);
	}

	// ## Input capture 4 Init ** CAM1 ** falling edge 
	void IC4Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line11;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);
	}
    
	// ## Input capture 5 Init ** CAM2 ** rising edge 
	void IC5Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line12;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Rising;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);		
	}

	// ## Input capture 6 Init ** CAM2 ** falling edge 
	void IC6Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line13;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);		
	}    
	
/*****************************************************************************/
/*****************************************************************************/
