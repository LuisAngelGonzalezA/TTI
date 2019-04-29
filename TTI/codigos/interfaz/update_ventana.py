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
		self.respaldo=StringVar()

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
		cursor.execute("select nombre from panel_solar where isEliminado=1")
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
		if len(lista) <=0:
			lista.append("No hay paneles para actualizar ")
		db.close()
			
		self.has_mem=Tk.Label(self.dialogo, text="Actualizar Panel:",font="Arial 14",justify=Tk.CENTER) 
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
	consulta="select * from panel_solar where nombre= '{datos}' and isEliminado=1".format(datos=a)
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
	db.close()
	if len(lista) <=0:
			lista.append("No hay paneles para actualizar ")
			
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
	resultado=0
	
	if not self.respaldo.get().strip():
		messagebox.showinfo("Error","Seleccione panel a actualizar")
		
		
	else :
		status=validar(self.nombre_insergrado.get(),self.voltaje_ingresado.get(),self.corriente_ingresado.get())
		if self.nombre_insergrado.get()!=self.respaldo.get() and status==True:
			consulta="select * from panel_solar where nombre ='{nombre}' and isEliminado=1".format(nombre=self.nombre_insergrado.get())
			mysql=mysql_conection.mysql_conexion_tornasol()
			cursor = mysql.cursor()
			resultado=cursor.execute(consulta)
			print(consulta)
	
		if resultado == 0 and status==True:

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
				cursor.execute("select nombre from panel_solar where isEliminado=1")
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
				db.close()
				if len(lista) <=0:
					lista.append("No hay paneles para actualizar ")
			
				menu = self.has_memo["menu"]
				menu.delete(0, "end")
				for string in lista:
					menu.add_command(label=string,command=lambda value=string: self.has_memoria.set(value))
				
				
				
				
				
				#self.dialogo.destroy()
			else:
				messagebox.showinfo("Error","Panel no Actualizado")	
		else:
			if status==True:
				messagebox.showinfo("Error","Panel ya registrado")




def validar(nombre_insergrado,Voltaje_maximo,corriente_maximo):
	var=nombre_insergrado
	var1=Voltaje_maximo
	var2=corriente_maximo
	bandera1=0
	bandera2=0
	status=False
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
		messagebox.showinfo("Error","Nombre muy largo")
	elif bandera1==0 and bandera2==0:
		
		status=True
		
	elif bandera1 == 1:
		messagebox.showinfo("Error","Voltaje no aceptado")

	elif bandera2 == 1:
		messagebox.showinfo("Error","Corriente no aceptado")

	else:
		messagebox.showinfo("Error","Error inesperado")
		
	return status




"""
		______________________________
		|****************************|   
		|******Actualizar Bateria****|
		|****************************|		
		
"""



