#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "stm32f4xx_hal.h"

// Khởi tạo mutex

SemaphoreHandle_t xSemaphore = NULL;
UART_HandleTypeDef huart2;
TimerHandle_t xTimer1, xTimer2;

// Task điều khiển LED1
void LED1_Task(TimerHandle_t xTimer) {
    if(xSemaphore != NULL) {
        // Lấy mutex, chờ tối đa 10 tick nếu mutex không sẵn sàng
        if(xSemaphoreTake(xSemaphore, (TickType_t)10) == pdTRUE) {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Đảo trạng thái LED1
            if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET) {
                char *msg = "LED 1 ON\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY); // Gửi thông báo qua UART
            } else {
                char *msg = "LED 1 OFF\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY); // Gửi thông báo qua UART
            }
            xSemaphoreGive(xSemaphore); // Trả lại mutex
        }
    }
}

// Task điều khiển LED2
void LED2_Task(TimerHandle_t xTimer) {
    if(xSemaphore != NULL) {
        // Lấy mutex, chờ tối đa 10 tick nếu mutex không sẵn sàng
        if(xSemaphoreTake(xSemaphore, (TickType_t)10) == pdTRUE) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5); // Đảo trạng thái LED2
            if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_SET) {
                char *msg = "LED 2 ON\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY); // Gửi thông báo qua UART
            } else {
                char *msg = "LED 2 OFF\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY); // Gửi thông báo qua UART
            }
            xSemaphoreGive(xSemaphore); // Trả lại mutex
        }
    }
}

int main(void) {
    HAL_Init(); // Khởi tạo HAL
    SystemClock_Config(); // Cấu hình System Clock
    MX_GPIO_Init(); // Khởi tạo GPIO
    MX_USART2_UART_Init(); // Khởi tạo UART

    xSemaphore = xSemaphoreCreateMutex(); // Tạo mutex

    // Tạo timer
    xTimer1 = xTimerCreate("LED1 Timer", pdMS_TO_TICKS(500), pdTRUE, (void *)0, LED1_Task);
    xTimer2 = xTimerCreate("LED2 Timer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, LED2_Task);

    // Khởi động timer
    xTimerStart(xTimer1, 0);
    xTimerStart(xTimer2, 0);

    vTaskStartScheduler(); // Bắt đầu lập lịch các task

    while(1) {
    }
}
