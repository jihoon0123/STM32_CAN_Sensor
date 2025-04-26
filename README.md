#STM32 CAN Communication Project


##📋 프로젝트 개요


이 프로젝트는 STM32F103과 STM32F411 보드를 사용하여, MCP2515 모듈을 통해 CAN 통신을 구현하고,
DHT11 센서에서 측정한 온습도 데이터를 송신 및 수신하여 LCD에 표시하는 시스템을 개발한 것입니다.
FreeRTOS를 적용하여 안정적인 데이터 통신과 태스크 관리를 수행했습니다.

🛠️ 사용한 기술
MCU: STM32F103 (Transmitter), STM32F411 (Receiver)

Sensor: DHT11 (온습도 센서)

CAN Controller: MCP2515 + TJA1050

Display: LCD (I2C 통신)

RTOS: FreeRTOS

Debugging: UART 통신

📦 주요 기능
DHT11 센서로 온도/습도 데이터 주기적 측정

MCP2515를 통한 CAN 메시지 송수신

수신된 데이터를 LCD에 실시간 출력

UART를 통한 디버깅 및 상태 출력

FreeRTOS 기반 멀티태스킹 구조

🖼️ 시스템 구성도
plaintext
복사
편집
[DHT11] --> [STM32F103 + MCP2515] --> CAN Bus --> [MCP2515 + STM32F411] --> [LCD 출력]
🗂️ 디렉토리 구조
markdown
복사
편집
/Transmitter
    ├── Core
    ├── Drivers
    └── FreeRTOS

/Receiver
    ├── Core
    ├── Drivers
    └── FreeRTOS

/Docs
    └── System_Architecture.png

/README.md
⚙️ 개발 환경
IDE: STM32CubeIDE

Compiler: ARM-GCC

Debugger: ST-Link v2

Frameworks: HAL, FreeRTOS

🚀 빌드 및 실행 방법
STM32CubeIDE로 프로젝트 Import

각각의 보드에 맞게 프로젝트 빌드 후 업로드

두 보드를 MCP2515 모듈과 연결하여 CAN 통신 설정

시스템 실행 및 디버깅

📝 추가 참고사항
FreeRTOS의 큐(Queue)를 활용해 CAN 데이터 수신 안정성 확보

MCP2515 드라이버는 SPI 통신 기반으로 구현

초기 통신 안정화 과정에서 리셋 문제를 해결

📸 결과 화면
(※ LCD 출력 사진이나 UART 디버깅 로그 캡처 추가 예정)

🧑‍💻 개발자
Your Name (GitHub ID)
