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


def update_ven(self):
		self.dialogo = Toplevel(self)
		cerrar_select_dialogo=cerrar_ven.cerrar_select(self.dialogo)
		self.dialogo.transient(master=self)
		self.has_memoria=StringVar()
		self.nombre_insergrado =StringVar()
		self.voltaje_ingresado =StringVar()
		self.corriente_ingresado =StringVar()
		self.respaldo=StringVar

		action_cambio = partial(ver_lista, self)
		self.has_memoria.trace('w', action_cambio)
		action_update = partial(update_datos_panel, self)
		self.Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel.gif")
		action_insert_ventana_bateria = partial(insert.insert_bateria, self.dialogo)
		action_insert_ventana_panel = partial(insert.insert_panel, self.dialogo)
		ver = partial(ver_lista, self)
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select nombre from panel_solar")
		print("--->",type(cursor))
		print("\n\n")
		lista=tuple()
		for row in cursor:
		    lista=list(lista)
		    lista.append(row[0])
		    lista=tuple(lista)
		    #lista.extend(row[0])
		    #print(row[0])
		lista=list(lista)
		self.has_mem=Tk.Label(self.dialogo, text="Memoria de bateria:",font="Arial 14",justify=Tk.CENTER) 
		self.has_memo= Tk.OptionMenu(self.dialogo, self.has_memoria,*lista)

		imagen_inicio = Tk.Label(self.dialogo, image=img)

		
		self.nombre = Tk.Label(self.dialogo, text="Nombre del panel:",font="Arial 14",justify=Tk.CENTER) 
		self.nombre_insergrado_entry = Tk.Entry(self.dialogo, textvariable=self.nombre_insergrado,justify=Tk.CENTER,font="Arial 12") 
		self.nombre_voltaje = Tk.Label(self.dialogo, text="Voltaje Máximo:",font="Arial 14",justify=Tk.CENTER) 
		self.voltaje_insergrado_entry = Tk.Entry(self.dialogo, textvariable=self.voltaje_ingresado,justify=Tk.CENTER,font="Arial 12") 
		self.nombre_corriente = Tk.Label(self.dialogo, text="Corriente Máximo:",font="Arial 14",justify=Tk.CENTER) 
		self.corriente_insergrado_entry = Tk.Entry(self.dialogo, textvariable=self.corriente_ingresado,justify=Tk.CENTER,font="Arial 12") 
		boton_aceptar = Tk.Button(self.dialogo, text='Aceptar',command=action_update,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="green")
		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		
		self.Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.has_mem.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.has_memo.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.nombre.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.nombre_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		self.nombre_voltaje.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.voltaje_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.nombre_corriente.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.corriente_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		boton_aceptar.pack(side=LEFT,padx=10, pady=5)
		boton_regresar.pack(side=RIGHT,padx=10, pady=5)
		self.dialogo.minsize(width=380, height=680)
		self.dialogo.maxsize(width=500, height=680)
		width=450
		heigth=680
		x=(self.dialogo.winfo_width()//2)+30+(width//2)
		y=(self.dialogo.winfo_height()//2)-(heigth//2)
		self.dialogo.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
		#self.update_label()

		#
		elf.dialogo.overrideredirect(0)
		

		  # El método grab_set() asegura que no haya eventos 
		  # de ratón o teclado que se envíen a otra ventana 
		  # diferente a 'self.dialogo'. Se utiliza para 
		  # crear una ventana de tipo modal que será 
		  # necesario cerrar para poder trabajar con otra
		  # diferente. Con ello, también se impide que la 
		  # misma ventana se abra varias veces. 
		  
		self.dialogo.grab_set()
		self.wait_window(self.dialogo)


def ver_lista(self,*args):
	#print("Cambio el valor")
	a=self.has_memoria.get()
	print("Valor actual de Entry :",self.nombre_insergrado_entry.get())
	print("--->",a)
	db =mysql_conection.mysql_conexion_tornasol()
	cursor = db.cursor()
	consulta="select * from panel_solar where nombre= '{datos}'".format(datos=a)
	print(consulta)
	cursor.execute(consulta)
	print("--->",type(cursor))
	print("\n\n")
	lista=tuple()
	for row in cursor:
	    lista=list(lista)
	    lista=row
	    #lista.append(row[0])
	    lista=tuple(lista)
	    #lista.extend(row[0])
	    #print(row[0])
	lista=list(lista)
	print(lista)
	print(lista[2])
	#self.has_mem.configure(text = lista)
	self.nombre_insergrado=Tk.StringVar()
	self.nombre_insergrado.set(lista[2])
	self.respaldo=Tk.StringVar()
	self.respaldo.set(lista[2])
	self.voltaje_ingresado.set(lista[3])
	self.corriente_ingresado.set(lista[4])
	
	self.nombre_insergrado_entry.configure(textvariable=self.nombre_insergrado)
	self.voltaje_insergrado_entry.configure(textvariable=self.voltaje_ingresado)
	self.corriente_insergrado_entry.configure(textvariable=self.corriente_ingresado)
	

def update_datos_panel(self):
	
	consulta="select * from panel_solar where nombre ='{nombre}'".format(nombre=self.nombre_insergrado.get())
	print(consulta)
	mysql=mysql_conection.mysql_conexion_tornasol()
	cursor = mysql.cursor()
	resultado=cursor.execute(consulta)
	if resultado == 0:

		consulta="update panel_solar set nombre ='{nombre}',voltaje_max={voltaje},corriente_max={corriente} where nombre = '{rempazado}'".format(nombre=self.nombre_insergrado_entry.get(),voltaje=self.voltaje_ingresado.get(),corriente=self.corriente_insergrado_entry.get(),rempazado=self.respaldo.get())
		print(consulta)
		mysql=mysql_conection.mysql_conexion_tornasol()
		cursor = mysql.cursor()
		resultado=cursor.execute(consulta)
		mysql.commit()
		print(resultado)
		if resultado>0:
			messagebox.showinfo("Exito","Panel Actualizado")
			self.nombre_insergrado=Tk.StringVar()
			self.nombre_insergrado.set("")
			self.respaldo=Tk.StringVar()
			self.respaldo.set("")
			self.voltaje_ingresado.set("")
			self.corriente_ingresado.set("")
			
			self.nombre_insergrado_entry.configure(textvariable=self.nombre_insergrado)
			self.voltaje_insergrado_entry.configure(textvariable=self.voltaje_ingresado)
			self.corriente_insergrado_entry.configure(textvariable=self.corriente_ingresado)
			
			
			
			db =mysql_conection.mysql_conexion_tornasol()
			cursor = db.cursor()
			cursor.execute("select nombre from panel_solar")
			print("--->",type(cursor))
			print("\n\n")
			lista=tuple()
			for row in cursor:
				lista=list(lista)
				lista.append(row[0])
				lista=tuple(lista)
				#lista.extend(row[0])
				#print(row[0])
			lista=list(lista)
			
			menu = self.has_memo["menu"]
			menu.delete(0, "end")
			for string in lista:
				menu.add_command(label=string,command=lambda value=string: self.has_memoria.set(value))
			
			
			
			
			
			#self.dialogo.destroy()
		else:
			messagebox.showinfo("Error","Panel no Actualizado")	
	else:
		messagebox.showinfo("Error","Panel ya registrado")




