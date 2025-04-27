/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tim.h"
#include "spi.h"
#include "usart.h"
#include "can.h"
#include "mcp2515.h"
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
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
 QueueHandle_t xQueue;


 extern SPI_HandleTypeDef hspi2;
 extern TIM_HandleTypeDef htim1;
 extern UART_HandleTypeDef huart1;


/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void DhtTask(void *parameter);
void LcdTask(void *parameter);
int _write(int file, char* p, int len){
	HAL_UART_Transmit(&huart1, (uint8_t*)p, len, HAL_MAX_DELAY);
	return len;
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
	xQueue= xQueueCreate(5, sizeof(float));
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  xTaskCreate(DhtTask,"DhtTask",128,NULL,3,NULL);
  xTaskCreate(LcdTask,"LcdTask",128,NULL,1,NULL);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }

  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void DhtTask(void *parameter)
{
	uCAN_MSG rxMessage;
	uint16_t rxValue1;
	uint16_t rxValue2;
	CANSPI_Initialize();
	fillScreen(BLACK);

	for(;;)
	{

		if(CANSPI_Receive(&rxMessage))
	    {
	        rxValue1 = ((uint16_t)rxMessage.frame.data0 << 8) | rxMessage.frame.data1;
	        rxValue2 = ((uint16_t)rxMessage.frame.data2 << 8) | rxMessage.frame.data3;
	        float temp = ((float)rxValue1)*0.01;
	        float humi = ((float)rxValue2)*0.01;
	        xQueueSendToBack(xQueue, &temp, portMAX_DELAY);
	        xQueueSendToBack(xQueue, &humi, portMAX_DELAY);

	    }
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void LcdTask(void *parameter)
{

	float temperature=0.0, humidity=0.0;
	char data1[10];
	char data2[10];
	for(;;)
	{

		if(xQueueReceive(xQueue, &temperature , portMAX_DELAY)==pdTRUE)
		{
			if(xQueueReceive(xQueue, &humidity , portMAX_DELAY)==pdTRUE)
			{

				ST7735_SetRotation(1);
				ST7735_WriteString(0,0, "temp : ", Font_11x18, WHITE, BLACK);
				snprintf(data1, sizeof(data1),"%.2f",temperature);
				ST7735_SetRotation(1);
				ST7735_WriteString(0,30, data1, Font_11x18, MAGENTA, BLACK);

				ST7735_SetRotation(1);
				ST7735_WriteString(0,60, "humi : ", Font_11x18, GREEN, BLACK);
				snprintf(data2, sizeof(data2),"%.2f",humidity);
				ST7735_SetRotation(1);
				ST7735_WriteString(0,90, data2, Font_11x18, MAGENTA, BLACK);




			}
		}
		vTaskDelay(pdMS_TO_TICKS(500));
	}


}

/* USER CODE END Application */

