/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Configuration Bits                                     */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  18.09.2012                                             */
/* Author          :  Christian Ringlstetter/Thomas Pichler                  */
/*****************************************************************************/

#ifndef _CONFIG_H_
#define _CONFIG_H_

	//// Fast RC oscillator (internal)
	_FOSCSEL(FNOSC_FRCPLL);               
	//
	//// Only clock switching enabled & OSC2 Pin OSC2 is clock O/P & XT oscillator
	_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
	//
	//// Watchdog Timer disabled
	_FWDT(FWDTEN_OFF);
	

	//_FOSCSEL(FNOSC_PRIPLL);
	//_FOSC(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMD_XT);
	//_FWDT(FWDTEN_OFF);


#endif
/*****************************************************************************/
/*****************************************************************************/
