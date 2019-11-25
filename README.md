# Arduino-Proximity-Alarm

Proximity Alarm that detects nearby objects and set off a buzzing noise when under a certain distance. Also display the distance to a LCD screen.

Built on Arduino 1.8.10.

# Parts list:
  
  * (1) x Elegoo Uno R3
  * (1) x USB cable
  * (1) x LCD1602 module
  * (1) x Potentiometer (10k)
  * (1) x 830 tie-points Breadboard
  * (1) x Ultrasonic sensor module
  * (1) x Passive buzzer
  * (1) x Transistor - PN2222
  * (1) x 1k ohm resistor
  * (1) x 220 ohm resistor
  * (26) x M-M wires (Male to Male jumper wires)
  
 #Libraries
 
  * <LiquidCrystal.h> -- Liquid crystal is used to run the LCD screen.

  * <HC-SR04.h> -- This library is used to run with the echo pin, the trig pin, and get the distance using the ultrasonic sensor.

  * “Pitches.h” -- Contains public constants for all the tones used by the passive buzzer.

