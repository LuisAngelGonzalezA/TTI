import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(12,GPIO.OUT)

led=GPIO.PWM(12,100)

#while True:
led.start(0)
 #   for i in range(0,100,1):
led.ChangeFrequency(100)

led.ChangeDutyCycle(100)
  #      print(i)
        #time.sleep(1.0)
        
    