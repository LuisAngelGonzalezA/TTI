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


		action_cambio = partial(ver_lista, self)
		self.has_memoria.trace('w', action_cambio)

		self.Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/luis/Documentos/pruebas_python/sistema/panel.gif")
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
		has_memo= Tk.OptionMenu(self.dialogo, self.has_memoria,*lista)

		imagen_inicio = Tk.Label(self.dialogo, image=img)

		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		self.nombre = Tk.Label(self.dialogo, text="Nombre del panel:",font="Arial 14",justify=Tk.CENTER) 
		self.nombre_insergrado_entry = Tk.Entry(self.dialogo, textvariable=self.nombre_insergrado,justify=Tk.CENTER) 
		
		Boton_PANEL=Tk.Button(self.dialogo, text ="Insertar Panel Fotovoltaicos", command =action_insert_ventana_panel, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		Boton_Baterias=Tk.Button(self.dialogo, text ="Insertar Bateria", command = action_insert_ventana_bateria, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		Boton_Aceptar=Tk.Button(self.dialogo, text ="Visualizar", command =ver, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		
		self.Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.has_mem.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		has_memo.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.nombre.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.nombre_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		Boton_PANEL.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		Boton_Baterias.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		Boton_Aceptar.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		boton_regresar.pack(side=TOP,padx=10, pady=5)
		self.dialogo.minsize(width=380, height=680)
		self.dialogo.maxsize(width=500, height=680)
		width=450
		heigth=680
		x=(self.dialogo.winfo_width()//2)+30+(width//2)
		y=(self.dialogo.winfo_height()//2)-(heigth//2)
		self.dialogo.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
		#self.update_label()

		self.dialogo.overrideredirect(0)
		

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
	self.has_mem.configure(text = lista)
	self.nombre_insergrado=Tk.StringVar()
	self.nombre_insergrado.set(lista[2])
	self.nombre_insergrado_entry.configure(textvariable=self.nombre_insergrado)
	print(self.nombre_insergrado.get())

	#print(lista)
	#print("--->",self.has_memoria.get())