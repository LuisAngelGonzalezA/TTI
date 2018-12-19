from Tkinter import*
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(12,GPIO.OUT)
pwm=GPIO.PWM(12,100);
pwm.start(0)

class App:
	def __init__(self,master):
		frame=Frame(master)
		frame.pack()
		scale=Scale(frame,from_=10,to=180,orient=HORIZONTAL,command=self.update)
		scale.grid(row=0)
	def update(self,angle):
		print(angle)
		duty = float(angle)/10.0 +2.5
		pwm.ChangeDutyCycle(duty)
		time.sleep(0.01)



root=Tk()
root.wm_title("SERVO")
app=App(root)
root.geometry("200x150+30+20")
root.mainloop()
		
		
#while(True):
#    angle=input("Que grado desea")
    #duty = float(angle)/10.0 +2.5
#    duty=1./18.*float(angle)+2
#    pwm.ChangeDutyCycle(duty)
#    time.sleep(1)
    