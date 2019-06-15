# STM32 Collection
Some Programs run on STM32 single chip microcomputer.

P.S. The core source codes are under ./HARDWARE & ./SYSTEM & ./USER, others are libraries. And the programs are Keil projects, program on Keil uvision5 and run on STM32 SCM.

1. **GPIOKey**

   Function: When you press each of 4 buttons, the buzzer will beep of the lights will blink.

2. **GPIOKey+EXTI**

   Function: The same function with GPIOKey program, but use interrupts.
   
3. **Keyboard4x4**

   Function: Fetch the key you press on 4x4 keyboard, and print through serial port on monitor.
   
4. **Usart**

   Function: An implement of USART(Universal Synchronous Asynchronous Receiver Transmitter). This program receives message from serial port and send back another processed message.

5. **FrequencyMeasure(Square)**

   Function: Measure the frequency and duty ratio of square wave.

6. **InfraredTransmit**

   Function: YS-NEC module infrared modulation and demodulation test program.

7. **MeasureDistance**

   Function: Measure distance through ultrasound module.

8. **MeasureMotorRPM**

   Function: Measure the rotational speed of motor, output period and round-per-minute.
   
9. **SignalMeasure**

   Function: Measure times of voltage and calculates average.

10. **PWMMotorControl**

    Function: Control motor by motor driver module with PWM wave.

11. UsartOutputAdc

    Function: ADC sample and output to usart, so that we can see on PC.

12. VoiceSignalTest

    Function: Sample output of ISD-1820 module, which is a module to record audio and play, and output through usart to PC.

