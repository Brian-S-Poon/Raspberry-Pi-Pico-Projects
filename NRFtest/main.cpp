// VCC -> 3.3V
// GND -> GND
// CE -> GP8 SPI1 RX
// CSN -> GP9 SPI1 CSn
// SCK -> GP10 SPI1 SCK
// MOSI -> GP11 SPI1 TX
// MISO -> GP12 SPI1 RX
// 1k pull up resistor power

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "NRF24.h"
#include <stdio.h>
#include <string.h>

// 2 pico demo
int main() {    
    NRF24 nrf(spi1, 9, 8); 
    nrf.config(); // configure at start
    nrf.modeRX(); // set to recv

    gpio_init(25); // led on board
    gpio_init(15); // button
    gpio_init(16); // button

    gpio_set_dir(25, 1);
    gpio_set_dir(15,0);
    gpio_set_dir(16,0);

    char bufferOut[32] {0};
    char bufferIn[32] {0};

    while(true) {
        // button pins are always pulled HIGH, button swithces to gnd
        if(!gpio_get(15)) {
            // if pulled to ground by pressing
            nrf.modeTX();
            sprintf(bufferOut, "ON");
            nrf.sendMessage(bufferOut);
            nrf.modeRX();
        }
        else if(!gpio_get(16)) {
            nrf.modeTX();
            sprintf(bufferOut, "OFF");
            nrf.sendMessage(bufferOut);
            nrf.modeRX();
        }

        if(nrf.newMessage() == 1) { // if we have new message
            nrf.receiveMessage(bufferIn);
            if(strcmp(bufferIn, "ON") == 0) { // compare string, equal returns 0
                gpio_put(25, 1); // turn LED on
            }
            else if(strcmp(bufferIn, "OFF") == 0) { // compare string, equal returns 0
                gpio_put(25, 0); // turn LED off
            }
        }
    }
    return 0;
}


// first demo
/*
int main() {

    NRF24 nrf(spi1, 9, 8); // Port, CSN, CE
    nrf.config();
    nrf.modeTX();

    char buffer[32]; // buffer 32 bytes
    while(true) {
        sprintf(buffer, "45");
        buffer[30] = 'R';
        buffer[31] = 'O'; // not zero
        nrf.sendMessage(buffer);
        sleep_ms(1000);

        sprintf(buffer, "-45");
        buffer[30] = 'R';
        buffer[31] = 'O'; // not zero
        nrf.sendMessage(buffer);
        sleep_ms(1000);

    }
    return 0;
}*/