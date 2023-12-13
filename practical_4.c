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