def update_ven_bateria(self):
		self.dialogo = Toplevel(self)
		cerrar_select_dialogo=cerrar_ven.cerrar_select(self.dialogo)
		self.dialogo.transient(master=self)
		self.has_memoria=StringVar()
		self.nombre_insergrado =StringVar()
		self.voltaje_ingresado =StringVar()
		self.voltaje_minima=StringVar()
		self.corriente_ingresado =StringVar()
		self.num_celdas=StringVar()
		self.temperatura_ingresada=StringVar()
		self.memoria_ingresada=IntVar()
		
		self.respaldo=StringVar()

		action_cambio = partial(ver_lista_bateria, self)
		self.has_memoria.trace('w', action_cambio)
		action_update = partial(update_datos_bateria, self)
		self.Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel.gif")

		ver = partial(ver_lista_bateria, self)
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select nombre from bateria where isEliminado=1")
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
		db.close()
		if len(lista) <=0:
			lista.append("No hay paneles para actualizar ")
			
		self.has_mem=Tk.Label(self.dialogo, text="Actualizar bateria:",font="Arial 14",justify=Tk.CENTER) 
		self.has_memo= Tk.OptionMenu(self.dialogo, self.has_memoria,*lista)

		imagen_inicio = Tk.Label(self.dialogo, image=img)

		
		self.nombre = Tk.Label(self.dialogo, text="Nombre del panel:",font="Arial 14",justify=Tk.CENTER) 
		self.nombre_insergrado_entry = Tk.Entry(self.dialogo, textvariable=self.nombre_insergrado,justify=Tk.CENTER,font="Arial 12") 
		self.nombre_voltaje = Tk.Label(self.dialogo, text="Voltaje Máximo:",font="Arial 14",justify=Tk.CENTER) 
		self.voltaje_insergrado_entry = Tk.Entry(self.dialogo, textvariable=self.voltaje_ingresado,justify=Tk.CENTER,font="Arial 12") 
		
		self.nombre_voltaje_min = Tk.Label(self.dialogo, text="Voltaje Minimo:",font="Arial 14",justify=Tk.CENTER) 
		self.voltaje_insergrado_min_entry = Tk.Entry(self.dialogo, textvariable=self.voltaje_minima,justify=Tk.CENTER,font="Arial 12")
		
		self.nombre_corriente = Tk.Label(self.dialogo, text="Corriente Máximo:",font="Arial 14",justify=Tk.CENTER) 
		self.corriente_insergrado_entry = Tk.Entry(self.dialogo, textvariable=self.corriente_ingresado,justify=Tk.CENTER,font="Arial 12") 
		
		self.numero_de_celdas = Tk.Label(self.dialogo, text="Numero de celdas:",font="Arial 14",justify=Tk.CENTER) 
		self.numero_de_celdas_entry = Tk.Entry(self.dialogo, textvariable=self.num_celdas,justify=Tk.CENTER,font="Arial 12")
		
		self.temperatura = Tk.Label(self.dialogo, text="Temperatura:",font="Arial 14",justify=Tk.CENTER) 
		self.temperatura_entry = Tk.Entry(self.dialogo, textvariable=self.temperatura_ingresada,justify=Tk.CENTER,font="Arial 12")
		
		self.memoria=Tk.Label(self.dialogo, text="Memoria:",font="Arial 14",justify=Tk.CENTER) 
		self.memoria_entry= Spinbox(self.dialogo, from_=0, to=1, wrap=True,textvariable=self.memoria_ingresada, state='readonly',justify=Tk.CENTER)
		
		
		
		boton_aceptar = Tk.Button(self.dialogo, text='Aceptar',command=action_update,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="green")
		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		
		
		self.Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		#imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.has_mem.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.has_memo.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.nombre.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.nombre_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		self.nombre_voltaje.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.voltaje_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.nombre_voltaje_min.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.voltaje_insergrado_min_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		self.nombre_corriente.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.corriente_insergrado_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.numero_de_celdas.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.numero_de_celdas_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		self.temperatura.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.temperatura_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		self.memoria.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.memoria_entry.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)

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


def ver_lista_bateria(self,*args):
	#print("Cambio el valor")
	a=self.has_memoria.get()
	print("Valor actual de Entry :",self.nombre_insergrado_entry.get())
	print("--->",a)
	db =mysql_conection.mysql_conexion_tornasol()
	cursor = db.cursor()
	consulta="select * from bateria where nombre= '{datos}' and isEliminado=1".format(datos=a)
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
	db.close()
	if len(lista) <=0:
			lista.append("No hay paneles para actualizar ")
			
	print(lista)
	#print(lista[2])
	#self.has_mem.configure(text = lista)
	self.nombre_insergrado=Tk.StringVar()
	self.nombre_insergrado.set(lista[2])
	self.respaldo=Tk.StringVar()
	self.respaldo.set(lista[2])
	self.voltaje_ingresado.set(lista[3])
	self.voltaje_minima.set(lista[4])
	self.corriente_ingresado.set(lista[5])
	self.num_celdas.set(lista[6])
	self.temperatura_ingresada.set(lista[7])
	self.memoria_ingresada.set(lista[8])
	
	self.nombre_insergrado_entry.configure(textvariable=self.nombre_insergrado)
	self.voltaje_insergrado_entry.configure(textvariable=self.voltaje_ingresado)
	self.voltaje_insergrado_min_entry.configure(textvariable=self.voltaje_minima)
	self.corriente_insergrado_entry.configure(textvariable=self.corriente_ingresado)
	self.numero_de_celdas_entry.configure(textvariable=self.num_celdas)
	self.temperatura_entry.configure(textvariable=self.temperatura_ingresada)
	self.memoria_entry.configure(textvariable=self.memoria_ingresada)	
	

