#include "exemple.h"
#include "usart.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"

int main(void){
    
    MX_USART1_Init(void);

    while(1){
        uint8_t buffer[4];
        switch(HAL_USART_Receive(husart1,&buffer,4,1000)){
            case HAL_OK:
                HAL_USART_Transmit(husart1,&buffer,4,1000);
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