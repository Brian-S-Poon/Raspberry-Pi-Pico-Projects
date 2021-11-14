#include "pico/stdlib.h"

int main() {
    // Initialize onboard LED pin
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    // Initialize GPIO pin 15
    gpio_init(15);
    gpio_set_dir(15, GPIO_IN);

    // Initialize GPIO pin 16
    gpio_init(16);
    gpio_set_dir(16, GPIO_IN);
    
    // Infinite on loop
    while(true) {
        // If GPIO pin 15 is pressed, turn ON onboard LED
        if(gpio_get(15)) {
            gpio_put(25, true);
        }
        // If GPIO pin 16 is pressed, turn OFF onboard LED
        else if(gpio_get(16)) {
            gpio_put(25, false);
        }
    }
    return 0;
}
