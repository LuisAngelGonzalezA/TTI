#!/usr/bin/env python
# -*- coding: utf-8 -*-

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import Tkinter as Tk
import matplotlib.pyplot as plt
import threading
import tkMessageBox
import time
import sys
import os
#os.system('date')


siguiente=0;
graficar_panel=0
inicio_bandera=0
def guardar():
	f = open ('/home/luis/Documentos/pruebas_python/inicio.txt','w')
	f.write('0')
	f.close()

def helloCallBack():
	f = open ('/home/luis/Documentos/pruebas_python/inicio.txt','r')
	mensaje = f.read()
	print(mensaje)
	f.close()
	
	
	if inicio_bandera==0:
		guardar();
		mensaje='0'

	if mensaje=='0':

		global inicio_bandera
		inicio_bandera=1
		t = threading.Thread(target=ventana_grafica)
		t.start()
		
	else:
		tkMessageBox.showinfo("Precaucion", "En ejecucion grafica")
	



def ventana_grafica():
	os.system('python /home/luis/Documentos/pruebas_python/grafica.py')
   
def handle_close(evt):
		print('Closed Figure!')
		global siguiente  #Recordar que con esto se afecta la variable global para no generar dos
		siguiente=1
		print siguiente
		global graficar_panel
		graficar_panel=0
		
		
		 
def datos_degrafica():
			
			print "Iniciando una nueva ventana"
			leitura =[]
			fig, ax = plt.subplots()
			contador = 0
			eixo_x = 1024
			#fig = plt.figure()
			

			while siguiente==0:

				datostext = open('/home/luis/Documentos/pruebas_python/datos.txt','r').read()
				#print type(datostext)
				try:
					dados=float(datostext)

				except Exception as e:
					dados=0



				   #firmware deve ter um delay de pelo menos 100ms entre cada envio
				print dados
				ax.clear()
				
				plt.isinteractive()
				ax.set_xlim([0,eixo_x])   #faixa do eixo horizontal
				ax.set_ylim([0,6]) # faixa do eixo vertical   
				#leitura.append(random.randint(0,1023))  #teste com numeros aleatorios
				leitura.append(dados)  

				ax.plot(leitura)
				plt.xlabel('Muestras')
				plt.ylabel('Voltaje')
				plt.plot(leitura,marker='.', color='y', label = "Voltaje")
				plt.legend()
				fig.canvas.mpl_connect('close_event', handle_close)
				plt.text(380, 6.5, 'Voltaje Panel', color='red', fontsize=15)
				plt.pause(.000000000001)     
				contador = contador + 1
				if (contador > eixo_x):
				   leitura.pop(0)
				print "vale =",siguiente,"\n"
			plt.show(block = False)
			try:
				plt.close(1)
				time.sleep(1)
				print "Se cerró correctamente el plot"
			except Exception as e:
				print "Error al cierre"
			
			


class grafica_nueva:
	"""docstring for grafica_nueva"""
	def __init__(self, master):
		global t
		t = threading.Thread(target=self.datos_degrafica)
		t.start()
		
	def datos_degrafica(self):
			
			
			leitura =[]
			fig, ax = plt.subplots()
			contador = 0
			eixo_x = 1024
			#fig = plt.figure()
			

			while siguiente==0:

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
				plt.xlabel('Muestras')
				plt.ylabel('Voltaje')
				plt.plot(leitura,marker='.', color='y', label = "Voltaje")
				plt.legend()
				fig.canvas.mpl_connect('close_event', handle_close)
				plt.text(380, 6.5, 'Voltaje Panel', color='red', fontsize=15)
				plt.pause(.000000000001)     
				contador = contador + 1
				if (contador > eixo_x):
				   leitura.pop(0)
				print "vale =",siguiente,"\n"

	

	

			#datostext.close()
class MyDialog:
	def __init__(self, master):
		self.top = Tk.Toplevel(master)
		self.master = master
		self.top.title("Salir")
		self.top.columnconfigure(0, weight=1)
		self.top.rowconfigure(0, weight=1)
		self.top.resizable(False, False)

		Tk.Label(self.top, text="¿Está seguro?").grid(row=0, column=0, columnspan=5,sticky="n")

		self.button1 = Tk.Button(self.top, text="Si, salir de la app.", command=self.salir,bg="green")
		self.button2 = Tk.Button(self.top, text="No, salir de la app.", command=self.minimizar,bg="red")
		self.button1.grid(row=3, column=1, padx=5, pady=5,sticky="n")
		self.button2.grid(row=3, column=2, padx=5, pady=5, sticky="n")
		self.top.transient(master=self.master)

		# El método grab_set() asegura que no haya eventos 
		# de ratón o teclado que se envíen a otra ventana 
		# diferente a 'self.top'. Se utiliza para 
		# crear una ventana de tipo modal que será 
		# necesario cerrar para poder trabajar con otra
		# diferente. Con ello, también se impide que la 
		# misma ventana se abra varias veces. 
		
		self.top.grab_set()
		self.master.wait_window(self.top)

	def salir(self):
		global siguiente  #Recordar que con esto se afecta la variable global para no generar dos
		siguiente=1
		print siguiente
		self.top.destroy()
		self.master.destroy()

	def minimizar(self):
		self.top.destroy()
		#self.master.iconify()
# Declaramos la clase "Ventana"
class Ventana():
	def __init__(self, master):
		
		
		self.master = master
		
		self.master.protocol("WM_DELETE_WINDOW", self.on_closing)

   
	def on_closing(self):
		d = MyDialog(root)
		#self.master.wait_window(d.top)
		

 

if __name__ == '__main__':
	global t
	t = threading.Thread(target=datos_degrafica)
	# Ahora preparamos a la ventana
	root = Tk.Tk()
	app = Ventana(root)
	root.columnconfigure(0, weight=1)
	root.rowconfigure(0, weight=1)
	root.columnconfigure(1, weight=1)
	root.rowconfigure(1, weight=1)
	root.columnconfigure(2, weight=1)
	root.rowconfigure(2, weight=1)
	root.columnconfigure(3, weight=1)
	root.rowconfigure(4, weight=1)
	
	label=Tk.Label(root, text="Tornasol",width=10, height=5,fg="green",font=("Arial",18)).grid(row=0, column=0, columnspan=3,sticky="n")
 
	Tk.Button(root, text ="Graficar Voltaje de Panel raro", command = helloCallBack, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=1).grid(row=1, column=1,sticky="n")
	Tk.Button(root, text ="Graficar Voltaje de Panel", command = helloCallBack, background="CadetBlue",relief=Tk.FLAT).grid(row=4, column=0,sticky="n")
	#B.pack()

	# Titulo de la ventana
	root.title( "Tornasol" )
  	root.minsize(width=200, height=200)
	root.maxsize(width=400, height=400)
	# Dimensiones de la ventana
	#root.geometry("700x400"
	#root.resizable(False, False,True)
	root.update()
	root.deiconify()
	root.mainloop()