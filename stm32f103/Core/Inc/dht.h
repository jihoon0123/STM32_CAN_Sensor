/*
 * dht.h
 *
 *  Created on: Mar 28, 2025
 *      Author: user
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "main.h"
#include "tim.h"

uint8_t DHT_Start();
uint8_t DHT_Read();
void DHT_GetData(void *temperature, void *humidity);

#endif /* INC_DHT_H_ */
