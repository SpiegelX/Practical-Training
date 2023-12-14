#include "main.h"
#include "cmsis_os.h"
#include "stdio.h"

// Define LED and BUTTON GPIO pins
#define LED1_PIN GPIO_PIN_0
#define LED1_PORT GPIOA
#define LED2_PIN GPIO_PIN_1
#define LED2_PORT GPIOA
#define LED3_PIN GPIO_PIN_2
#define LED3_PORT GPIOA
#define BUTTON_PIN GPIO_PIN_3
#define BUTTON_PORT GPIOA

// Semaphore and mutex handles
osSemaphoreId LED1SemaphoreHandle;
osSemaphoreId LED2SemaphoreHandle;
osMutexId UARTMutexHandle;

// Task handles
osThreadId LED1TaskHandle;
osThreadId LED2TaskHandle;
osThreadId LED3TaskHandle;
osThreadId BUTTONTaskHandle;

// UART handle (assuming USART2 for example)
extern UART_HandleTypeDef huart2;

void LED1_Task(void const* argument) {
    for (;;) {
        osSemaphoreWait(LED1SemaphoreHandle, osWaitForever);
        HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
        if (HAL_GPIO_ReadPin(LED1_PORT, LED1_PIN) == GPIO_PIN_SET) {
            osMutexWait(UARTMutexHandle, osWaitForever);
            HAL_UART_Transmit(&huart2, (uint8_t*)"LED1 ON\r\n", 9, 100);
            osMutexRelease(UARTMutexHandle);
        }
        else {
            osMutexWait(UARTMutexHandle, osWaitForever);
            HAL_UART_Transmit(&huart2, (uint8_t*)"LED1 OFF\r\n", 10, 100);
            osMutexRelease(UARTMutexHandle);
        }
    }
}

// LED2_Task and UART_Send for LED2 omitted for brevity (similar to LED1_Task)

void LED3_Task(void const* argument) {
    for (;;) {
        uint32_t ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (ulNotificationValue == 3) {
            HAL_GPIO_TogglePin(LED3_PORT, LED3_PIN);
            if (HAL_GPIO_ReadPin(LED3_PORT, LED3_PIN) == GPIO_PIN_SET) {
                osMutexWait(UARTMutexHandle, osWaitForever);
                HAL_UART_Transmit(&huart2, (uint8_t*)"LED3 ON\r\n", 9, 100);
                osMutexRelease(UARTMutexHandle);
            }
            else {
                osMutexWait(UARTMutexHandle, osWaitForever);
                HAL_UART_Transmit(&huart2, (uint8_t*)"LED3 OFF\r\n", 10, 100);
                osMutexRelease(UARTMutexHandle);
            }
        }
    }
}

void BUTTON_Task(void const* argument) {
    for (;;) {
        if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_SET) {
            osThreadNotify(LED3TaskHandle, 3, osThreadWaitForever);
        }
        osDelay(100); // Adjust this delay based on the application's requirements
    }
}

void StartDefaultTask(void const* argument) {
    LED1SemaphoreHandle = osSemaphoreCreate(osSemaphore(LED1Semaphore), 1);
    LED2SemaphoreHandle = osSemaphoreCreate(osSemaphore(LED2Semaphore), 1);
    UARTMutexHandle = osMutexCreate(osMutex(UARTMutex));

    osThreadDef(LED1_Task, LED1_Task, osPriorityNormal, 0, 128);
    LED1TaskHandle = osThreadCreate(osThread(LED1_Task), NULL);

    // LED2_Task creation and other tasks omitted for brevity

    osThreadDef(BUTTON_Task, BUTTON_Task, osPriorityNormal, 0, 128);
    BUTTONTaskHandle = osThreadCreate(osThread(BUTTON_Task), NULL);

    for (;;) {
        osDelay(osWaitForever);
    }
}

