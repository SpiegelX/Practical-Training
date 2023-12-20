#ifndef ADS1115_H_
#define ADS1115_H_

#include "stm32h7xx_hal.h"

// Định nghĩa các địa chỉ của IC ADS1115
#define ADS1115_ADDRESS_1 0x48
#define ADS1115_ADDRESS_2 0x49

// Định nghĩa thanh ghi cấu hình
#define ADS1115_REG_CONFIG 0x01

// Định nghĩa chế độ chuyển đổi ADC
typedef enum {
    ADS1115_MODE_CONTINUOUS = 0b00000000, // Chế độ chuyển đổi liên tục
    ADS1115_MODE_SINGLE_SHOT = 0b01000000 // Chế độ chuyển đổi single-shot
} ADS1115_Mode;

// Định nghĩa các kênh đọc ADC
typedef enum {
    ADS1115_CHANNEL_0 = 0b000, // Kênh 0
    ADS1115_CHANNEL_1 = 0b001, // Kênh 1
    ADS1115_CHANNEL_2 = 0b010, // Kênh 2
    ADS1115_CHANNEL_3 = 0b011  // Kênh 3
} ADS1115_Channel;

// Prototype các hàm để sử dụng trong ADS1115.c
void ADS1115_Init(I2C_HandleTypeDef *hi2c, uint8_t address, ADS1115_Mode mode);
int16_t ADS1115_ReadChannel(I2C_HandleTypeDef *hi2c, uint8_t address, ADS1115_Channel channel);

#endif /* ADS1115_H_ */
