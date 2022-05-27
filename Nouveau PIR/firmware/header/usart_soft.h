/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  USART		                                             */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

#ifndef _USART_H_
#define _USART_H_

// ### Functions ###

	// ## Usart1 Init ##

	void Usart1Init(void);

	//### USART Receive Function ###

	void USART_receive(void);

	//### USART Send Configuration Status Function ###
	
	void USART_send_failure_configuration_status(char, bool, bool);

	//## USART Reset temporary char-arrays

	void Reset_temp_arrays(void);

	//## USART COM Error Function

	void USART_COM_error(void);
	
#endif
/*****************************************************************************/
/*****************************************************************************/
