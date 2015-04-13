#include <bcm2835.h>  

// Blinks on RPi Plug P1 pin 11 (which is GPIO pin 17)  
#define PIN RPI_GPIO_P1_11  

int main(int argc, char **argv)  
{  
    if (!bcm2835_init())  
        return 1;  

    // Set the pin to be an output  
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);  

    // Blink  
    while (1)  
    {  
        bcm2835_gpio_write(PIN, HIGH);  
        bcm2835_delay(100);  

        bcm2835_gpio_write(PIN, LOW);  
        bcm2835_delay(100);  
    }  
    bcm2835_close();  
    return 0;  
}
