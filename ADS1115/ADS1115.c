#include "ADS1115.h"

// Ghi cấu hình vào thanh ghi của ADS1115
void ADS1115_WriteConfig(I2C_HandleTypeDef *hi2c, uint8_t address, uint16_t config) {
    uint8_t data[3];
    data[0] = ADS1115_REG_CONFIG; // Địa chỉ thanh ghi cấu hình
    data[1] = config >> 8; // Ghi 8 bit cao vào byte thứ 2
    data[2] = config & 0xFF; // Ghi 8 bit thấp vào byte thứ 3

    HAL_I2C_Master_Transmit(hi2c, address, data, 3, HAL_MAX_DELAY);
}

// Khởi tạo ADS1115 với chế độ chuyển đổi và địa chỉ IC
void ADS1115_Init(I2C_HandleTypeDef *hi2c, uint8_t address, ADS1115_Mode mode) {
    uint16_t config = 0b1100001100000000 | mode;
    ADS1115_WriteConfig(hi2c, address, config);
}

// Đọc giá trị từ kênh được chỉ định của IC với địa chỉ xác định
int16_t ADS1115_ReadChannel(I2C_HandleTypeDef *hi2c, uint8_t address, ADS1115_Channel channel) {
    uint16_t config = 0b1100001100000000 | (channel << 12);
    ADS1115_WriteConfig(hi2c, address, config);

    HAL_Delay(100); // Thời gian chuyển đổi (có thể điều chỉnh tùy thuộc vào ứng dụng của bạn)

    uint8_t data[2];
    HAL_I2C_Master_Transmit(hi2c, address, &ADS1115_REG_CONFIG, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(hi2c, address, data, 2, HAL_MAX_DELAY);

    int16_t adc_value = (int16_t)((data[0] << 8) | data[1]);
    return adc_value;
}