def update_datos_bateria(self):
	resultado=0
	
	if not self.respaldo.get().strip():
		messagebox.showinfo("Error","Seleccione panel a actualizar")
		
		
	else :
		status=validar_bateria(self.nombre_insergrado.get(),self.voltaje_ingresado.get(),self.voltaje_minima.get(),self.corriente_ingresado.get(),self.num_celdas.get(),self.temperatura_ingresada.get(),self.memoria_ingresada.get())
		if self.nombre_insergrado.get()!=self.respaldo.get() and status==True:
			consulta="select * from bateria where nombre ='{nombre}' and isEliminado=1".format(nombre=self.nombre_insergrado.get())
			mysql=mysql_conection.mysql_conexion_tornasol()
			cursor = mysql.cursor()
			resultado=cursor.execute(consulta)
			print(consulta)
	
		if resultado == 0 and status==True:

			consulta="update bateria set nombre ='{nombre}',voltaje_max={voltaje},voltaje_min={vol_min},corriente={corriente},nu_celdas={celd},temperatura_max={tm},hasMemoria={hm} where nombre = '{rempazado}'".format(nombre=self.nombre_insergrado_entry.get(),voltaje=self.voltaje_ingresado.get(),vol_min=self.voltaje_insergrado_min_entry.get(),corriente=self.corriente_insergrado_entry.get(),celd=self.num_celdas.get(),tm=self.temperatura_ingresada.get(),hm=self.memoria_ingresada.get(),rempazado=self.respaldo.get())
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
				self.voltaje_minima.set("")
				self.corriente_ingresado.set("")
				self.num_celdas.set("")
				self.temperatura_ingresada.set("")
				self.memoria_ingresada.set("")
				self.nombre_insergrado_entry.configure(textvariable=self.nombre_insergrado)
				self.voltaje_insergrado_entry.configure(textvariable=self.voltaje_ingresado)
				self.corriente_insergrado_entry.configure(textvariable=self.corriente_ingresado)
				
				
				
				db =mysql_conection.mysql_conexion_tornasol()
				cursor = db.cursor()
				cursor.execute("select nombre from bateria where isEliminado=1")
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
				db.close()
				if len(lista) <=0:
						lista.append("No hay paneles para actualizar ")
			
				menu = self.has_memo["menu"]
				menu.delete(0, "end")
				for string in lista:
					menu.add_command(label=string,command=lambda value=string: self.has_memoria.set(value))
				
				
				
				
				
				#self.dialogo.destroy()
			else:
				messagebox.showinfo("Error","Panel no Actualizado")	
		else:
			if status==True:
				messagebox.showinfo("Error","Panel ya registrado")




def validar_bateria(nombre_insergrado,voltaje_ingresado,voltaje_minimo,corriente_ingresado,num_celdas,temperatura_ingresada,memoria_ingresada):
	status=False
	var=nombre_insergrado
	var1=voltaje_ingresado
	var2=voltaje_minimo
	var3=corriente_ingresado
	var4=num_celdas
	var5=temperatura_ingresada
	var6=memoria_ingresada
	

	bandera1=0
	bandera2=0
	bandera3=0
	bandera4=0
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
		var5=float(var5)
		bandera5=0
	except Exception as e:
		bandera4=1

	try:
		var6=int(var6)
		bandera6=0
	except Exception as e:
		bandera6=1



	if len(var) == 0:
		messagebox.showinfo("Error","Ingrese nombre")
	elif len(var)>45:
		messagebox.showinfo("Error","Nombre muy grande")
	elif bandera1==0 and bandera2==0 and bandera3==0 and bandera4==0 and bandera5==0 and bandera6==0:
		status=True
	elif bandera1 == 1:
		messagebox.showinfo("Error","Voltaje no aceptado")

	elif bandera2 == 1:
		messagebox.showinfo("Error","Corriente no aceptado")
	elif bandera3 == 1:
		messagebox.showinfo("Error","Numero de celdas no aceptado")
	elif bandera4 == 1:
		messagebox.showinfo("Error","Temperatura no aceptado")
	elif bandera5 == 1:
		messagebox.showinfo("Error","Memoria no aceptado")

	else:
		messagebox.showinfo("Error","Error inesperado")

	return status



