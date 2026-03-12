# STM32 Advanced Embedded Software Development Projects

This repository contains projects, custom driver software, and hardware control applications developed as part of the **"Advanced Embedded Software Development with STM32"** course on BTK Academy.

Built from scratch in alignment with the course curriculum, these projects cover advanced embedded systems concepts ranging from basic GPIO control to Direct Memory Access (DMA), USB OTG, Low Power modes, IMU sensor data processing, and Nextion HMI display management.

## 🗂️ Folder Structure and Project Contents

The projects are categorized by their development stages and core concepts:

### 1. Basic I/O and Custom Driver Development
* `001_GPIO_Configuration`: Fundamental GPIO port/pin configurations.
* `002_Debounce_Integration`: Algorithmic approaches to prevent mechanical switch bouncing.
* `003_IO_Driver`: Hardware-independent, custom GPIO driver architecture.
* `026_Volatile` & `027_Volatile_EXTI`: The critical role of the `volatile` keyword in memory optimization and External Interrupt (EXTI) management.

### 2. Analog-to-Digital Conversion (ADC/DAC) and DMA
* `005_Multi_Channel_ADC`: Multi-channel analog data reading using Polling/Interrupt methods.
* `006_Multi_Channel_ADC_With_DMA`: High-speed ADC reading via Direct Memory Access (DMA) without CPU intervention.
* `007_ADC_Driver`: Creation of an abstracted hardware library for the ADC module.
* `008_DAC`: Converting digital data into analog signals.

### 3. Timers and Signal Processing
* `009_Timer` & `022_Software_Timer`: Hardware and software timer initialization.
* `010 - 014 (Timer Modes)`: Utilization of timer modes including External Trigger, Internal Trigger, Slave Reset, Gated, and Trigger.
* `015_Timer_Input_Capture`: Measuring the frequency and period of incoming external signals.
* `016_Timer_Output_Compare`: Generating precision-timed output signals.
* `017_PWM`: Pulse Width Modulation (PWM) generation for motor drivers or lighting control.

### 4. Communication Protocols, Peripherals, and Sensors
* `018_UART_Printf`: Standard UART communication and `printf` function retargeting for debugging.
* `019_I2C_2x16_LCD`: Character LCD control using the I2C protocol.
* `020_MEMS_LIS3DSH`: Reading and processing 3-axis accelerometer (MEMS) data via the SPI protocol.
* `021_USB_OTG_CDC`: Configuring the microcontroller as a USB device (Virtual COM Port - VCP).

### 5. User Interface (HMI) and Power Optimization
* `028_Nextion_Display_Control`: Bidirectional asynchronous data communication and UI control with Nextion HMI smart displays via UART.
* `023_LP_Sleep_Mode`: Entering Sleep mode to reduce power consumption.
* `024_LP_Stop_Mode`: Deep sleep application where clock signals are stopped.
* `025_LP_Standby_Mode`: Transitioning to Standby mode for minimum power consumption and handling wake-up scenarios.
* `BTK_Project`: The final integration project combining all the skills acquired during the course.

### 6. Hardware Documentation and Visual Assets (`assets`)
* `assets/`: This directory contains the system block diagrams (created via draw.io) that outline the overall software/hardware architecture. It also includes Fritzing wiring schematics detailing the pinout and electrical connections for specific hardware setups, such as Servo Motor and RGB LED configurations.

### 7. HMI Design Files (`Nextion_tools`)
* `Nextion_tools/`: Contains the raw Nextion Editor project files (`.HMI`). These source files demonstrate the GUI design, variable mapping, and event-driven button logic used in the intelligent display applications before being compiled for the Nextion screen.

## 🛠️ Hardware Requirements and Components
* **Development Board:** STM32F4 Discovery Board
* **Displays:** Nextion HMI Display, 2x16 Character LCD Display (with I2C module)
* **Actuators & Sensors:** Servo Motor, LIS3DSH MEMS Accelerometer (on-board)
* **Basic Components:** Push Buttons, Potentiometer, Resistors, RGB LEDs
* **Wiring & Prototyping:** Jumper cables and Breadboard

## 💻 Software & Development Tools
* **IDE:** STM32CubeIDE (v1.14.1)
* **Monitoring & Debugging:** STM32CubeMonitor, STM32CubeProgrammer
* **Serial Communication:** Termite (RS232 Terminal)
* **HMI Design:** Nextion Editor
* **Circuit & Block Diagrams:** Fritzing, Draw.io
* **Asset Conversion:** Image2LCD / C-Array Generator

## 🚀 Engineering Highlights
- **DMA Integration:** Enabled peripherals to transfer data independently of the processor core.
- **Driver Abstraction:** Aimed to abstract the main code from the hardware layer, as demonstrated in the `003_IO_Driver` and `007_ADC_Driver` projects.
- **Energy Efficiency:** Actively implemented Low Power modes, crucial for battery-operated systems or industrial standards.

## ⚙️ Installation and Usage
1. Clone this repository to your local machine:
   ```bash
   git clone [https://github.com/yunus-kunduz/STM32_Advanced_Embedded_Systems.git](https://github.com/yunus-kunduz/STM32_Advanced_Embedded_Systems.git)