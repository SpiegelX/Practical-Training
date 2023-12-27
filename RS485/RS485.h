#ifndef __RS485_H
#define __RS485_H

#include "stm32h7xx.h"

extern UART_HandleTypeDef huart1
struct RS485
{
uint8_t RxData[32];
uint8_t TxData[8];
uint16_t Data[10];
};RS485_DATA

void sendData(uint8_t *data);


#endif