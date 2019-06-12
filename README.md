# STM32 Collection
Some Programs run on STM32 single chip microcomputer.

P.S. The core source codes are under ./HARDWARE & ./SYSTEM & ./USER, others are libraries. And the programs are Keil projects, program on Keil uvision5 and run on STM32 SCM.

1. GPIOKey

   Function: When you press each of 4 buttons, the buzzer will beep of the lights will blink.

2. GPIOKey+EXTI

   Function: The same function with GPIOKey program, but use interrupts.
   
3. Keyboard4x4

   Function: Fetch the key you press on 4x4 keyboard, and print through serial port on monitor.
   
4. Usart

   Function: An implement of USART(Universal Synchronous Asynchronous Receiver Transmitter). This program receives message from serial port and send back another processed message.

