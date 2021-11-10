#pragma once
#include "hardware/spi.h"
#include "hardware/gpio.h"

class NRF24 {
    private:
        // private variables
        spi_inst_t *port // spi port
        uint16_t csn; // csn pin
        uint16_t ce; // ce pin


        // private functions

        // functions to set CSN and CE to HIGH and LOW
        void csnLow() {
            gpio_put(csn, 0);
        }
        void csnHigh() {
            gpio_put(csn, 1);
        }
        void ceLow() {
            gpio_put(ce, 0);
        }
        void ceHigh() {
            gpio_put(ce, 1);
        }


    public:
        uint8_t readReg(uint8_t reg); // read register
        
        void writeReg(uint8_t reg, uint8_t data); // write to register
        void writeReg(uint8_t reg, uint8_t *data, uint8_t size);
        
        void config(); // configure

        void modeTX(); // mode to trasmit
        void modeRX(); // mode to receive

        void sendMessage(char *msg); // send msg
        void receiveMessage(char *msg); // recv msg


        uint8_t newMessage(); // check if new message came in
        
        
        NRF24(spi_inst_t *port, uint16_t csn, uint16_t ce);
        ~NRF24();

};