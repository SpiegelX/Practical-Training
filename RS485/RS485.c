#include "RS485.h"

void sendData (uint8_t *data)
{
	HAL_UART_Transmit(&huart1, data, 8, 1000);
}


