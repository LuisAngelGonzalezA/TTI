from Tkinter import*
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(18,GPIO.OUT)
pwm=GPIO.PWM(18,100);
pwm.start(0)

class App:
	def __init__(self,master):
		frame=Frame(master)
		frame.pack()
		scale=Scale(frame,from_=00,to=180,orient=HORIZONTAL,command=self.update)
		scale.grid(row=0)
	def update(self,angle):
		print(angle)
		duty = float(angle)/10.0 +2.5
		pwm.ChangeDutyCycle(duty)



root=Tk()
root.wm_title("SERVO")
app=App(root)
root.geometry("200x150+30+20")
root.mainloop()