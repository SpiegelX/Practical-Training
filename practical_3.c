#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f4xx_hal.h"

// Khởi tạo mutex
SemaphoreHandle_t xSemaphore = NULL;
UART_HandleTypeDef huart2;

// Task điều khiển LED1 ??????
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
    // Thay đổi chu kỳ của timer1 thành 2 giây
    xTimerChangePeriod(xTimer, pdMS_TO_TICKS(2000), 0);
    // Ngừng task trong 2 giây
    vTaskDelay(pdMS_TO_TICKS(2000));
    // Dừng timer1
    xTimerStop(xTimer, 0);
}

// Task điều khiển LED2
void LED2_Task(void *pvParameters) {
    const TickType_t xDelay = pdMS_TO_TICKS(1000); // Chu kỳ nhấp nháy của LED2
    while(1) {
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
        vTaskDelay(xDelay); // Dừng task trong một khoảng thời gian
    }
}

int main(void) {
    HAL_Init(); // Khởi tạo HAL
    SystemClock_Config(); // Cấu hình System Clock
    MX_GPIO_Init(); // Khởi tạo GPIO
    MX_USART2_UART_Init(); // Khởi tạo UART

    xSemaphore = xSemaphoreCreateMutex(); // Tạo mutex

    xTimer1 = xTimerCreate()

    // Tạo các task
    xTaskCreate(LED1_Task, "LED1 Task", 128, NULL, 1, NULL);
    xTaskCreate(LED2_Task, "LED2 Task", 128, NULL, 1, NULL);

    vTaskStartScheduler(); // Bắt đầu lập lịch các task

    while(1) {
    }
}


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
void LED1_Task(void * pvParameter) {
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
void LED2_Task(void * pvParameter) {
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
    xTimer1 = xTimerCreate("LED1 Timer", pdMS_TO_TICKS(2000), pdTRUE, (void *)0, LED1_Task);
    xTimer2 = xTimerCreate("LED2 Timer", pdMS_TO_TICKS(3000), pdTRUE, (void *)0, LED2_Task);
/*
TimerHandle_t xTimerCreate
                 ( const char * const pcTimerName,
                   const TickType_t xTimerPeriod,
                   const UBaseType_t uxAutoReload,
                   void * const pvTimerID,
                   TimerCallbackFunction_t pxCallbackFunction );
*/
    // for create task one time vTimerSetReloadMode(xTimer1|xTimer2, pdFAIL);
    // Khởi động timer
    xTimerStart(xTimer1, 0);
    xTimerStart(xTimer2, 0);
/*
BaseType_t xTimerStart( TimerHandle_t xTimer, TickType_t xBlockTime);
*/
    vTaskStartScheduler(); // Bắt đầu lập lịch các task
    while(1) {
    }
}
