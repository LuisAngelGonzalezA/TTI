import RPi.GPIO as GPIO # Cargamos la libreria RPi.GPIO  
from time import sleep  # cargamos la función sleep del módulo time 
  
GPIO.setmode(GPIO.BCM)  # Ponemos la Raspberry en modo BCM  
  
GPIO.setup(12, GPIO.OUT)  # Ponemos el pin GPIO nº25 como salida para el LED #1  
  
white = GPIO.PWM(12, 100)   # Creamos el objeto 'white' en el pin 25 a 100 Hz  
  
white.start(0)              # Iniciamos el objeto 'white' al 0% del ciclo de trabajo (completamente apagado)  


# A partir de ahora empezamos a modificar los valores del ciclo de trabajo
  
pause_time = 0.02           # Declaramos un lapso de tiempo para las pausas

voltaje_ingresado=2
voltaje_min=float(0.23)
voltaje_deseado=1
pendiente=0
b1=float(0.0)
b2=float(0.0)
b_a_usar=float(0.0)
duty=0
white.ChangeDutyCycle(100)      # LED #1 = i
#red.ChangeDutyCycle(100 - i)  # LED #2 resta 100 - i
sleep(pause_time)

try:                        # Abrimos un bloque 'Try...except KeyboardInterrupt'
    while True:             # Iniciamos un bucle 'while true'
        if voltaje_deseado <= voltaje_ingresado:
            
            pendiente=((100-0)/(voltaje_min-voltaje_ingresado))
            print(type(pendiente))
            print(pendiente)
            
            b1=(100.0-pendiente*(voltaje_min))
            print("-->",b1)
            b2=0-pendiente*(voltaje_ingresado)
            print("-->",b2)
            duty=pendiente*(voltaje_ingresado)+(b1)
            print("duty--->",duty)
            
            if duty>=0 and duty <= 1:
                
                print("si entro en b1")
                print("Duty vale -- >",duty)
                b_a_usar=b1
            else:
                duty=pendiente*(voltaje_ingresado)+(b2)
                if duty>=0 and duty <= 1:
                    print("si entro en b2")
                    print("Duty vale -- >",duty)
                    b_a_usar=b2
                
            
                
            print("B a usar-->",b_a_usar)
            duty=int(pendiente*(voltaje_deseado)+b_a_usar)
            
            if duty >= 100:
                duty=100
            print("Duty : -->",duty)
            white.ChangeDutyCycle(duty)      # LED #1 = i
                 #red.ChangeDutyCycle(100 - i)  # LED #2 resta 100 - i
            sleep(pause_time)             # Pequeña pausa para no saturar el procesador
            
        else:
            white.ChangeDutyCycle(100)      # LED #1 = i
                 #red.ChangeDutyCycle(100 - i)  # LED #2 resta 100 - i
            sleep(pause_time)             # Pequeña pausa para no saturar el procesador
            
            
        
                    
        
        
        
        
        
#        for i in range(0,100):            # De i=0 hasta i=101 (101 porque el script se detiene al 100%)
#            white.ChangeDutyCycle(i)      # LED #1 = i
#            #red.ChangeDutyCycle(100 - i)  # LED #2 resta 100 - i
#            sleep(pause_time)             # Pequeña pausa para no saturar el procesador
        
#        print("EL voltaje debe de ser 0v")
#        sleep(5)
#        for i in range(100,-1,-1):        # Desde i=100 a i=0 en pasos de -1  
#            white.ChangeDutyCycle(i)      # LED #1 = i
            #red.ChangeDutyCycle(100 - i)  # LED #2 resta 100 - i  
#            sleep(pause_time)             # Pequeña pausa para no saturar el procesador  
#        print("EL voltaje debe de ser 5v")
#        sleep(5)
except KeyboardInterrupt:   # Se ha pulsado CTRL+C!!
    white.stop()            # Detenemos el objeto 'white'
    red.stop()              # Detenemos el objeto 'red'
    GPIO.cleanup()          # Limpiamos los pines GPIO y salimos