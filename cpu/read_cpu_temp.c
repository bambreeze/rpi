#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define CPU_THERMAL_FILE "/sys/class/thermal/thermal_zone0/temp"
int main(int argc, char **argv)
{
    int fd = 0;
    unsigned char temp;
    int i = 0;

    fd = open(CPU_THERMAL_FILE, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "%s: %s\n", CPU_THERMAL_FILE, strerror(errno));
        return 1;
    }
    
	printf("CPU temp: ");
    for (i = 0; i < 6; i++) {
        read(fd, &temp, 1);
        printf("%c", temp);
        if (i == 1)
            printf(".");
    }
    printf("\n");

    return 0;
}

