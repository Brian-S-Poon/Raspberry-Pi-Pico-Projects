# Raspberry Pi Pico GT-U7 GPS Module

An embedded software C++ application to receive and encode GPS NMEA data from the GT-U7 GPS module.

## Required hardware
1x Raspberry Pi Pico <br>
1x Breadboard (Optional) <br>
1x GT-U7 GPS Module <br>
1x IPX antenna (Should come included with your GT-U7) <br>
Jumper wires of your choice depending on your setup (M/M) (M/F) (F/F)

## Required software
PlatformIO IDE (A plugin for Visual Studio Code) https://platformio.org/ <br>
TinyGPS++ library http://arduiniana.org/libraries/tinygpsplus/

## Hardware connections
GT-U7 VCC -> Pico VBUS (5V) #40 <br>
GT-U7 GND -> Pico GND #38 <br>
GT-U7 RXD -> Pico GPIO Pin 8 #11 <br>
GT-U7 TXD -> Pico GPIO Pin 9 #12 <br>
GT-U7 PPS -> NOT USED <br>

## Challenges encountered
I encountered multiple challenges when I attempted to setup the correct GPIO Pins on the Raspberry Pi Pico. <br> 
Firstly, I attempted using the SoftwareSerial library which only has support for the Arduino. <br>
Secondly, I mistakenly connected GT-U7 RX to Pico RX and GT-U7 TX to Pico TX, which is incorrect. RX has to connect to TX, and TX has to connect to RX. <br>
Lastly, I attempted to use UART0 TX and UART0 RX for Serial1 communication on the Pico which corresponds to GPIO Pin 0 and Pin 1. 
However, I learned that GPIO Pin 0 and Pin 1 are reserved for Serial communication on the computer and therefore connecting peripherals to these pins can cause failed
uploads to the Raspberry Pi Pico board. 
In conclusion I chose to use UART1 TX and UART1 RX for Serial2 communication which corresponds to GPIO Pin 8 and Pin 9 on the Pico board. <br>

## What I learned
I learned how to encode GPS NMEA data using the TinyGPS++ library. <br>
I also learned how to use Universal Asynchronous Receiver-Transmitter (UART) on the Raspberry Pi Pico board for serial communication with the GT-U7 GPS module.


