#include "RS485.h"

#define DV1_SL_ADDRESS 0x01

RS485_DATA.Txdata[0] = DV1_SL_ADDRESS;
RS485_DATA.TxData[1] = 0x03;  // Function code for Read Holding Registers

RS485_DATA.TxData[2] = 0;
RS485_DATA.TxData[3] = 0x04;

//The Register address will be 00000000 00000100 = 4 + 40001 = 40005
RS485_DATA.TxData[4] = 0;
RS485_DATA.TxData[5] = 0x05;

// no of registers to read will be 00000000 00000101 = 5 Registers = 10 Bytes
RS485_DATA.uint16_t crc = crc16(TxData, 6);
RS485_DATA.TxData[6] = crc&0xFF;   // CRC LOW
RS485_DATA.TxData[7] = (crc>>8)&0xFF;  // CRC HIGH

sendData(RS485_DATA.TxData);
HAL_UARTEx_ReceiveToIdle_IT(&huart1, RxData, 32);

RS485_DATA.TxData[0] = 0x05;  // slave address
RS485_DATA.TxData[1] = 0x04;  // Function code for Read Input Registers

RS485_DATA.TxData[2] = 0;
RS485_DATA.TxData[3] = 0x01;
//The Register address will be 00000000 00000001 = 1 +30001 = 30002

RS485_DATA.TxData[4] = 0;
RS485_DATA.TxData[5] = 0x05;
// no of registers to read will be 00000000 00000101 = 5 Registers = 10 Bytes

uint16_t crc = crc16(RS485_DATA.TxData, 6);
RS485_DATA.TxData[6] = crc&0xFF;   // CRC LOW
RS485_DATA.TxData[7] = (crc>>8)&0xFF;  // CRC HIGH

sendData(RS485_DATA.TxData);

// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
// {
// 	Data[0] = RxData[3]<<8 | RxData[4];
// 	Data[1] = RxData[5]<<8 | RxData[6];
// 	Data[2] = RxData[7]<<8 | RxData[8];
// 	Data[3] = RxData[9]<<8 | RxData[10];
// 	Data[4] = RxData[11]<<8 | RxData[12];
// }
