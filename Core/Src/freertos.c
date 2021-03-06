/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wr_czas.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart1;

/* USER CODE END Variables */
osThreadId blink01Handle;
osThreadId blink02Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartBlink01(void const * argument);
void StartBlink02(void const * argument);

extern void MX_USB_HOST_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of blink01 */
  osThreadDef(blink01, StartBlink01, osPriorityNormal, 0, 128);
  blink01Handle = osThreadCreate(osThread(blink01), NULL);

  /* definition and creation of blink02 */
  osThreadDef(blink02, StartBlink02, osPriorityNormal, 0, 128);
  blink02Handle = osThreadCreate(osThread(blink02), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartBlink01 */
/**
  * @brief  Function implementing the blink01 thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartBlink01 */
void StartBlink01(void const * argument)
{
  /* init code for USB_HOST */
  MX_USB_HOST_Init();

  struct timespec ts;
  /* USER CODE BEGIN StartBlink01 */
  /* Infinite loop */
  for(;;)
  {
	srand(time(0));
	int num = (rand() % (10000 - 100 + 1)) + 100;
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);

	wr_czas_us time = czas_aktualny();
    wr_czas_do_ts(&ts, time);
    wr_czas_us timeChanged = ts_do_wr_czas(&ts);

    printf("startBlink01: time=%lld , timeChanged=%lld\n", time, timeChanged);

	osDelay(num);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartBlink01 */
}

/* USER CODE BEGIN Header_StartBlink02 */
/**
* @brief Function implementing the blink02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBlink02 */
void StartBlink02(void const * argument)
{
  /* USER CODE BEGIN StartBlink02 */
  /* Infinite loop */
  for(;;)
  {
	srand(time(0));
	int num = (rand() % (1000 - 100 + 1)) + 100;
    wr_czas_us timeMeasured = czas_aktualny();
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
	osDelay(num);

    int32_t diff = roznica_czasu(&timeMeasured);
    printf("startBlink02: timeMeasured=%llu, delay=%d, difference=%ld\n", timeMeasured, num, diff);
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
	osDelay(10);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartBlink02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
int _write(int file, char *ptr, int len) {
  /* Implement your write code here, this is used by puts and printf for example */
  for(int i=0 ; i<len ; i++)
    ITM_SendChar((*ptr++));
  return len;
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
