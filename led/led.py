#!/usr/bin/env python

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
# need to set up every channel which are using as an input or an output
GPIO.setup(11, GPIO.OUT)

count = 0
while True:
    GPIO.output(11, GPIO.LOW)
    time.sleep(1)
	
    GPIO.output(11, GPIO.HIGH)
    time.sleep(1)

    count = count + 1
GPIO.output(11, GPIO.LOW)
