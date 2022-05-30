/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Input capture                                          */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Grégoire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

#ifndef _IC_H_
#define _IC_H_

// ### Functions ###

	// ## Input capture 1 Init  ** CRK ** falling edge  
	void IC1Init(void);

	// ## Input capture 2 Init  ** CRK ** rising edge
	void IC2Init(void);

	// ## Input capture 3 Init  ** CAM1 ** falling edge 
	void IC3Init(void);

	// ## Input capture 4 Init  ** CAM1 ** rising edge
	void IC4Init(void);

    // ## Input capture 5 Init  ** CAM2 ** falling edge 
	void IC5Init(void);
    
    // ## Input capture 6 Init  ** CAM2 ** rising edge
	void IC6Init(void);
    
	
#endif
/*****************************************************************************/
/*****************************************************************************/
