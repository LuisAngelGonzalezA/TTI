#!/usr/bin/env python
# -*- coding: utf-8 -*-
from tkinter import *
import tkinter as Tk
import mysql_conection
from tkinter import ttk
import tkinter.font as tkFont
import vista as vis
import cerrar_ven
import insert
from functools import partial
from tkinter import messagebox


def insert_panel(self):
		self.ventana_insert_panel = Toplevel(self)
		cerrar_select_ventana_insert_panel=cerrar_ven.cerrar_select(self.ventana_insert_panel)
		self.ventana_insert_panel.transient(master=self)
		self.nombre_insergrado =	 StringVar()
		self.Voltaje_maximo = StringVar()
		self.corriente_maximo = StringVar()
		action_with_arg = partial(insert.nombre_tener, self)

		Letrero=Tk.Label(self.ventana_insert_panel,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel2.gif")
		imagen_inicio = Tk.Label(self.ventana_insert_panel, image=img)
		nombre = Tk.Label(self.ventana_insert_panel, text="Nombre del panel:",font="Arial 14",justify=Tk.CENTER) 
		nombre_insergrado_entry = Tk.Entry(self.ventana_insert_panel, textvariable=self.nombre_insergrado,justify=Tk.CENTER) 
		Voltaje = Tk.Label(self.ventana_insert_panel, text="Voltaje Máximo(v):",font="Arial 14",justify=Tk.CENTER) 
		voltaje_maximo = Tk.Entry(self.ventana_insert_panel, textvariable=self.Voltaje_maximo,justify=Tk.CENTER)
		corriente = Tk.Label(self.ventana_insert_panel, text="Corriente Máximo(mA):",font="Arial 14",justify=Tk.CENTER) 
		corriente_maxima = Tk.Entry(self.ventana_insert_panel, textvariable=self.corriente_maximo,justify=Tk.CENTER)
		boton_regresar = Tk.Button(self.ventana_insert_panel, text='Regresar',command=self.ventana_insert_panel.destroy,relief=Tk.SOLID,font="Arial 12",bd=4,width=20, height=1,activebackground="red")
		boton_Aceptar = Tk.Button(self.ventana_insert_panel, text='Aceptar',command=action_with_arg,relief=Tk.SOLID,font="Arial 12",bd=4,width=20, height=1,activebackground="green")



		Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		#imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		nombre.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		nombre_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		Voltaje.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		voltaje_maximo.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		corriente.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		corriente_maxima.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		boton_Aceptar.pack(side=LEFT,padx=10, pady=5)
		boton_regresar.pack(side=RIGHT,padx=10, pady=5)



		self.ventana_insert_panel.minsize(width=460, height=350)
		self.ventana_insert_panel.maxsize(width=460, height=350)
		width=460
		heigth=350
		x=(self.ventana_insert_panel.winfo_width()//2)+100+(width//2)
		y=(self.ventana_insert_panel.winfo_height()//2)-(heigth//2)
		self.ventana_insert_panel.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
		self.ventana_insert_panel.overrideredirect(0)
		

		  # El método grab_set() asegura que no haya eventos 
		  # de ratón o teclado que se envíen a otra ventana 
		  # diferente a 'self.ventana_insert_panel'. Se utiliza para 
		  # crear una ventana de tipo modal que será 
		  # necesario cerrar para poder trabajar con otra
		  # diferente. Con ello, también se impide que la 
		  # misma ventana se abra varias veces. 
		  
		self.ventana_insert_panel.grab_set()
		self.wait_window(self.ventana_insert_panel)

def nombre_tener(self):

	var=self.nombre_insergrado.get()
	var1=self.Voltaje_maximo.get()
	var2=self.corriente_maximo.get()
	bandera1=0
	bandera2=0
	try:
		var1=float(var1)
		bandera1=0
	except Exception as e:
		bandera1=1

	try:
		var1=float(var2)
		bandera2=0
	except Exception as e:
		bandera2=1


	if len(var) == 0:
		messagebox.showinfo("Error","Ingrese nombre")
	elif len(var)>45:
		messagebox.showinfo("Error","Nombre excede tamaño")
	elif bandera1==0 and bandera2==0:
		
		consulta="select * from panel_solar where nombre ='{nombre}' and isEliminado=0".format(nombre=var)
		print(consulta)
		mysql=mysql_conection.mysql_conexion_tornasol()
		cursor = mysql.cursor()
		resultado=cursor.execute(consulta)
		if resultado == 0:
		
			consulta="insert into panel_solar values(null,1,'{nombre}',{voltaje},{corriente},0)".format(nombre=var,voltaje=var1,corriente=var2)
			print(consulta)
			mysql=mysql_conection.mysql_conexion_tornasol()
			cursor = mysql.cursor()
			resultado=cursor.execute(consulta)
			mysql.commit()
			print(resultado)
			if resultado>0:
				messagebox.showinfo("Exito","Panel registrado")
			else:
				messagebox.showinfo("Error","Panel no registrado")	
		else:
			messagebox.showinfo("Error","Panel ya registrado")	

		mysql.close()
	elif bandera1 == 1:
		messagebox.showinfo("Error","Voltaje no aceptado")

	elif bandera2 == 1:
		messagebox.showinfo("Error","Corriente no aceptado")

	else:
		messagebox.showinfo("Error","Error inesperado")









def insert_bateria(self):
		self.ventana_insert_panel = Toplevel(self)
		cerrar_select_ventana_insert_panel=cerrar_ven.cerrar_select(self.ventana_insert_panel)
		self.ventana_insert_panel.transient(master=self)
		self.nombre_insergrado =	 StringVar()
		self.Voltaje_maximo = StringVar()
		self.voltaje_min=StringVar()
		self.corriente_maximo = StringVar()
		self.numero_de_celdas = StringVar()
		self.temperatura = StringVar()
		self.has_memoria = IntVar()
		action_with_arg = partial(insert.nombre_tener_bateria, self)

		Letrero=Tk.Label(self.ventana_insert_panel,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel2.gif")
		imagen_inicio = Tk.Label(self.ventana_insert_panel, image=img)
		nombre = Tk.Label(self.ventana_insert_panel, text="Nombre de la Batería:",font="Arial 14",justify=Tk.CENTER) 
		nombre_insergrado_entry = Tk.Entry(self.ventana_insert_panel, textvariable=self.nombre_insergrado,justify=Tk.CENTER) 
		Voltaje = Tk.Label(self.ventana_insert_panel, text="Voltaje Máximo(V):",font="Arial 14",justify=Tk.CENTER) 
		voltaje_maximo = Tk.Entry(self.ventana_insert_panel, textvariable=self.Voltaje_maximo,justify=Tk.CENTER)
		Voltaje_m = Tk.Label(self.ventana_insert_panel, text="Voltaje Minimo(V):",font="Arial 14",justify=Tk.CENTER) 
		voltaje_minimo = Tk.Entry(self.ventana_insert_panel, textvariable=self.voltaje_min,justify=Tk.CENTER)
		corriente = Tk.Label(self.ventana_insert_panel, text="Corriente Máximo(mA):",font="Arial 14",justify=Tk.CENTER) 
		corriente_maxima = Tk.Entry(self.ventana_insert_panel, textvariable=self.corriente_maximo,justify=Tk.CENTER)
		num_celd=Tk.Label(self.ventana_insert_panel, text="Número de celdas:",font="Arial 14",justify=Tk.CENTER) 
		num_celda=Tk.Entry(self.ventana_insert_panel, textvariable=self.numero_de_celdas,justify=Tk.CENTER)
		tem=Tk.Label(self.ventana_insert_panel, text="Temperatura Máxima (°C):",font="Arial 14",justify=Tk.CENTER) 
		tem_max=Tk.Entry(self.ventana_insert_panel, textvariable=self.temperatura,justify=Tk.CENTER)
		has_mem=Tk.Label(self.ventana_insert_panel, text="Memoria de bateria:",font="Arial 14",justify=Tk.CENTER) 
		has_memo= Spinbox(self.ventana_insert_panel, from_=0, to=1, wrap=True,textvariable=self.has_memoria, state='readonly',justify=Tk.CENTER)

		boton_regresar = Tk.Button(self.ventana_insert_panel, text='Regresar',command=self.ventana_insert_panel.destroy,relief=Tk.SOLID,font="Arial 12",bd=4,width=20, height=1,activebackground="red")
		boton_Aceptar = Tk.Button(self.ventana_insert_panel, text='Aceptar',command=action_with_arg,relief=Tk.SOLID,font="Arial 12",bd=4,width=20, height=1,activebackground="green")



		Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		#imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		nombre.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		nombre_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		Voltaje.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		voltaje_maximo.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		Voltaje_m.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		voltaje_minimo.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		corriente.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		corriente_maxima.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		num_celd.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		num_celda.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		tem.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		tem_max.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		has_mem.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		has_memo.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)


		boton_Aceptar.pack(side=LEFT,padx=10, pady=5)
		boton_regresar.pack(side=RIGHT,padx=10, pady=5)



		self.ventana_insert_panel.minsize(width=460, height=550)
		self.ventana_insert_panel.maxsize(width=460, height=550)
		width=460
		heigth=550
		x=(self.ventana_insert_panel.winfo_width()//2)+100+(width//2)
		y=(self.ventana_insert_panel.winfo_height()//2)-(heigth//2)
		self.ventana_insert_panel.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
		self.ventana_insert_panel.overrideredirect(0)
		

		  # El método grab_set() asegura que no haya eventos 
		  # de ratón o teclado que se envíen a otra ventana 
		  # diferente a 'self.ventana_insert_panel'. Se utiliza para 
		  # crear una ventana de tipo modal que será 
		  # necesario cerrar para poder trabajar con otra
		  # diferente. Con ello, también se impide que la 
		  # misma ventana se abra varias veces. 
		  
		self.ventana_insert_panel.grab_set()
		self.wait_window(self.ventana_insert_panel)

def nombre_tener_bateria(self):

	var=self.nombre_insergrado.get()
	var1=self.Voltaje_maximo.get()
	var2=self.voltaje_min.get()
	var3=self.corriente_maximo.get()
	var4=self.numero_de_celdas.get()
	var5=0
	var6=0
	

	bandera1=0
	bandera2=0
	bandera3=0
	bandera4=0
	bandera5=0
	bandera6=0
	try:
		var1=float(var1)
		bandera1=0
	except Exception as e:
		bandera1=1

	try:
		var2=float(var2)
		bandera2=0
	except Exception as e:
		bandera2=1

	try:
		var3=float(var3)
		bandera3=0
	except Exception as e:
		bandera3=1
	try:
		var4=float(var4)
		bandera4=0
	except Exception as e:
		bandera4=1

	try:
		var5=float(self.temperatura.get())
		bandera5=0
	except Exception as e:
		bandera5=1

	try:
		var6=int(self.has_memoria.get())
		bandera6=0
	except Exception as e:
		bandera6=1



	if len(var) == 0:
		messagebox.showinfo("Error","Ingrese nombre")
	if len(var) > 45:
		messagebox.showinfo("Error","Nombre excede el tamaño")
	elif bandera1==0 and bandera2==0 and bandera3==0 and bandera4==0 and bandera5==0 and bandera6==0:
		
		consulta="select * from bateria where nombre ='{nombre}' and isEliminado=0".format(nombre=var)
		print(consulta)
		mysql=mysql_conection.mysql_conexion_tornasol()
		cursor = mysql.cursor()
		resultado=cursor.execute(consulta)
		if resultado == 0:
			consulta="insert into bateria values(null,1,'{nombre}',{voltaje},{vol_min},{corriente},{nu_celdas},{temperatura},{has_mem},0)".format(nombre=var,voltaje=var1,vol_min=var2,corriente=var3,nu_celdas=var4,temperatura=var5,has_mem=var6)
			print(consulta)
			mysql=mysql_conection.mysql_conexion_tornasol()
			cursor = mysql.cursor()
			resultado=cursor.execute(consulta)
			mysql.commit()
			print(resultado)
			if resultado>0:
				messagebox.showinfo("Exito","Batería registrado")
			else:
				messagebox.showinfo("Error","Batería no registrado")	
		else:
			messagebox.showinfo("Error","Batería ya registrado")	
		mysql.close()
	elif bandera1 == 1:
		messagebox.showinfo("Error","Voltaje no aceptado")

	elif bandera2 == 1:
		messagebox.showinfo("Error","Voltaje no aceptado")
	elif bandera3 == 1:
		messagebox.showinfo("Error","Corriente no aceptado")
	elif bandera4 == 1:
		messagebox.showinfo("Error","Numero de celdas no aceptado")
	elif bandera5 == 1:
		messagebox.showinfo("Error","Temperatura no aceptado")
	elif bandera6 == 1:
		messagebox.showinfo("Error","Memoria no aceptado")

	else:
		messagebox.showinfo("Error","Error inesperado")
