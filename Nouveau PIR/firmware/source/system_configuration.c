/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  System configuration                                   */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  18.09.2012                                             */
/* Author          :  Christian Ringlstetter/Thomas Pichler                  */
/*****************************************************************************/

// ### Basic includes ###
	#include "stdbool.h"
	#include "system_configuration.h"
	#include "stm32f10x.h"
  #include "stm32f10x_gpio.h"
// ### Programm includes ###
	#include "synchronization.h"
	#include "uart.h"
			

// ### Variables ###

	// CRK-configuration
	extern unsigned int number_teeth_between_gaps;
	extern unsigned int number_teeth_CRK;
	extern unsigned int number_gap;
	extern unsigned int number_miss_teeth;
    extern unsigned int number_real_teeth;
    extern unsigned int number_segments_CRK;
    extern unsigned int first_seg_start_tooth;  
    extern unsigned int number_cylinder;
	extern double revolution_CRK;
	extern double tdc_to_gap;
    extern double first_seg_angle;
	extern bool CRK_config;

	
	//CAM_CRK-configuration
 	extern double first_edge_to_tdc0[2];
	extern double CAM_edges[2][24];
	extern double gap_to_first_edge[2];
	extern bool TDC_on_edge[2];
	extern bool configuration_complete; 
	extern bool output_level_setting;

	//CAM-configuration
	extern unsigned int number_teeth_CAM[2];
	extern unsigned int number_active_edges_CAM[2];
	extern double distance_gap_to_CAM_edge[2][24];
	extern double filter_time_CAM[2];
	extern double tolerance_window_CAM[2];
	extern bool CAM_config;
	extern char active_CAM_edges[2];
    extern int number_of_CAM;

	//UART-Send 
	extern char message[];

//### Functions ###

	// ## CRK Configuration
	void CRK_configuration(void) 
	{
		// Number of teeth between two gaps 
		number_teeth_between_gaps = (number_teeth_CRK/number_gap) - number_miss_teeth;
		
		// Number of remaining teeth
		number_real_teeth = number_teeth_CRK - number_miss_teeth;
		
		// Revolution of one tooth time
		revolution_CRK = (double)(360.0/number_teeth_CRK);
	
		// Set number of segments
		number_segments_CRK = number_cylinder;
        
        int first_tooth_angle = 720 - tdc_to_gap;
        
        if (first_seg_angle >= first_tooth_angle){
            first_seg_start_tooth = (first_seg_angle - first_tooth_angle) / revolution_CRK;
            
        }else{
            first_seg_start_tooth = number_teeth_CRK - (( first_tooth_angle - first_seg_angle) / revolution_CRK);
        }

		// Set configuration status
		CRK_config = true;

		// Complete configuration
		if((CRK_config == true) && (CAM_config == true))
		{
            CAM_CRK_configuration(); 
		}

		// Send configuration status
		USART_send(message[1]);
	}


	// ## CAM Configuration
	void CAM_configuration(void)
	{	
        int camId = 0;
        
        for(camId = 0; camId < number_of_CAM; camId++)
        {
            // Set counter to calculate the distances of the CAM edges to the gap in the for-loop
          int i;

          // Set number of CAM edges
          if(active_CAM_edges[camId] == 'b')
          {
              number_teeth_CAM[camId] = number_active_edges_CAM[camId] / 2;
          }
          else
          {
              number_teeth_CAM[camId] = number_active_edges_CAM[camId];
          }

          // Calculate distance from gap to CAM edges
          for(i = 0; i < number_active_edges_CAM[camId]; i++)
          {
              distance_gap_to_CAM_edge[camId][i] = CAM_edges[camId][i] + tdc_to_gap;

              if(distance_gap_to_CAM_edge[camId][i] >= 720.0)
              {
                  distance_gap_to_CAM_edge[camId][i] = distance_gap_to_CAM_edge[camId][i] - 720.0;
              }			
          }  
        }
		

		// Set configuration status
		CAM_config = true;

		// Complete configuration
		if(CRK_config == true && CAM_config == true)
		{
			CAM_CRK_configuration();
		}

		// Send configuration status
		USART_send(message[2]);

	}


	// ## CAM_CRK Configuration
	void CAM_CRK_configuration(void)
	{
        int camId = 0;
        
        for(camId = 0; camId < number_of_CAM; camId++)
        {
            // Set first falling(rising, when active_edges = 'r') CAM edge after TDC0
            first_edge_to_tdc0[camId] = CAM_edges[camId][0];

            // Distance from gap to first falling CAM-edge
            gap_to_first_edge[camId] = first_edge_to_tdc0[camId] + tdc_to_gap;

            if((long)tdc_to_gap%(long)revolution_CRK == 0)
            {
                TDC_on_edge[camId] = true;
            }
            else
            {
                TDC_on_edge[camId] = false;
            }

            // Set tolerance window for CAM_CRK synchronization in case of start
            tolerance_window_CAM[camId] = 2.0 * revolution_CRK;
        }
		Stalling_detection();

		configuration_complete = true;					
	}


	//### Input Signal Observation ###
	void Input_signal_observe(bool output_set)
	{
		if(!output_set)
		{
			// Check CRK input signal level
			if(GPIO_ReadInputDataBit(GPIOB,8) != GPIO_ReadInputDataBit(GPIOA,4))
			{
				if (GPIO_ReadInputDataBit(GPIOA, 4) == 1)
                        {
                        GPIO_ResetBits(GPIOA, 4);
                        }
                    else
                        {
                         GPIO_SetBits(GPIOA, 4);
                        };
			}
	
			// Check CAM input signal level
			if(GPIO_ReadInputDataBit(GPIOB,10) != GPIO_ReadInputDataBit(GPIOA,5))
			{
				if (GPIO_ReadInputDataBit(GPIOA, 5) == 1)
                        {
                        GPIO_ResetBits(GPIOA, 5);
                        }
                    else
                        {
                         GPIO_SetBits(GPIOA, 5);
                        };
			}
            
            if(GPIO_ReadInputDataBit(GPIOB,12) != GPIO_ReadInputDataBit(GPIOA,6))
			{
				if (GPIO_ReadInputDataBit(GPIOA, 6) == 1)
                        {
                        GPIO_ResetBits(GPIOA, 6);
                        }
                    else
                        {
                         GPIO_SetBits(GPIOA, 6);
                        };	
			}

			output_level_setting = true;
		}		
	}	
/************************************************************************/
/************************************************************************/
//Activation of all clock trees for all used peripherals
void Config_clock_tree(void)
{
	//USART1 GPIO A9 et A10 si on utilise les gpios
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;															
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}

