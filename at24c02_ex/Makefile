# check whether we're cross-compiling
ifneq ($(shell hostname), raspberrypi)
    RPI_CROSS_COMPILE = y
endif

ifeq ($(RPI_CROSS_COMPILE), y)
    CC = arm-linux-gnueabihf-gcc
else
    CC = gcc
endif

CFLAGS = 
DEPS = 
OBJ = at24c02.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

at24c02: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o at24c02
