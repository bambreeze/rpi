CC = gcc
CFLAGS =  -std=c99 -I. -lbcm2835
DEPS = 
OBJ = dht11.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dht11: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o dht11
