#include "exemple.h"
#include "usart.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#define BUFFER_SIZE 4

int main(void){
    
    MX_USART1_Init(void);
    HAL_USART_IRQHandler(&husart1);

    while(1){
        uint8_t bufferReceive[BUFFER_SIZE];
        uint8_t bufferTransmit[BUFFER_SIZE];
        switch(HAL_USART_TransmitReceive_IT(husart1,&bufferTransmit,&bufferReceive,BUFFER_SIZE,1000)){
            case HAL_OK:
                break;
            case HAL_ERROR:
                break;
            case HAL_BUSY:
                break;
            case HAL_TIMEOUT:
                break;
        }
    }

    return 0;
}