#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
import numpy as np
import matplotlib.pyplot as plt 
import numpy as np 
import matplotlib.animation as animation
from tkinter import *
from tkinter import ttk




lista1 = [11,2,3,15,8,13,21,34]   # Declara lista1 con 8 valores
plt.plot(lista1)   # Dibuja el grafico
plt.xlabel("abscisa")   # Inserta el titulo del eje X 
plt.ylabel("ordenada")   # Inserta el titulo del eje Y
plt.ioff()   # Desactiva modo interactivo de dibujo
lista2 = [2,3,4,2,3,6,4,10]   # Declara lista2 con 8 valores
plt.plot(lista2)   # No dibuja datos de lista2
plt.ion()   # Activa modo interactivo de dibujo
plt.plot(lista2)   # Dibuja datos de lista2 sin borrar datos de lista1
plt.ioff()   # Desactiva modo interactivo
lista3 = [9,15,9,15,9,15,9,15]   # Declara lista3 con 8 valores
plt.plot(lista3)   # No dibuja datos de lista3

plt.title("Grafica")   # Establece nuevo titulo pero no muestra en grafico
plt.grid(True)  # Activa cuadrícula del gráfico pero no se muestra

#plt.ion()   # Activa modo interactivo de dibujo

plt.plot(lista1, marker='x', linestyle=':', color='b', label = "Enero")
plt.plot(lista2, marker='*', linestyle=':', color='g', label = "Febrero")
plt.plot(lista3, marker='o', linestyle='--', color='r', label = "Marzo")
plt.legend(loc="upper left")
plt.show()   # Muestra cuadrícula del gráfico



class ini():
	def __init__(self):
	   self.fig = plt.figure()
	   self.ax1 = self.fig.add_subplot(1,1,1)
	   self.datosy=[]
	   self.datosx=[]

	def animada(self,i):    #aqui es donde agrego la i
	   datostext = open('/home/luis/Documentos/pruebas_python/datos.txt','r').read()
	   lines = datostext.split('\n')
	   for line in lines:
		  if len(line)>1:
			 self.x, self.y = line.split(",")
			 self.datosx.append(self.x)
			 self.datosy.append(self.y)
	   self.ax1.clear()
	   self.ax1.plot(self.datosx,self.datosy)


	def fungraf(self):
	   self.ani = animation.FuncAnimation(self.fig, 
									  self.animada,   #serias dudas aca  
									  interval=1000)    
	   plt.show() 



h=ini()
raiz=Tk()
raiz.geometry("600x600")

boton=ttk.Button(raiz,text="start",command=h.fungraf)
boton.pack()


