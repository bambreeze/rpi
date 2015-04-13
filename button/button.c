#include <stdio.h>  
#include <bcm2835.h>  
  
#define BUTTON1 RPI_V2_GPIO_P1_13 //    = 27,  ///< Version 2, Pin P1-13
#define BUTTON2 RPI_V2_GPIO_P1_15 //    = 22,  ///< Version 2, Pin P1-15

int main(int argc, char **argv)
{
    uint8_t data = 0;
    uint8_t btn_counter1 = 0;
    uint8_t btn_counter2 = 0;

	if (!bcm2835_init())  
		return 1;  

	// Set the pin to be an input  
	bcm2835_gpio_fsel(BUTTON1, BCM2835_GPIO_FSEL_INPT);  
	bcm2835_gpio_fsel(BUTTON2, BCM2835_GPIO_FSEL_INPT);  
    

	// Reading  
	while (1)  
	{  
        data = bcm2835_gpio_lev(BUTTON1);
        printf("Reading button1: %d\n", data);
        if (data)
            btn_counter1++;
		bcm2835_delay(1000);  

        data = bcm2835_gpio_lev(BUTTON2);
        printf("Reading button2: %d\n", data);
        if (data)
            btn_counter2++;
		bcm2835_delay(1000);  

        printf("--- The btn_counter1 is %d, btn_counter2 is %d ---\n",
                btn_counter1, btn_counter2);
	}  

	bcm2835_close();  
	return 0;  
}  
