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
    unsigned char len = 0;
    unsigned char rbuf[16];
    unsigned char wbuf[16];

	if (!bcm2835_init())  
		return 1;  

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(I2C_ADDR_AT24C02);
    //bcm2835_i2c_setClockDivider(/*BCM2835_I2C_CLOCK_DIVIDER_2500*/7500); /* ~32 kHz */
    
    // read
    len = 1;
    rc = bcm2835_i2c_read(rbuf, len);
    printf("Read Result = %d\n", rc);
    for (i = 0; i < len; i++) {
        printf("Read rbuf[%d] = %x\n", i, rbuf[i]);
    }

    // write
    /*wbuf[0] = 0x5a;
    rc = bcm2835_i2c_write(wbuf, len);
    printf("Write Result = %d\n", rc);*/

    bcm2835_i2c_end();   
    bcm2835_close();
    return 0;
}
