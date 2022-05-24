/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  EXTIs			                                         */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

#ifndef _EXTI_H_
#define _EXTI_H_

// ### Functions ###

	// ## EXTI8 Init  ** CRK ** falling edge  
	void EXTI8Init(void);

	// ## EXTI9 Init  ** CRK ** rising edge
	void EXTI9Init(void);

	// ## EXTI11 Init  ** CAM1 ** rising edge
	void EXTI11Init(void);

    // ## EXTI12 Init  ** CAM2 ** falling edge 
	void EXTI12Init(void);
    
    // ## EXTI13 Init  ** CAM2 ** rising edge
	void EXTI13Init(void);

	// ## EXTI14 Init  ** CAM1 ** falling edge 
	void EXTI14Init(void);
    
	
#endif
/*****************************************************************************/
/*****************************************************************************/
