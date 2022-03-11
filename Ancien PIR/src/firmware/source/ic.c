/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Input capture                                          */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Grégoire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

// ### Basic includes ###
	#include "p33FJ256GP710A.h"
	#include "ic.h"

// ### Functions ###

	// ## Input capture 1 Init  ** CRK ** rising edge
	void IC1Init(void){

		IC1CONbits.ICSIDL = 0;		//Input capture continues in idle mode
		IC1CONbits.ICTMR = 1;		//Input capture timer select(TMR2)
		IC1CONbits.ICI = 0b00;		//Interrupt on every capture event
		IC1CONbits.ICM = 0b011;		//Caputure mode, every rising edge


		IPC0bits.IC1IP = 0x03; 		//Set IC1 Interrupt Priority Level
		IFS0bits.IC1IF = 0; 		//Clear IC1 Interrupt Flag
		IEC0bits.IC1IE = 1; 		//Enable IC1 interrupt
		
		TRISDbits.TRISD8 = 1;		//IC1 is input port
		
	}

	// ## Input capture 2 Init ** CRK ** falling edge 
	void IC2Init(void){

		IC2CONbits.ICSIDL = 0;		//Input capture continues in idle mode
		IC2CONbits.ICTMR = 1;		//Input capture timer select (TMR2)
		IC2CONbits.ICI = 0b00;		//Interrupt on every capture event
		IC2CONbits.ICM = 0b010;		//Caputure mode, every falling edge


		IPC1bits.IC2IP = 0x03; 		//Set IC2 Interrupt Priority Level
		IFS0bits.IC2IF = 0; 		//Clear IC2 Interrupt Flag
		IEC0bits.IC2IE = 1; 		//Enable IC2 interrupt
		
		TRISDbits.TRISD9 = 1;		//IC2 is input port
		
	}

	// ## Input capture 2 Init  ** CAM1 ** rising edge
	void IC3Init(void){
		
		IC3CONbits.ICSIDL = 0;		//Input capture continues in idle mode
		IC3CONbits.ICTMR = 0;		//Input capture timer select(TMR3)
		IC3CONbits.ICI = 0b00;		//Interrupt on every capture event
		IC3CONbits.ICM = 0b011;		//Caputure mode, every rising edge


		
		IPC9bits.IC3IP = 0x02; 		//Set IC3 Interrupt Priority Level
		IFS2bits.IC3IF = 0; 		//Clear IC3 Interrupt Flag
		IEC2bits.IC3IE = 1; 		//Enable IC3 interrupt

		TRISDbits.TRISD10 = 1;		//IC3 is input port
		

	}

	// ## Input capture 4 Init ** CAM1 ** falling edge 
	void IC4Init(void){

		IC4CONbits.ICSIDL = 0;		//Input capture continues in idle mode
		IC4CONbits.ICTMR = 0;		//Input capture timer select (TMR3)
		IC4CONbits.ICI = 0b00;		//Interrupt on every capture event
		IC4CONbits.ICM = 0b010;		//Caputure mode, every falling edge


		IPC9bits.IC4IP = 0x02; 		//Set IC4 Interrupt Priority Level
		IFS2bits.IC4IF = 0; 		//Clear IC4 Interrupt Flag
		IEC2bits.IC4IE = 1; 		//Enable IC4 interrupt
		
		TRISDbits.TRISD11 = 1;		//IC4 is input port
		
	}
    
	// ## Input capture 5 Init ** CAM2 ** rising edge 
	void IC5Init(void){

		IC5CONbits.ICSIDL = 0;		//Input capture continues in idle mode
		IC5CONbits.ICTMR = 0;		//Input capture timer select (TMR3)
		IC5CONbits.ICI = 0b00;		//Interrupt on every capture event
		IC5CONbits.ICM = 0b011;		//Caputure mode, every rising edge


		IPC9bits.IC5IP = 0x02; 		//Set IC5 Interrupt Priority Level
		IFS2bits.IC5IF = 0; 		//Clear IC5 Interrupt Flag
		IEC2bits.IC5IE = 1; 		//Enable IC5 interrupt
		
		TRISDbits.TRISD12 = 1;		//IC5 is input port
		
	}

	// ## Input capture 6 Init ** CAM2 ** falling edge 
	void IC6Init(void){

		IC6CONbits.ICSIDL = 0;		//Input capture continues in idle mode
		IC6CONbits.ICTMR = 0;		//Input capture timer select (TMR3)
		IC6CONbits.ICI = 0b00;		//Interrupt on every capture event
		IC6CONbits.ICM = 0b010;		//Caputure mode, every falling edge


		IPC10bits.IC6IP = 0x02; 	//Set IC6 Interrupt Priority Level
		IFS2bits.IC6IF = 0; 		//Clear IC6 Interrupt Flag
		IEC2bits.IC6IE = 1; 		//Enable IC6 interrupt
		
		TRISDbits.TRISD13 = 1;		//IC6 is input port
		
	}    
	
/*****************************************************************************/
/*****************************************************************************/
