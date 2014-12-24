#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <bcm2835.h>

#define I2C_ADDR_AT24C02 0x50

int main(int argc, char **argv)
{
    int rc = 0;
    int i = 0;
    int counter = 0;
    unsigned char rbuf = 0;

	if (!bcm2835_init())  
		return 1;  

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(I2C_ADDR_AT24C02);
    bcm2835_i2c_set_baudrate(10000); /* 10 KHz */
    
    // read
    counter = 8;
    for (i = 0; i < counter; i++) {
        rc = bcm2835_i2c_read(&rbuf, 1);
        if (!rc) {
            printf("Read rbuf = %x\n", rbuf);
        } else {
            printf("ERROR! rc = %d\n", rc);
        }
    }

    // Just leave them as i2c pin to make i2c tools happy :-)
    //bcm2835_i2c_end();   
    bcm2835_close();

    return 0;
}
