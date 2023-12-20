#include "ADS1115.h"

// Địa chỉ của các IC ADS1115
#define IC1_ADDRESS 0x48
#define IC2_ADDRESS 0x49
const float Vol_Cur = ((6.144/32768.0)/250)*1000;
const float Vol010  = (6.144/32768.0)*2;
const float Vol1010  = ((6.144/32768.0)*4)-10;
const float Vol = 6.144/32768.0;
// Số lượng IC ADS1115
#define NUM_DEVICES 2

int main() {
    I2C_HandleTypeDef hi2c; // Khởi tạo cấu trúc I2C của STM32

    // Khởi tạo các giá trị kênh của từng IC
    ADS1115_Init(&hi2c2, IC1_ADDRESS, ADS1115_MODE_SINGLE_SHOT);
    ADS1115_Init(&hi2c2, IC2_ADDRESS, ADS1115_MODE_SINGLE_SHOT);

    // Khởi tạo mảng kết quả
   
    // Đọc giá trị từ các kênh của từng IC

        uint16_t current_1_result;
        uint16_t current_2_result;
        uint16_t Vol010_result;
        uint16_t Vol010_result;

        uint16_t Ain_0;
        uint16_t Ain_1;
        uint16_t Ain_2;
        uint16_t Ain_3; 

        current_1_result = ADS1115_ReadChannel(&hi2c2, IC1_ADDRESS, ADS1115_CHANNEL_0)*Vol_Cur;
        current_2_result = ADS1115_ReadChannel(&hi2c2, IC1_ADDRESS, ADS1115_CHANNEL_1)*Vol_Cur;
        Vol010_result   =  ADS1115_ReadChannel(&hi2c2, IC1_ADDRESS, ADS1115_CHANNEL_2)*Vol010;
        Vol010_result   =  ADS1115_ReadChannel(&hi2c2, IC1_ADDRESS, ADS1115_CHANNEL_3)*Vol1010;

        Ain_0   = ADS1115_ReadChannel(&hi2c2, IC2_ADDRESS, ADS1115_CHANNEL_0)*Vol;                
        Ain_1   = ADS1115_ReadChannel(&hi2c2, IC2_ADDRESS, ADS1115_CHANNEL_1)*Vol;
        Ain_2   = ADS1115_ReadChannel(&hi2c2, IC2_ADDRESS, ADS1115_CHANNEL_2)*Vol;
        Ain_3   = ADS1115_ReadChannel(&hi2c2, IC2_ADDRESS, ADS1115_CHANNEL_3)*Vol;
    
    // In ra giá trị đọc được từ từng kênh của từng IC
    // Thực hiện xử lý dữ liệu hoặc các thao tác khác ở đây

    // Kết thúc chương trình
    return 0;
}
