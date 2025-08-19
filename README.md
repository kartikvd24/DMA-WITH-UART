# STM32 UART DMA Example

This project demonstrates how to send data from an STM32F4 microcontroller to a PC over UART using DMA (Direct Memory Access). When transmission completes, an onboard LED lights up to confirm a successful DMA transfer.

---

## Why Use DMA for UART?

**DMA** allows the microcontroller to move data between memory and peripherals (like UART) without CPU intervention. This is faster and reduces CPU workload, especially helpful for large or continuous transfers.

---

## How Registers Work & Their Significance

Below are the key peripheral registers and their roles:

| Peripheral           | Register(s)                                   | Purpose |
|----------------------|-----------------------------------------------|---------|
| RCC                  | `AHB1ENR`, `APB1ENR`                         | Enable clocks for GPIOA, DMA1, USART2           |
| GPIOA                | `MODER`, `AFR`                               | Configure PA2/PA3 as UART TX/RX pins            |
| USART2               | `CR1`, `CR3`, `BRR`, `SR`, `DR`              | Set UART operating mode, DMA enable, baud rate, flags for data ready/empty, send/receive data |
| DMA1_Stream6         | `CR`, `M0AR`, `PAR`, `NDTR`, `FCR`, `HIFCR`, `HISR` | Setup DMA transfer: source, destination, length, interrupt flags |

**Highlights:**
- **DMA1_Stream6->CR**: Set direction (memory-to-peripheral), transfer complete interrupt, channel number, enable stream
- **DMA1_Stream6->HIFCR**: Clear DMA interrupt flags after transfer
- **USART2->DR**: Data to be transmitted by UART
- **USART2->CR3**: Enable DMA requests for transmission
- **NVIC**: Enable DMA stream interrupts in the interrupt controller

---

## Project Flow

1. Set PA2/PA3 pins as UART TX/RX (alternate function).
2. Enable clocks for GPIOA, DMA1, USART2.
3. Configure UART2: transmit/receive, baud rate, enable DMA transmission.
4. Configure DMA1_Stream6: source data buffer (message), destination (USART2->DR), transfer length, interrupt.
5. When DMA transfer completes, interrupt is triggered and LED is turned on.

---

## RealTerm Usage

To see UART output from your STM32F4:

1. Connect STM32 UART TX (PA2) to a USB-UART adapter or ST-Link VCP RXD.
2. Open RealTerm (or similar) on your PC.
3. Set the baud rate to `115200`, data: 8 bit, stop: 1 bit, no parity, no flow control.
4. Run the code on your STM32 board.  
   You should see:
Hello from Stm32 DMA interface

5. On successful DMA completion, onboard LED turns ON.

## Files Included

- `main.c` - Main application logic and DMA/UART setup
- `uart.h` - UART and DMA configuration, register definitions
- `stm32f4xx.h` - STM32F4 hardware definitions

---

## Build & Flash Instructions

- Use STM32CubeIDE, Keil, or preferred toolchain.
- Wire PA2 (TX) and PA3 (RX) as described.
- Flash firmware to STM32F4.
- Observe UART message in RealTerm and LED indication for DMA transfer.

---

## Troubleshooting

- Ensure all relevant clocks are enabled.
- Confirm DMA interrupt handler is named `DMA1_Stream6_IRQHandler` correctly.
- Check DMA flag macros use **bit 27** for TCIF6/CTCIF6.
- Double-check UART, DMA, and NVIC configuration matches STM32F4 datasheet.

---

## Reference

See the STM32F4 Reference Manual,user guide and the datasheet from the 'https://www.st.com/content/st_com/en.html' for register bit definitions and peripheral configuration with the block diagram and the memory map.

---