raiz.mainloop() 
"""


import matplotlib.pyplot as plt
import numpy as np
import time
import random
import pymysql


siguiente=0
def guardar():
	f = open ('/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/inicio1.txt','w')
	f.write('0')
	f.close()
def handle_close(evt):
		

		print('Closed Figure!')
		global siguiente  #Recordar que con esto se afecta la variable global para no generar dos
		siguiente=1
		print siguiente
		guardar()
def mysql_datos():
    db = pymysql.connect(
         user='TT',
         password='TT',
         host='localhost',
         database='tornasol')
    cursor = db.cursor()
    sql = "select voltaje,corriente,temperatura from sensadoB order by hora desc limit 1"

    resultado=cursor.execute(sql)

    myresult = cursor.fetchall()
    lista=list()
    if resultado >0:
	    for x in myresult:
	      lista=list(x)
	      print(lista,"\n")
    else:
	    lista.append(0)
	    lista.append(0)
	    lista.append(0)
      
    db.close()
    return lista



def mysql_datos_y():
    db = pymysql.connect(
         user='TT',
         password='TT',
         host='localhost',
         database='tornasol')
    cursor = db.cursor()
    sql = "select b.temperatura_max from historial_bateria_panel hbp,bateria b where hbp.id_bateria=b.id_bateria and hbp.activo=1"

    resultado=cursor.execute(sql)

    myresult = cursor.fetchall()
	#lista=0
    if resultado >0:
	    for x in myresult:
	      lista=x[0]
	      print(lista,"\n")
	      
    else:
	    lista=3
      
    db.close()
    
    return lista

leitura =[]
lectura2 =[]
lectura3 = []
fig, ax = plt.subplots()
contador = 0
eixo_x = 40

f = open ('/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/inicio1.txt','w')
f.write('1')
f.close()
while siguiente==0:
	y=mysql_datos_y()
	lista=mysql_datos()
	datostext =lista[0]
	datostext1 = lista[1]
	datostext2 = lista[2]
	#print type(datostext)
	try:
		dados=float(datostext)
		dados2=float(datostext1)
		dados3=float(datostext2)
		y=float(y)
	except Exception as e:
		dados=0
		dados2=0
		dados3=0
		y=80
	
	

	   #firmware deve ter um delay de pelo menos 100ms entre cada envio
	#print dados
	ax.clear()
	ax.set_xlim([0,eixo_x])   #faixa do eixo horizontal
	ax.set_ylim([0,y+10]) # faixa do eixo vertical   
	#leitura.append(random.randint(0,1023))  #teste com numeros aleatorios
	leitura.append(dados)
	lectura2.append(dados2)
	lectura3.append(dados3)

	ax.plot(leitura)
	ax.plot(lectura2)
	ax.plot(lectura3)
	plt.xlabel('Tiempo')
	plt.ylabel('Voltaje/Corriente/Temperatura')
	plt.plot(leitura,marker='.', color='y', label = "Voltaje")
	plt.plot(lectura2,linestyle='--', color='r', label = "Corriente")
	plt.plot(lectura3,linestyle='-', color='b', label = "Temperatura")
	plt.legend()
	
	plt.text(380, 4.5, 'Voltaje Bateria', color='red', fontsize=15)
	fig.canvas.mpl_connect('close_event', handle_close)
	plt.pause(.000000000001)     
	contador = contador + 1
	if (contador > eixo_x):
	   leitura.pop(0)
	   lectura2.pop(0)
	   lectura3.pop(0)
	



"""

import matplotlib
matplotlib.use('TkAgg')
import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from Tkinter import *
import matplotlib.pyplot as plt


def datos_degrafica():

		leitura =[]
		fig, ax = plt.subplots()
		contador = 0
		eixo_x = 500
		while True:

			datostext = open('/home/luis/Documentos/pruebas_python/datos.txt','r').read()
			#print type(datostext)
			try:
				dados=float(datostext)

			except Exception as e:
				dados=0



			   #firmware deve ter um delay de pelo menos 100ms entre cada envio
			print dados
			ax.clear()
			ax.set_xlim([0,eixo_x])   #faixa do eixo horizontal
			ax.set_ylim([0,6]) # faixa do eixo vertical   
			#leitura.append(random.randint(0,1023))  #teste com numeros aleatorios
			leitura.append(dados)  

			ax.plot(leitura)
			plt.pause(.000000000001)     
			contador = contador + 1
			if (contador > eixo_x):
			   leitura.pop(0)

			#datostext.close()



class mclass:
	def __init__(self,  window):
		self.window = window
		self.box = Entry(window)
		self.button = Button (window, text="Aceptar", command=self.plot)
		self.box.pack ()
		self.button.pack()

	def plot (self):


		
	   

		fig = Figure(figsize=(6,6))
		a = fig.add_subplot(111) 
		p= datos_degrafica()
		a.plot(p, range(2 +max(x)),color='blue')
		a.set_title ("Estimation Grid", fontsize=16)
		a.set_ylabel("Y", fontsize=14)
		a.set_xlabel("X", fontsize=14)

		canvas = FigureCanvasTkAgg(fig, master=self.window)
		canvas.get_tk_widget().pack()
		canvas.draw()
		

window= Tk()
start= mclass (window)
window.mainloop()
"""
