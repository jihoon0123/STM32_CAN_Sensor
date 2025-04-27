/*
 * dht.c
 *
 *  Created on: Mar 28, 2025
 *      Author: user
 */

#include "dht.h"


uint32_t pre_time;
uint32_t cMillis;
extern TIM_HandleTypeDef htim1;

void Delay (uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  while (__HAL_TIM_GET_COUNTER(&htim1) < delay);
}

uint8_t DHT_Start(void)
{
	bool response = 0;
	GPIO_InitTypeDef GPIO_InitStructPrivate = {0};
    GPIO_InitStructPrivate.Pin = DHT_OUT_Pin;
	GPIO_InitStructPrivate.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructPrivate.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructPrivate.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DHT_OUT_GPIO_Port, &GPIO_InitStructPrivate);
	HAL_GPIO_WritePin(DHT_OUT_GPIO_Port, DHT_OUT_Pin, GPIO_PIN_RESET);
	HAL_Delay(18);
	HAL_GPIO_WritePin(DHT_OUT_GPIO_Port, DHT_OUT_Pin, GPIO_PIN_SET);
	Delay(30);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT_OUT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	Delay(40);
	if (!(HAL_GPIO_ReadPin (DHT_OUT_GPIO_Port, DHT_OUT_Pin)))
	  {
	    Delay(80);
	    if ((HAL_GPIO_ReadPin (DHT_OUT_GPIO_Port, DHT_OUT_Pin)))
	    {
	    	response = 1;
	    }
	  }
	  pre_time = HAL_GetTick();
	  cMillis = HAL_GetTick();
	  while ((HAL_GPIO_ReadPin (DHT_OUT_GPIO_Port, DHT_OUT_Pin)) && cMillis- pre_time < 2)
	  {
	    cMillis = HAL_GetTick();
	  }

	return response;

}

uint8_t DHT_Read(void)
{
   uint8_t a, b=0;
   for (a=0;a<8;a++)
     {
       pre_time = HAL_GetTick();
       cMillis = HAL_GetTick();
       while (!(HAL_GPIO_ReadPin (DHT_OUT_GPIO_Port, DHT_OUT_Pin)) && cMillis- pre_time < 2)
       {
         cMillis = HAL_GetTick();
       }
       Delay (40);
       if (!(HAL_GPIO_ReadPin (DHT_OUT_GPIO_Port, DHT_OUT_Pin)))
         b&= ~(1<<(7-a));
       else
         b|= (1<<(7-a));
       pre_time = HAL_GetTick();
       cMillis = HAL_GetTick();
       while ((HAL_GPIO_ReadPin (DHT_OUT_GPIO_Port, DHT_OUT_Pin)) && cMillis- pre_time < 2)
       {
         cMillis = HAL_GetTick();
       }
     }
     return b;

}

void DHT_GetData(void *temperature, void *humidity)
{
  uint8_t RHI, RHD, TCI, TCD, SUM;

	if (DHT_Start())
	{
	    RHI = DHT_Read();
	    RHD = DHT_Read();
	    TCI = DHT_Read();
	    TCD = DHT_Read();
	    SUM = DHT_Read();

	if (RHI + RHD + TCI + TCD == SUM)
	 {
		float *temp = (float *)temperature;
		float *hum = (float *)humidity;

		*temp = (float)TCI + (float)(TCD / 10.0);
		*hum = (float)RHI + (float)(RHD / 10.0);
	 }
	}
}
