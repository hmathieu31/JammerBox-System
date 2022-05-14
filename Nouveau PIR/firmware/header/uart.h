/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  UART		                                             */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

#ifndef _UART_H_
#define _UART_H_

// ### Functions ###

	// ## Uart2 Init ##

	void Uart2Init(void);

	//### UART Receive Function ###

	void USART_receive(void);

	//### UART Send Function ###
	
	void USART_send(char);

	//### UART Send Configuration Status Function ###
	
	void UART_send_failure_configuration_status(char, bool, bool);

	//## UART Reset temporary char-arrays

	void Reset_temp_arrays(void);

	//## UART COM Error Function

	void UART_COM_error(void);
	
#endif
/*****************************************************************************/
/*****************************************************************************/
