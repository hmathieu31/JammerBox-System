/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Oscillator                                             */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  18.09.2012                                             */
/* Author          :  Christian Ringlstetter/Thomas Pichler                  */
/*****************************************************************************/

// ### Basic includes ###
	#include "p33FJ256GP710A.h"
	#include "osc.h"

// ### Functions ###

	// ## OSC Init ##
	void OSCInit(void){
	
	    // Configure Oscillator to operate the device at 40Mhz
	        // Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
	        // Fosc= 7,37M*40/(2*2)=73,7Mhz
	    	PLLFBD=38;				// M=40
			CLKDIVbits.DOZE=0b000;  // No prozessor clock reduction
	    	CLKDIVbits.PLLPOST=0;	// N1=2
	    	CLKDIVbits.PLLPRE=0;	// N2=2
	    	OSCTUN=0;				// Tune FRC oscillator, if FRC is used
	
	    //Disable Watch Dog Timer
	    	RCONbits.SWDTEN=0;
	
	    //Clock switch to incorporate PLL
		    __builtin_write_OSCCONH(0b001);		// Initiate Clock Switch to Fast RC with PLL
		    __builtin_write_OSCCONL(0x01);		// Start clock switching
	  
	    // Wait for Clock switch to occur
	        while (OSCCONbits.COSC != 0b001);		
	
	    // Wait for PLL to lock
		    while(OSCCONbits.LOCK!=1){};
    
	}
	
	
/*****************************************************************************/
/*****************************************************************************/