int main(void) {
    // HAL_Init and system initialization code

    // Initialize the HAL UART handle (huart2 in this example)
    // Initialize GPIO pins for LEDs and BUTTON

    osThreadDef(DefaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
    osThreadId DefaultTaskHandle = osThreadCreate(osThread(DefaultTask), NULL);

    osKernelStart();

    // We should not reach here
    for (;;);
}


// Include necessary libraries and define constants

// Define LED pin numbers
#define LED1_PIN 1
#define LED2_PIN 2
#define LED3_PIN 3

// Define semaphore and mutex handles
SemaphoreHandle_t LED1Semaphore, LED2Semaphore;
SemaphoreHandle_t UARTMutex;

// Define tasks
void LED1_Task(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xLED1Period = pdMS_TO_TICKS(2000);

    while (1) {
        vTaskDelayUntil(&xLastWakeTime, xLED1Period);
        xSemaphoreGive(LED1Semaphore);
    }
}

void LED2_Task(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xLED2Period = pdMS_TO_TICKS(3000);

    while (1) {
        vTaskDelayUntil(&xLastWakeTime, xLED2Period);
        xSemaphoreGive(LED2Semaphore);
    }
}

void UART_Send(const char *data) {
    // Acquire UART mutex
        if (xSemaphoreTake(UARTMutex, portMAX_DELAY) == pdTRUE) {
        // Send data via UART
        // Release UART mutex
        xSemaphoreGive(UARTMutex);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART3)
    {
        HAL_UART_Transmit(&huart1, &rx_data, sizeof(rx_data), 100);
        Blink_LED(GPIOC, GPIO_PIN_13); // Nháy LED khi truyền UART
    }
}

void UART_TRANS_ESP(char *TRANS_DATA)
{
    if (xSemaphoreTake(UARTMutex, portMAX_DELAY) == pdTRUE) {
        HAL_UART_Transmist(&huart, (uint8_t*)TRANS_DATA,strlen(TRANS_DATA), HAL_MAX_DELAY)
        BLINK_LED();
        xSemaphoreGive(UARTMutex);
    }
}


void RS485_TRANS(uint16_t ADDRESS, char *TRANS_DATA)
{
    HAL_UART_Transmist(&huart, (uint8_t*)TRANS_DATA,strlen(TRANS_DATA), HAL_MAX_DELAY)


}

char RS485_READ(uint16_t ADDRESS, char *COMMAND)
{
    char DATA;
    RS485_TRANS(ADDRESS, COMMAND);
    HAL_UART_Receive_IT(&huart3, &DATA, 1);
    return DATA;
}

void BLINK_LED(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    for(int i=0;i<10;i++){
    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
    HAL_Delay(100);}
}

/*-------------------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"

// LED pin definition
#define LED_PIN GPIO_PIN_13
#define LED_PORT GPIOC

// UART handle (assuming USART2 for example)
extern UART_HandleTypeDef huart2;

void LED_Blink_Task(void const * argument) {
  for (;;) {
    // Blink LED
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
    osDelay(500); // Blink interval 500ms
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART2) {
    // UART Receive callback
    // Activate LED blinking task upon receiving data
    osThreadDef(LED_Blink_Task, LED_Blink_Task, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(LED_Blink_Task), NULL);
  }
}

int main(void) {
  // Initialize HAL, System Clock, UART, GPIO

  // Start UART reception
  HAL_UART_Receive_IT(&huart2, (uint8_t *)RxDataBuffer, 1);

  // Start RTOS kernel
  osKernelStart();

  // We should not reach here
  for (;;);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  // UART error handling if needed
}
/*-------------------------------------------------------------------------------*/
void LED3_Task(void *pvParameters) {
    while (1) {
        // Wait for control value from BUTTON task
        uint32_t controlValue;
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == pdTRUE) {
            // Toggle LED3
            // Send status via UART
            UART_Send("LED3 TOGGLED");
        }
    }
}

void BUTTON_Task(void *pvParameters) {
    while (1) {
        // Simulate button press or read actual button state
        // If button value is 3, notify LED3_Task
        uint32_t buttonValue = 3; // Replace this with actual button read logic
        xTaskNotifyGive(LED3_Task_Handle);
    }
}

// Main function
int main() {
    // Create semaphores
    LED1Semaphore = xSemaphoreCreateBinary();
    LED2Semaphore = xSemaphoreCreateBinary();
    // Create mutex
    UARTMutex = xSemaphoreCreateMutex();

    // Create tasks
    xTaskCreate(LED1_Task, "LED1_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(LED2_Task, "LED2_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(LED3_Task, "LED3_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(BUTTON_Task, "BUTTON_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Start scheduler
    vTaskStartScheduler();

    // Should not reach here
    for (;;);
    return 0;
}


#include "stm32f1xx_hal.h"

// Khai báo biến
uint8_t rx_data;
uint8_t tx_data[20] = "STM32 Hello Man!!\r\n";

// Hàm nháy LED
void Blink_LED(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
    HAL_Delay(1000);
}

// Hàm ngắt UART
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        HAL_UART_Transmit(&huart1, &rx_data, sizeof(rx_data), 100);
        Blink_LED(GPIOC, GPIO_PIN_13); // Nháy LED khi truyền UART
    }
}

int main(void)
{
    // Khởi tạo hệ thống
    HAL_Init();

    // Cấu hình và khởi tạo UART
    // ...

    // Truyền dữ liệu và cho phép ngắt ở lần đầu tiên khởi động
    HAL_UART_Transmit(&huart1, tx_data, sizeof(tx_data), 100);
    HAL_UART_Receive_IT(&huart1, &rx_data, 1);

    while (1)
    {
        // Vòng lặp chính của chương trình
    }
}
