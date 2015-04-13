#!/usr/bin/env python

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
# need to set up every channel which are using as an input or an output
GPIO.setup(13, GPIO.IN)
GPIO.setup(15, GPIO.IN)

count = 0
while True:
    key_button1 = GPIO.input(13)
    key_button2 = GPIO.input(15)
	
    if (key_button1 == 0):
         count = count + 1
         print("The key_button1 is 0")
    else:
         print("The key_button1 is 1")		 
    time.sleep(1)
	
    if (key_button2 == 0):
         count = count + 1
         print("The key_button2 is 0")
    else:
         print("The key_button2 is 1")
    time.sleep(1)
