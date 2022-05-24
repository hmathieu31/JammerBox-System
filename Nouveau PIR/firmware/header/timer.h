/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Timer                                                  */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  18.09.2012                                             */
/* Author          :  Christian Ringlstetter/Thomas Pichler                  */
/*****************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

// ### Functions ###

	// Set period of Systick timer
	void Systick_SetPeriod(float);
	// ## Timer2 Init **Prescaler: 64; CRK Synchronization; tooth time** 

	void SysTickInit(void);
	//## Timer2Reset **Prescaler: 64; CRK Synchronization; tooth time** 

	void TIM1Reset(void);

	//## Timer3Reset **Prescaler: 256; CAM Synchronization; segment time** 

	void TIM2Reset(void); 

	//## Timer4Reset **Prescaler: 64; CRK_NO_SIG/CAM_delay** 

	void Timer4Reset(void);

	//## Timer5Reset **CAM Prescaler: 256; CAM_NO_SIG** 

	void Timer5Reset(void);

	//## Timer9Reset **Prescaler: 64; CAM_delay** 

	void Timer9Reset(void);

#endif
/*****************************************************************************/
/*****************************************************************************/
