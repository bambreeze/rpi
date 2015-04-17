#include <stdio.h>  
#include <errno.h>  
#include <fcntl.h>  
#include <linux/i2c-dev.h>  

#define AT24C02_I2C_ADDR 0x50  

int main (void)
{  
    int fd = 0;  
    unsigned char data = 0;

    fd = open("/dev/i2c-1", O_RDWR);  
    if (fd < 0) {  
        printf("Error opening file: %s\n", strerror(errno));  
        return 1;  
    }

    if (ioctl(fd, I2C_SLAVE, AT24C02_I2C_ADDR) < 0) {  
        printf("ioctl error: %s\n", strerror(errno));  
        return 1;  
    }

    data = 0x69;
    write(fd, &data, 1);

    return 0;  
}
