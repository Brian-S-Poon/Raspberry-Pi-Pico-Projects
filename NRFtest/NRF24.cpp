#include "NRF24.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

// constructor
NRF24::NRF24(spi_inst_t *port, uint16_t csn, uint16_t ce) {
    this->port = port;
    this->csn = csn;
    this->ce = ce;

    spi_init(this->port, 1000000) // initialize SPI
    // set functions for SPI (SCK, MOSI, MISO) -> GPIO pin 10,11,12
    gpio_set_function(10, GPIO_FUNC_SPI);
    gpio_set_function(11, GPIO_FUNC_SPI);
    gpio_set_function(12, GPIO_FUNC_SPI);

    // intialize CSN and CE
    gpio_init(csn);
    gpio_init(ce);

    // set direction for CSN and CE (to change btwn HIGH and LOW)
    gpio_set_dir(csn, 1);
    gpio_set_dir(ce, 1);

    // set CE to LOW and CSN to HIGH in the beginning
    ceLow();
    csnHigh();
}

// destructor
NRF24::~NRF24() {

}

uint8_t NRF24::readReg(uint8_t reg) {
    uint8_t result = 0;
    csnLow(); // switch csn value

    spi_write_blocking(port, &reg, 1); // spi write 1 byte
    spi_read_blocking(port, 0xff, &result, 1); // spi read 1 byte
    csnHigh(); // switch csn value

    return result;

} // read register
        
void NRF24::writeReg(uint8_t reg, uint8_t data) {
    writeReg(reg, &data, 1);
} // write to register

void NRF24::writeReg(uint8_t reg, uint8_t *data, uint8_t size) {
    reg = 0b00100000 | ( 0b00011111 & reg) // 0b set to binary
    csnLow();
    spi_write_blocking(port, &reg, 1);
    spi_write_blocking(port, (uint8_t*)data, size);
    csnHigh();
}

void NRF24::config() {
    csnHigh();
    ceLow();

    sleep_ms(11);

    writeReg(0, 0b00001010);
    sleep_us(1500);

    writeReg(1, 0); // set everything to 0

    writeReg(5, 60); // specify channel for communication

    writeReg(0x0a, (uint8_t*)"gyroc", 5); //test unit expecting gyroc, 5 bytes
    writeReg(0x10, (uint8_t*)"gyroc", 5); //test unit expecting gyroc, 5 bytes

    writeReg(0x11, 32);
} // configure

void NRF24::modeTX() {
    // first read bit

    uint8_t reg = readReg(0);
    reg &= ~(1<<0); // clear that bit 
    writeReg(0, reg);
    ceLow(); // transmit is low
    sleep_us(130);
} // mode to trasmit

void NRF24::modeRX() {
    uint8_t reg = readReg(0);
    reg |= (1<<0);
    writeReg(0, reg);
    ceHigh(); // recv is high
    sleep_us(130);
} // mode to receive

void NRF24::sendMessage(char *msg) {
    uint8_t reg = 0b10100000;
    csnLow();
    spi_write_blocking(port, &reg, 1);
    spi_write_blocking(port, (uint8_t*)msg, 32); // 32 byte messages
    csnHigh();

    ceHigh();
    sleep_us(500); // dont switch modes too fast
    ceLow();
} // send msg
void NRF24::receiveMessage(char *msg) {
    uint8_t cmd = 0b01100001; // cmd is command
    csnLow();
    spi_write_blocking(port, &cmd, 1);

    spi_read_blocking(port, 0xff, (uint8_t*)msg, 32);
    csnHigh();
} // recv msg


uint8_t NRF24::newMessage() {
    uint8_t fifo_status = readReg(0x17); // check data status

    return !(0x00000001 & fifo_status);
} // check if new message came in