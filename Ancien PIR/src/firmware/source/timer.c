/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Timer                                                  */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Grégoire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

// ### Basic includes ###

	#include "p33FJ256GP710A.h"
	#include "timer.h"


// ### Variables ###

	extern unsigned long timer_overflow_CRK;
	extern unsigned long timer_overflow_CAM;
	extern unsigned long timer_overflow_CRK_failure;
	extern unsigned long timer_overflow_CAM_failure;
	extern unsigned long timer_overflow_CAM_REF_CRK;

// ### Functions ###

// ## Timer1 Init **Prescaler: 256; Communication validation** 
	void Timer1Init(void){
		
		// Aim: high timer duration
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 64 = 575,78 kHz = 1,737 µs

		T1CONbits.TON = 0; 			// Disable Timer
		T1CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T1CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T1CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T1CONbits.TCKPS = 0b11; 	// Select 1:256 Prescaler
		TMR1 = 0x00; 				// Clear timer register
		PR1 = 0xFD07;				// Load the period value(timer period: 450ms)
		
		IPC0bits.T1IP = 0x02; 		// Set Timer1 Interrupt Priority Level
		IFS0bits.T1IF = 0; 			// Clear Timer1 Interrupt Flag
		IEC0bits.T1IE = 1; 			// Enable Timer1 interrupt
	}

	// ## Timer2 Init **Prescaler: 64; CRK Synchronization; tooth time** 
	void Timer2Init(void){

		// Aim: resolution of < 2 µs;
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 64 = 575,78 kHz = 1,7367744624683038660599534544444µs
		
		T2CONbits.TON = 0; 			// Disable Timer
		T2CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T2CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T2CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T2CONbits.TCKPS = 0b10; 	// Select 1:64 Prescaler
		T2CONbits.T32 = 0;			// Separate timers
		TMR2 = 0x00; 				// Clear timer register
		PR2 = 0xFFFF;				// Load the period value
		
		IPC1bits.T2IP = 0x02; 		// Set Timer2 Interrupt Priority Level
		IFS0bits.T2IF = 0; 			// Clear Timer2 Interrupt Flag
		IEC0bits.T2IE = 1; 			// Enable Timer2 interrupt
		T2CONbits.TON = 1; 			// Start Timer
		
	}


	// ## Timer3 Init **Prescaler: 256; CAM Synchronization; segment time** 
	void Timer3Init(void){
		
		// Aim: high timer duration
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 256 = 143,95 kHz = 6.946 µs

		T3CONbits.TON = 0; 			// Disable Timer
		T3CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T3CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T3CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T3CONbits.TCKPS = 0b11; 	// Select 1:256 Prescaler
		TMR3 = 0x00; 				// Clear timer register
		PR3 = 0xFFFF;				// Load the period value
		
		IPC2bits.T3IP = 0x02; 		// Set Timer3 Interrupt Priority Level
		IFS0bits.T3IF = 0; 			// Clear Timer3 Interrupt Flag
		IEC0bits.T3IE = 1; 			// Enable Timer3 interrupt
		T3CONbits.TON = 1; 			// Start Timer

	}

	// ## Timer4 Init **Prescaler: 64; CRK_NO_SIG/CAM_delay**  
	void Timer4Init(void)
	{
		// Aim: resolution of < 2 µs;
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 64 = 575,78 kHz = 1,737 µs

		T4CONbits.TON = 0; 			// Disable Timer
		T4CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T4CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T4CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T4CONbits.TCKPS = 0b10; 	// Select 1:64 Prescaler
		TMR4 = 0x00; 				// Clear timer register
		PR4 = 0xFFFF;				// Load the period value
		
		IPC6bits.T4IP = 0x02; 		// Set Timer4 Interrupt Priority Level
		IFS1bits.T4IF = 0; 			// Clear Timer4 Interrupt Flag
		IEC1bits.T4IE = 1; 			// Enable Timer4 interrupt
	}

	// ## Timer5 Init **CAM Prescaler: 256; CAM_NO_SIG**
	void Timer5Init(void)
	{
		// Aim: high timer duration
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 256 = 143,95 kHz = 6.946 µs

		T5CONbits.TON = 0; 			// Disable Timer
		T5CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T5CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T5CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T5CONbits.TCKPS = 0b11; 	// Select 1:256 Prescaler
		TMR5 = 0x00; 				// Clear timer register
		PR5 = 0xFFFF;				// Load the period value
		
		IPC7bits.T5IP = 0x02; 		// Set Timer5 Interrupt Priority Level
		IFS1bits.T5IF = 0; 			// Clear Timer5 Interrupt Flag
		IEC1bits.T5IE = 1; 			// Enable Timer5 interrupt
	}
	
	// ## Timer6 Init **Prescaler: 8; CAM_PER/CRK_TOOTH_PER(start-value)//CRK_SHO_LEVEL pulse duration**
	void Timer6Init(void)
	{
		// Aim: Timer ticks < 1 µs
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 8 = 4606 kHz = 0.217 µs

		T6CONbits.TON = 0; 			// Disable Timer
		T6CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T6CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T6CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T6CONbits.TCKPS = 0b01; 	// Select 1:8 Prescaler
		TMR6 = 0x00; 				// Clear timer register
		PR6 = 0xFFFF;				// Load the period value
		
		IPC11bits.T6IP = 0x04; 		// Set Timer6 Interrupt Priority Level
		IFS2bits.T6IF = 0; 			// Clear Timer6 Interrupt Flag
		IEC2bits.T6IE = 1; 			// Enable Timer6 interrupt
	}

	// ## Timer7 Init **Prescaler: 8; CAM_PER/CRK_TOOTH_PER(pulse duration)**
	void Timer7Init(void)
	{
		// Aim: Timer ticks < 1 µs
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 8 = 4606 kHz = 0.217 µs

		T7CONbits.TON = 0; 			// Disable Timer
		T7CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T7CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T7CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T7CONbits.TCKPS = 0b01; 	// Select 1:8 Prescaler
		TMR7 = 0x00; 				// Clear timer register
		PR7 = 0x002E;				// Load the period value //5us 0x0017 is too low for pulse recognition, double value
		
		IPC12bits.T7IP = 0x04; 		// Set Timer7 Interrupt Priority Level
		IFS3bits.T7IF = 0; 			// Clear Timer7 Interrupt Flag
		IEC3bits.T7IE = 1; 			// Enable Timer7 interrupt
	}

	// ## Timer8 Init **Prescaler: 64; CRK_RUN_OUT/CAM_delay**
	void Timer8Init(void)
	{
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 64 = 575,78 kHz = 1.73 µs
		T8CONbits.TON = 0; 			// Disable Timer
		T8CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T8CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T8CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T8CONbits.TCKPS = 0b10; 	// Select 1:64 Prescaler
		TMR8 = 0x00; 				// Clear timer register
		PR8 = 0xFFFF;				// Load the period value
		
		IPC12bits.T8IP = 0x02; 		// Set Timer8 Interrupt Priority Level
		IFS3bits.T8IF = 0; 			// Clear Timer8 Interrupt Flag
		IEC3bits.T8IE = 1; 			// Enable Timer8 interrupt
	}

	// ## Timer9 Init **Prescaler: 64; CAM_delay**
	void Timer9Init(void){
		
		// Aim: high timer duration
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 64 = 575,78 kHz = 1.73 µs

		T9CONbits.TON = 0; 			// Disable Timer
		T9CONbits.TSIDL = 0;		// Continue timer operation in idle mode
		T9CONbits.TGATE = 0; 		// Disable Gated Timer mode
		T9CONbits.TCS = 0; 			// Select internal instruction cycle clock
		T9CONbits.TCKPS = 0b10; 	// Select 1:64 Prescaler
		TMR9 = 0x00; 				// Clear timer register
		PR9 = 0xFFFF;				// Load the period value
		
		IPC13bits.T9IP = 0x02; 		// Set Timer9 Interrupt Priority Level
		IFS3bits.T9IF = 0; 			// Clear Timer9 Interrupt Flag
		IEC3bits.T9IE = 1; 			// Enable Timer9 interrupt
	}

	//## Timer2Reset **Prescaler: 64; CRK Synchronization; tooth time** 
	void Timer2Reset(void){
		TMR2 = 0x00;				// Reset TMR2
		timer_overflow_CRK = 0;
	}
	

	//## Timer3Reset **Prescaler: 256; CAM Synchronization; segment time** 
	void Timer3Reset(void){
		TMR3 = 0x00;				// Reset TMR3
		timer_overflow_CAM = 0;
	}

	//## Timer4Reset **Prescaler: 64; CRK_NO_SIG/CAM_delay** 
	void Timer4Reset(void){
		TMR4 = 0x00;				// Reset TMR4
		timer_overflow_CRK_failure = 0;
	}

	//## Timer5Reset **CAM Prescaler: 256; CAM_NO_SIG** 
	void Timer5Reset(void){
		TMR5 = 0x00;				// Reset TMR5
		timer_overflow_CAM_failure = 0;
	}

	//## Timer9Reset **Prescaler: 64; CAM_delay** 
	void Timer9Reset(void){
		TMR9 = 0x00;				// Reset TMR9
		timer_overflow_CAM_REF_CRK = 0;
	}


/*****************************************************************************/
/*****************************************************************************/
