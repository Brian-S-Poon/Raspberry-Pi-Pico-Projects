#include "pico/stdlib.h"

int main() {
    // Initialize Onboard LED pin
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    // Infinite on loop
    while(true) {
        // Turn Onboard LED on
        gpio_put(25, true);
        sleep_ms(1000);
        // Turn Onboard LED off
        gpio_put(25, false);
        sleep_ms(1000);
    }
    return 0;
}
