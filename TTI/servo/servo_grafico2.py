# Servo Control
import math
from Tkinter import*
import time
import wiringpi
 
# use 'GPIO naming'
wiringpi.wiringPiSetupGpio()
 
# set #18 to be a PWM output
wiringpi.pinMode(18, wiringpi.GPIO.PWM_OUTPUT)
 
# set the PWM mode to milliseconds stype
wiringpi.pwmSetMode(wiringpi.GPIO.PWM_MODE_MS)
 
# divide down clock
wiringpi.pwmSetClock(192)
wiringpi.pwmSetRange(2000)           
 
delay_period = .01
class App:
	def __init__(self,master):
		frame=Frame(master)
		frame.pack()
		scale=Scale(frame,from_=1,to=180,orient=HORIZONTAL,command=self.update)
		scale.grid(row=0)
	def update(self,angle):
		print(angle)
		#duty = int(math.ceil((float(angle)+45)/.9))
		duty = int(math.ceil(39*(float(angle)+46.1538)/36))
		wiringpi.pwmWrite(18, duty)
                #print(duty)
                time.sleep(delay_period)

root=Tk()
root.wm_title("SERVO")
app=App(root)
root.geometry("200x150+30+20")
root.mainloop()