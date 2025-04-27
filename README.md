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

Display: LCD (I2C 통신)

RTOS: FreeRTOS

Debugging: UART 통신

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
    │
  CAN Bus
    │
[MCP2515] ── SPI ── [STM32F411] 
    │
[LCD (SPI)] 
    │
[UART 디버깅 출력]
```

## 🔄 시스템 흐름도

1. **Transmitter (STM32F103)**  
   - DHT11 데이터 주기적 측정  
   - CAN 메시지 생성 및 송신 (MCP2515 사용)  
   - 송신 상태 UART 출력  

2. **Receiver (STM32F411)**  
   - CAN 메시지 수신  
   - 데이터 파싱 및 LCD 출력  
   - 수신 상태 UART 출력  

3. **FreeRTOS Task 구조**  
   - CAN Rx Task  
   - LCD Update Task  
   - Debug Task  

---


## 📂 프로젝트 구조

```plaintext
STM32-CAN-Communication-Project/
├── Transmitter/
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── can.h
│   │   │   ├── gpio.h
│   │   │   ├── main.h
│   │   │   ├── mcp2515.h
│   │   │   ├── spi.h
│   │   │   ├── stm32f4xx_hal_conf.h
│   │   │   ├── stm32f4xx_it.h
│   │   │   ├── tim.h
│   │   │   └── usart.h
│   │   ├── Src/
│   │   │   ├── can.c
│   │   │   ├── gpio.c
│   │   │   ├── main.c
│   │   │   ├── mcp2515.c
│   │   │   ├── spi.c
│   │   │   ├── ST7735.c
│   │   │   ├── stm32f4xx_hal_msp.c
│   │   │   ├── stm32f4xx_hal_timebase_tim.c
│   │   │   ├── stm32f4xx_it.c
│   │   │   ├── syscalls.c
│   │   │   ├── sysmem.c
│   │   │   ├── system_stm32f4xx.c
│   │   │   ├── tim.c
│   │   │   └── usart.c
│   └── README.md
├── Receiver/
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── can.h
│   │   │   ├── fonts.h
│   │   │   ├── FreeRTOSConfig.h
│   │   │   ├── GFX_FUNCTIONS.h
│   │   │   ├── gpio.h
│   │   │   ├── main.h
│   │   │   ├── mcp2515.h
│   │   │   ├── spi.h
│   │   │   ├── ST7735.h
│   │   │   ├── stm32f4xx_hal_conf.h
│   │   │   ├── stm32f4xx_it.h
│   │   │   ├── tim.h
│   │   │   └── usart.h
│   │   ├── Src/
│   │   │   ├── can.c
│   │   │   ├── fonts.c
│   │   │   ├── freertos.c
│   │   │   ├── GFX_FUNCTIONS.c
│   │   │   ├── gpio.c
│   │   │   ├── main.c
│   │   │   ├── mcp2515.c
│   │   │   ├── spi.c
│   │   │   ├── ST7735.c
│   │   │   ├── stm32f4xx_hal_msp.c
│   │   │   ├── stm32f4xx_hal_timebase_tim.c
│   │   │   ├── stm32f4xx_it.c
│   │   │   ├── syscalls.c
│   │   │   ├── sysmem.c
│   │   │   ├── system_stm32f4xx.c
│   │   │   ├── tim.c
│   │   │   └── usart.c
├── README.md
└── LICENSE
```

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

---
## ⚙️ 개발 환경
IDE: STM32CubeIDE

Compiler: ARM-GCC

Debugger: ST-Link v2

Frameworks: HAL, FreeRTOS

## 🔧 빌드 및 업로드
1. 해당 보드 프로젝트 `Import`  
2. `FreeRTOS` 설정 확인  
3. 빌드 및 업로드  
4. 하드웨어 연결 후 시스템 실행  

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
| UART1_TX  | PA9       | TX          |              |
| UART_RX   | PA10      | RX          |              |
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

## 📝 추가 참고사항
FreeRTOS의 큐(Queue)를 활용해 CAN 데이터 수신 안정성 확보

MCP2515 드라이버는 SPI 통신 기반으로 구현

초기 통신 안정화 과정에서 리셋 문제를 해결

## 📸 결과 화면
(※ LCD 출력 사진이나 UART 디버깅 로그 캡처 추가 예정)

## 🧑‍💻 개발자
Your Name (GitHub ID)
