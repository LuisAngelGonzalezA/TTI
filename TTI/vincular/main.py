#!/usr/bin/env python
# -*- coding: utf-8 -*-
from tkinter import *
import tkinter as Tk
from tkinter import ttk
import tkinter.font as tkFont
import socket

class MyDialog:
	def __init__(self, parent):
		self.top = Tk.Toplevel(parent)
		self.parent = parent
		self.top.title("Salir")
		self.top.columnconfigure(0, weight=1)
		self.top.rowconfigure(0, weight=1)
		self.top.resizable(False, False)

		Tk.Label(self.top, text="¿Está seguro?").grid(row=0, column=0, columnspan=5,sticky="n")

		self.button1 = Tk.Button(self.top, text="Si, salir de la app.", command=self.salir,bg="green")
		self.button2 = Tk.Button(self.top, text="No, salir de la app.", command=self.minimizar,bg="red")
		self.button1.grid(row=3, column=1, padx=5, pady=5,sticky="n")
		self.button2.grid(row=3, column=2, padx=5, pady=5, sticky="n")
		self.top.transient(master=self.parent)

		# El método grab_set() asegura que no haya eventos 
		# de ratón o teclado que se envíen a otra ventana 
		# diferente a 'self.top'. Se utiliza para 
		# crear una ventana de tipo modal que será 
		# necesario cerrar para poder trabajar con otra
		# diferente. Con ello, también se impide que la 
		# misma ventana se abra varias veces. 
		
		self.top.grab_set()
		self.parent.wait_window(self.top)

	def salir(self):
		global siguiente  #Recordar que con esto se afecta la variable global para no generar dos
		siguiente=1
		#print siguiente
		self.top.destroy()
		self.parent.destroy()

	def minimizar(self):
		self.top.destroy()


class MyApp:
	def __init__(self, parent):
		self.parent = parent
		self.parent.protocol("WM_DELETE_WINDOW", self.on_closing)

	def on_closing(self):
		d = MyDialog(root)
class Ventanas:
	def __init__(self, parent):
			self.parent = parent
			parent.title("Tornasol")
			#parent.iconbitmap('@/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel_tt.xbm');
			nombre_equipo = socket.gethostname()
			direccion_equipo = socket.gethostbyname(nombre_equipo)
			
			s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
			
			s.connect(("8.8.8.8", 80))
			print ("Equipo: {name} \n {ip}".format(name=nombre_equipo,ip=s.getsockname()[0]))
			Letrero=Tk.Label(parent,text="Equipo:\n\n {name} \n\n\n Ip de dispositivo:\n\n{ip}\n\n\n Vincular".format(name=nombre_equipo,ip=s.getsockname()[0]),fg="green",font=("Arial",18))
			



			Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
			


			#B.pack()

			# Titulo de la ventana
			parent.title( "Vincular" )
			parent.minsize(width=550, height=450)
			parent.maxsize(width=500, height=450)
			# Dimensiones de la ventana
			#parent.geometry("700x400"
			#parent.resizable(True, False)
			
			parent.update_idletasks()
			width=550
			heigth=400
			x=(parent.winfo_width()//2)+30+(width//2)
			y=(parent.winfo_height()//2)+30-(heigth//2)
			parent.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
			parent.deiconify()


			parent.mainloop()

		




class cerrar_select:
	def __init__(self, parent):
		self.parent = parent
		self.parent.protocol("WM_DELETE_WINDOW", self.on_closing)

	def on_closing(self):
		print("Se elmino")
		self.parent.destroy()










if __name__ == "__main__":
	
	# Ahora preparamos a la ventana
	root = Tk.Tk()
	app = MyApp(root)
	ven=Ventanas(root)
	
