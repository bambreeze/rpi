# check whether we're cross-compiling
ifneq ($(shell hostname), raspberrypi)
    RPI_CROSS_COMPILE = y
endif

ifeq ($(RPI_CROSS_COMPILE), y)
    CC = arm-linux-gnueabihf-gcc
    CFLAGS = -std=c99 -I../bcm2835-1.35 -L../bcm2835-1.35 -lbcm2835
else
    CC = gcc
    CFLAGS = -std=c99 -I. -lbcm2835
endif

DEPS = 
OBJ = at24c02.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

at24c02: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o at24c02
