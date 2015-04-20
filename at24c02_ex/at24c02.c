#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "i2c-dev.h"

#define AT24C02_I2C_ADDR 0x50  

int i2c_write_data (int fd, uint16_t addr, uint8_t offset, uint8_t val)
{
    struct i2c_rdwr_ioctl_data *data = NULL;

    data = (struct i2c_rdwr_ioctl_data *) malloc(sizeof(struct i2c_rdwr_ioctl_data));
    if (!data) {
        printf("Memory alloc failed for *struct i2c_rdwr_ioctl_data*\n");
        return -1;
    }

    data->nmsgs = 1;
    data->msgs  = (struct i2c_msg *) malloc(data->nmsgs * sizeof(struct i2c_msg));
    if (!data->msgs) {
        printf("Memory alloc failed for *struct i2c_msg*\n");
        free(data);
        return -1;
    }

    data->msgs[0].buf = (unsigned char *) malloc(2 * sizeof(unsigned char));
    if (!data->msgs[0].buf) {
        printf("Memory alloc failed for *msg buf*\n");
        free(data->msgs);
        free(data);
        return -1;
    }

    data->msgs[0].addr = addr;
    data->msgs[0].flags = 0;
    data->msgs[0].len = 2;
    data->msgs[0].buf[0] = offset;
    data->msgs[0].buf[1] = val;

    if (ioctl(fd, I2C_RDWR, (unsigned long)data) < 0) {
        printf("ioctl failed\n");
        free(data->msgs[0].buf);
        free(data->msgs);
        free(data);
        return -1;
    }

    free(data->msgs[0].buf);
    free(data->msgs);
    free(data);
    return 0;
}

int main (void)
{
    int i = 0;
    int fd = 0;  
    unsigned char data[16];
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
    memset(data, 0, 16);
    counter = read(fd, data, 16);
    if (counter != 16) {
        printf("read fail!\n");
    } else {
        for (i = 0; i < 16; i++) {
            printf("Data[%d] is: 0x%x\n", i, data[i]);
        }
    }

    // Random read
    data[0] = i2c_smbus_read_byte_data(fd, 0x3);
    printf("The 4th data is: %x\n", data[0]);

    data[0] = i2c_smbus_read_byte_data(fd, 0x1);
    printf("The 2nd data is: %x\n", data[0]);

    data[0] = 'H';
    data[1] = 'e';
    data[2] = 'l';
    data[3] = 'l';
    data[4] = 'o';
    data[5] = ',';
    data[6] = ' ';
    data[7] = 'w';
    data[8] = 'o';
    data[9] = 'r';
    data[10] = 'l';
    data[11] = 'd';
    data[12] = '!';

    // write using raw i2c commands - failed
    for (i = 0; i < 16; i++) {
        if (i2c_write_data (fd, AT24C02_I2C_ADDR, i, data[i])) {
            printf("write fail!\n");
            return -1;
        }
    }

    // write using smbus commands - failed
    for (i = 0; i < 16; i++) {
        if (i2c_smbus_write_byte_data(fd, i, data[i])) {
            printf("write fail!\n");
            return -1;
        }
    }

    return 0;  
}
