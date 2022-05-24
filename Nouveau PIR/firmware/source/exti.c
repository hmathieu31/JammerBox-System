/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Input capture                                          */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

// ### Basic includes ###
	#include "exti.h"
	#include "stm32f10x.h"
	#include "stm32f10x_exti.h"
// ### Functions ###

	// ## EXTI8 Init  ** CRK ** rising edge
	void EXTI8Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line8;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Rising;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);
	}

	// ## EXTI9 Init ** CRK ** falling edge 
	void EXTI9Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line9;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);
	}

	// ## EXTI11 Init ** CAM1 ** falling edge 
	void EXTI11Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line11;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);
	}
    
	// ## EXTI12 Init ** CAM2 ** rising edge 
	void EXTI12Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line12;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Rising;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);		
	}

	// ## EXTI13 Init ** CAM2 ** falling edge 
	void EXTI13Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line13;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);		
	} 

	// ## EXTI14 Init  ** CAM1 ** rising edge
	void EXTI14Init(void){
		EXTI_InitTypeDef EXTI_Struct;
		EXTI_StructInit(&EXTI_Struct);
		EXTI_Struct.EXTI_Line=EXTI_Line14;
		EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Rising;
		EXTI_Struct.EXTI_LineCmd=ENABLE;
		EXTI_Init(&EXTI_Struct);
	}   
	
/*****************************************************************************/
/*****************************************************************************/
