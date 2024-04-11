#include "headfile.h"

uint8_t rec_data;

void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART1) {
		HAL_UART_Transmit(huart, &rec_data, 1, 50);
		HAL_UART_Receive_IT(huart, &rec_data, 1);
	}
}
