#include <stdio.h>  
#include <bcm2835.h>  
  
#define LED RPI_V2_GPIO_P1_11   // RPi Pin #11

int main(int argc, char **argv)
{
    uint8_t counter = 0;

	if (!bcm2835_init())  
		return 1;  

	// Set the pin to be an output
	bcm2835_gpio_fsel(LED, BCM2835_GPIO_FSEL_OUTP);  
    
	// Blinking the LED
	while (counter++ < 10) {
        bcm2835_gpio_write(LED, LOW);
		bcm2835_delay(1000);

        bcm2835_gpio_write(LED, HIGH);
	    bcm2835_delay(1000);
	}
    bcm2835_gpio_write(LED, LOW);

	bcm2835_close();  
	return 0;  
}
