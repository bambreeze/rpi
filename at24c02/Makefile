CC = gcc
CFLAGS =  -std=c99 -I. -lbcm2835
DEPS = 
OBJ = at24c02.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

at24c02: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o at24c02
