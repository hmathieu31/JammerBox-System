#include "usart.h"

USART_HandleTypeDef husart1;

void HAL_USART_MspInit(USART_HandleTypeDef* usartHandle);
void HAL_USART_MspDeInit(USART_HandleTypeDef* usartHandle);

void MX_USART1_Init(void);