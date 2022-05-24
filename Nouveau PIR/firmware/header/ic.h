/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Input capture                                          */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

#ifndef _IC_H_
#define _IC_H_

// ### Functions ###

	// ## Input capture 1 Init  ** CRK ** falling edge  
	void EXTI8Init(void);

	// ## Input capture 2 Init  ** CRK ** rising edge
	void EXTI9Init(void);

	// ## Input capture 3 Init  ** CAM1 ** falling edge 
	void EXTI14Init(void);

	// ## Input capture 4 Init  ** CAM1 ** rising edge
	void EXTI11Init(void);

    // ## Input capture 5 Init  ** CAM2 ** falling edge 
	void EXTI12Init(void);
    
    // ## Input capture 6 Init  ** CAM2 ** rising edge
	void EXTI13Init(void);
    
	
#endif
/*****************************************************************************/
/*****************************************************************************/
