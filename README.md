# 🚀STM32 CAN Communication Project

---

## 📋 프로젝트 개요


이 프로젝트는 STM32F103과 STM32F411 보드를 사용하여, MCP2515 모듈을 통해 CAN 통신을 구현하고,
DHT11 센서에서 측정한 온습도 데이터를 송신 및 수신하여 LCD에 표시하는 시스템을 개발한 것입니다.
FreeRTOS를 적용하여 안정적인 데이터 통신과 태스크 관리를 수행했습니다.

## 🛠️ 사용한 기술
MCU: STM32F103 (Transmitter), STM32F411 (Receiver)

Sensor: DHT11 (온습도 센서)

CAN Controller: MCP2515 + TJA1050

Display: LCD (ST7735)

RTOS: FreeRTOS

Debugging: UART 통신

## 🛠️ 사용한 기술 스택
| 구분           | 내용                                           |
| :------------- | :-------------------------------------------- |
| MCU            | STM32F103 (Transmitter) <br> STM32F411 (Receiver) |
| Sensor         | DHT11 (온습도 센서)                           |
| CAN Module     | MCP2515                         |
| Display        | ST7735 (LCD)                                |
| RTOS           | FreeRTOS                                      |
| Communication  | CAN (SPI 기반 MCP2515) <br> UART (디버깅)    |
| IDE            | STM32CubeIDE                                  |
| Language       | C (HAL 라이브러리 활용)                       |
| Debugger       | ST-Link v2                                    |

## ⚙️ 개발 환경
IDE: STM32CubeIDE

Compiler: ARM-GCC

Debugger: ST-Link v2

Frameworks: HAL, FreeRTOS


## 📦 주요 기능
DHT11 센서로 온도/습도 데이터 주기적 측정

MCP2515를 통한 CAN 메시지 송수신

수신된 데이터를 LCD에 실시간 출력

UART를 통한 디버깅 및 상태 출력

FreeRTOS 기반 멀티태스킹 구조

## 📡 시스템 구성도

```plaintext
[DHT11] 
    │ 
[STM32F103] ── SPI ── [MCP2515]
    |
[UART 디버깅 출력]
    │
  CAN Bus
    │
[MCP2515] ── SPI ── [STM32F411] 
    │
[LCD (SPI)] 
```

## 🔄 시스템 흐름도

1. **Transmitter (STM32F103)**  
   - DHT11 데이터 주기적 측정  
   - CAN 메시지 생성 및 송신 (MCP2515 사용)  
   - 송신 상태 UART 출력  

2. **Receiver (STM32F411)**  
   - CAN 메시지 수신  
   - 데이터 파싱 및 LCD 출력  

3. **FreeRTOS Task 구조**  
   - CAN Rx Task  
   - LCD Update Task  


## 🔌 하드웨어 연결
### 🚀Transmitter
| 모듈      | STM32 핀 | 설정 | 비고          |
| :--------- | :-------- | :---------- | :------------ |
| CAN_CS    | PA4       | CS          |               |
| SPI (SCK) | PA5       | SCK         |               |
| SPI (MISO)| PA6       | SO          |               |
| SPI (MOSI)| PA7       | SI          |               |
| UART_TX   | PA9       | TX          |               |
| UART_RX   | PA10      | RX          |               |
| CS        | PB9       | CS          | 사용자 설정   |
| DHT11     | PB4       | DATA        |               |


### 🚀Receiver
| 모듈      | STM32 핀 | 설정 | 비고          |
| :--------- | :-------- | :---------- | :------------ |
| CAN CS    | PA4       | CS          | 사용자 설정   |
| SPI (SCK) | PA5       | SCK         |              |
| SPI (MISO)| PA6       | SO          |              |
| SPI (MOSI)| PA7       | SI          |              |
| CS_PIN    | PB7       | CS          | 사용자 설정   |
| DC_PIN    | PB8       | DC          | 사용자 설정   |
| RST_PIN   | PB9       | RST         | 사용자 설정   |



## 📝 주요 기능 및 코드 설명

### 🌡️ 데이터 송신 (Transmitter)
```c
 DHT_GetData(&temperature, &humidity);
 uint16_t TempToSend = (uint16_t)(temperature*100);
 uint16_t HumiToSend = (uint16_t)(humidity*100);

 txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
 txMessage.frame.id = 0x167;
 txMessage.frame.dlc = 8;
 txMessage.frame.data0 = (TempToSend >> 8) & 0xFF;
 txMessage.frame.data1 = TempToSend & 0xFF;
 txMessage.frame.data2 = (HumiToSend >> 8) & 0xFF;
 txMessage.frame.data3 = HumiToSend &0xFF;
 txMessage.frame.data4 = 0;
 txMessage.frame.data5 = 0;
 txMessage.frame.data6 = 0;
 txMessage.frame.data7 = 0;

 CANSPI_Transmit(&txMessage);

 if(CANSPI_Transmit(&txMessage) == 1)
 {
  printf("송신이 성공했습니다.\n");
 }
 else
 {
 printf("송신이 실패했습니다.\n");
 }

 HAL_Delay(1000);
```

### 🌡️ 데이터 수신 (Receiver)
```c
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
```
## ⚡ 문제 해결 과정
문제: 수신 측 값 갱신이 안 되는 문제
➔ 해결: 배열 대신 구조체 사용 및 FreeRTOS Queue 적용 → 데이터 처리 안정성 향상

문제: MCP2515 초기화 불안정
➔ 해결: SPI 설정 확인 및 초기화 순서 수정

## 📸 결과 화면

| 송신 측 (UART 디버깅) | 수신 측 (LCD 출력) |
|----------------------|---------------------|
|![제목 없음](https://github.com/user-attachments/assets/00d914a0-5ede-4812-b960-12f88769832b) | ![20250426_153716](https://github.com/user-attachments/assets/c08a239a-d9ae-4729-8693-bb6e32de049d) |




## 🔧 개선 사항 및 향후 계획


다양한 센서 추가 및 데이터 전송

데이터 로깅  ex)  내부 플래시, SD카드

