#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <fcntl.h>  
#include <linux/i2c-dev.h>  

#define AT24C02_I2C_ADDR 0x50  

int main (void)
{
    int i = 0;
    int fd = 0;  
    unsigned char data[8];
    int counter = 0;

    fd = open("/dev/i2c-1", O_RDWR);  
    if (fd < 0) {  
        printf("Error opening file: %s\n", strerror(errno));  
        return 1;  
    }

    if (ioctl(fd, I2C_SLAVE, AT24C02_I2C_ADDR) < 0) {  
        printf("ioctl error: %s\n", strerror(errno));  
        return 1;  
    }

    // current address read
    memset(data, 0, 8);
    counter = read(fd, data, 8);
    if (counter != 8) {
        printf("read fail!\n");
    } else {
        for (i = 0; i < 8; i++) {
            printf("Data[%d] is: 0x%x\n", i, data[i]);
        }
    }

    //data = 0x69;
    //write(fd, &data, 1);

    return 0;  
}
