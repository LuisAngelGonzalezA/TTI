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




def eliminar_panel(self):
	
		consulta="delete from panel_solar where nombre ='{nombre}'".format(nombre=self.panel_eliminado.get())
		print(consulta)
		mysql=mysql_conection.mysql_conexion_tornasol()
		cursor = mysql.cursor()
		resultado=cursor.execute(consulta)
		mysql.commit()
		print(resultado)
		if resultado>0:
			messagebox.showinfo("Exito","Panel Eliminado")
		else:
			messagebox.showinfo("Error","Panel no Eliminado")	
		mysql.close()
		"""
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select nombre from panel")
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
		
		menu = self.panel_select["menu"]
		menu.delete(0, "end")
		for string in lista:
			menu.add_command(label=string,command=lambda value=string: self.panel_select.set(value))
		"""
	
def eliminar_bateria(self):
	print("hola")
	
	
