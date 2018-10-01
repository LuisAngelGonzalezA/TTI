#test_servo_2.py
#mover servo en python

###############configuraciones iniciales#############
import RPi.GPIO as GPIO # cargar libreria
import time # carga libreria del tiempo
GPIO.setmode(GPIO.BOARD)# establece la numeracion de los pines tipo fisico
ServoPin=11 # el pin 11 sera la variable 11
GPIO.setup(ServoPin,GPIO.OUT)# establece que el pin sera de salida


pwm=GPIO.PWM(11,50) # en el pin 11 el pulso sera de 50 Hz
pwm.start(7,5) #pulso medio , servo quieto(servo continuo) o a 90 grados (servo no continuo)



#movera el servo de un lado a otro en forma infinita ya que es un loop
while(1):
  
#en un sentido
    for i in range(0,180): #parametro que cambia en la formula de 0 a 180
        DC=1./18.*(i)+2    #relacion lineal entre DC y el angulo
        pwm.ChangeDutyCycle(DC)  #cambia el porcentaje del periodo con la señal en alto 
        time.sleep(.01) #cambia la velocidad del movimiento

#en el otro sentido    
    for i in range(180,0):
        DC=1./18.*(i)+2
        pwm.ChangeDutyCycle(DC)
        time.sleep(.01)

pwm.stop() #para el servo
GPIO.cleanup()#limpia las configuraciones de los GPIO