/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Timer                                                  */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Gr�goire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

// ### Basic includes ###
	#include "stm32f10x.h"
	#include "stm32f10x_tim.h"
	#include "timer.h"


// ### Variables ###

	extern unsigned long timer_overflow_CRK;
	extern unsigned long timer_overflow_CAM;
	extern unsigned long timer_overflow_CRK_failure;
	extern unsigned long timer_overflow_CAM_failure;
	extern unsigned long timer_overflow_CAM_REF_CRK;

// ### Functions ###

// ## Timer1 Init **Communication validation** 
	void Timer1Init(void){
		
		// Aim: high timer duration
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 64 = 575,78 kHz = 1,737 µs

		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Enable APB clock for the Timer1
		TIM_Cmd(TIM1, DISABLE); // Disable Timer1
		//No idle mode handling necessary on STM32
		TIM_ITConfig(TIM1, TIM_IT_Trigger, DISABLE); // Disable Trigger Interrupt (called Gated Timer mode on Microchip)
		TIM_InternalClockConfig(TIM1); // Tell the STM32 to use the internal clock (ticking at 72MHz)
		TIM_SetCounter(TIM1, 0); // Clear Timer1 counter
		//TIM_period = (1/72MHz) * (PSC+1) *(ARR+1)
		// (1/72MHz) * (499+1) * (64799+1) = 450ms
		TIM_PrescalerConfig(TIM1, 499,TIM_PSCReloadMode_Immediate);
		TIM_SetAutoreload(TIM1, 64799);

		NIVC_SetPriority(TIM1_UP_IRQn, 2); // Set Timer1 TIM1_UP_IRQn Interrupt Priority Level
		TIM_ClearFlag(TIM1, TIM_FLAG_Update); // Clear Timer1 Interrupt Flag
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); // Enable Timer1 interrupt
	}

	// ## Timer2 Init **Prescaler: 64; CRK Synchronization; tooth time** 
	void Timer2Init(void){

		// Aim: resolution of < 2 �s;
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 64 = 575,78 kHz = 1,7367744624683038660599534544444�s

		RCC->APB2ENR |= RCC_APB1ENR_TIM2EN; // Enable APB clock for the Timer2
		TIM_Cmd(TIM2, DISABLE); // Disable Timer2
		//No idle mode handling necessary on STM32
		TIM_ITConfig(TIM2, TIM_IT_Trigger, DISABLE); // Disable Trigger Interrupt (called Gated Timer mode on Microchip)
		TIM_InternalClockConfig(TIM2); // Tell the STM32 to use the internal clock (ticking at 72MHz)
		TIM_SetCounter(TIM2, 0); // Clear Timer2 counter
		// TIM_period = (1/72MHz) * (PSC+1) *(ARR+1)
		// (1/72MHz) * (119+1) * (62999+1) = 105ms
		TIM_PrescalerConfig(TIM2, 499,TIM_PSCReloadMode_Immediate);
		TIM_SetAutoreload(TIM2, 64799);

		NIVC_SetPriority(TIM2_IRQn, 2); // Set Timer2 TIM2_IRQn Interrupt Priority Level
		TIM_ClearFlag(TIM2, TIM_FLAG_Update); // Clear Timer2 Interrupt Flag
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // Enable Timer2 interrupt
		TIM_Cmd(TIM2, ENABLE); // Start Timer
	}


	// ## Timer3 Init **Prescaler: 256; CAM Synchronization; segment time** 
	void Timer3Init(void){
		
		// Aim: high timer duration
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 256 = 143,95 kHz = 6.946 �s

		RCC->APB2ENR |= RCC_APB1ENR_TIM3EN; // Enable APB clock for the Timer3
		TIM_Cmd(TIM3, DISABLE); // Disable Timer3
		//No idle mode handling necessary on STM32
		TIM_ITConfig(TIM3, TIM_IT_Trigger, DISABLE); // Disable Trigger Interrupt (called Gated Timer mode on Microchip)
		TIM_InternalClockConfig(TIM3); // Tell the STM32 to use the internal clock (ticking at 72MHz)
		TIM_SetCounter(TIM3, 0); // Clear Timer3 counter
		// TIM_period = (1/72MHz) * (PSC+1) *(ARR+1)
		// (1/72MHz) * (479+1) * (62999+1) = 420ms
		TIM_PrescalerConfig(TIM3, 479,TIM_PSCReloadMode_Immediate);
		TIM_SetAutoreload(TIM3, 62999);

		NIVC_SetPriority(TIM3_IRQn, 2); // Set Timer3 TIM3_IRQn Interrupt Priority Level
		TIM_ClearFlag(TIM3, TIM_FLAG_Update); // Clear Timer3 Interrupt Flag
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // Enable Timer3 interrupt
		TIM_Cmd(TIM3, ENABLE); // Start Timer
	}

	// ## Timer4 Init **Prescaler: 64; CRK_NO_SIG/CAM_delay**  
	void Timer4Init(void)
	{
		// Aim: resolution of < 2 �s;
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 64 = 575,78 kHz = 1,737 �s

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
		// 36,85 Mhz/ 256 = 143,95 kHz = 6.946 �s

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
		// Aim: Timer ticks < 1 �s
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 8 = 4606 kHz = 0.217 �s

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
		// Aim: Timer ticks < 1 �s
		// FCPU with PLL = 73,7 MHz
		// Fcy: 36,85 MHz
		// 36,85 Mhz/ 8 = 4606 kHz = 0.217 �s

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
		// 36,85 Mhz/ 64 = 575,78 kHz = 1.73 �s
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
		// 36,85 Mhz/ 64 = 575,78 kHz = 1.73 �s

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
