/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  UART		                                             */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  18.09.2012                                             */
/* Author          :  Christian Ringlstetter/Thomas Pichler                  */
/*****************************************************************************/

// ### Basic includes ###
	#include "p33FJ256GP710A.h"
	#include "port_config.h"	

// ### Functions ###

	void Port_G_config(void)
	{	
		TRISG = 0xF20F;
	}
	
	
/*****************************************************************************/
/*****************************************************************************/
