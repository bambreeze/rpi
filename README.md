# rpi
This is codes repository for my Raspberry Pi board

1. Hello World
----------------------
gcc -o hello hello.c
sudo ./hello

2. GPIO - led test
----------------------
sudo python led.py

gcc -o led led.c -lbcm2835
sudo ./led

3. GPIO - button test
----------------------
sudo python button.py

gcc -o button button.c -lbcm2835
sudo ./button

4. Read CPU temperature
-----------------------
sudo python read_cpu .py

gcc -o read_cpu_temp read_cpu_temp.c
./read_cpu_temp

5. Read DHT11 humidity and temperature
----------------------
gcc -o dht11 *.c -std=c99 -I. -lbcm2835
or
make

sudo ./dht11

