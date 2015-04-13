# rpi
This is codes repository for my Raspberry Pi board

1. GPIO - button test
----------------------
sudo python button.py

gcc -o button button.c -lbcm2835
sudo ./button

2. Read CPU temperature
-----------------------
python read_cpu_temp.py

gcc -o read_cpu_temp read_cpu_temp.c
./read_cpu_temp

3. GPIO - led test
----------------------
sudo python led.py

gcc -o led led.c -lbcm2835
sudo ./led

4. Read the DHT11 humidity and temperature
----------------------
gcc -o dht11 *.c -std=c99 -I. -lbcm2835
sudo ./dht11

