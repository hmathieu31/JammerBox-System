/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  UART		                                             */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  18.09.2012                                             */
/* Author          :  Christian Ringlstetter/Thomas Pichler                  */
/*****************************************************************************/

// ### Basic includes ###
	// #include "p33FJ256GP710A.h"
	#include "port_config.h"
	#include "wiringPi.h"	

// ### Functions ###

	void GPIOs_config(void)
	{	
		pinMode(6, OUTPUT);
	}
	
	
/*****************************************************************************/
/*****************************************************************************/
