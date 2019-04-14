#!/usr/bin/env python
 
#importamos el modulo para trabajar con sockets
import socket
 
#Creamos un objeto socket para el servidor. Podemos dejarlo sin parametros pero si 
#quieren pueden pasarlos de la manera server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s = socket.socket()
 
#Nos conectamos al servidor con el metodo connect. Tiene dos parametros
#El primero es la IP del servidor y el segundo el puerto de conexion

s.connect(("192.168.100.28", 51718))
print "\nRecibiendo datos de Servidor\n\n"
data=s.recv(1024)

print "\tEl servidor envio latitud   ---->>:  "+ data
s.send("ok")
data=s.recv(1024)
print "\tEl servidor envio longitud  ---->>:  " + data
s.send("ok")
data=s.recv(1024)
print "\tEl servidor envio la hora   ---->>:  " + data
s.send("ok")
print "\n"



 	
#Imprimimos la palabra Adios para cuando se cierre la conexion
print "\n\nFinalizando lectura."
 
#Cerramos la instancia del objeto servidor
s.close()
