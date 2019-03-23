#!/usr/bin/env python
# -*- coding: utf-8 -*-
from tkinter import *
import tkinter as Tk
import MySQLdb
from tkinter import ttk
import tkinter.font as tkFont
import vista as vis
import update_ventana
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
			parent.iconbitmap('@/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel_tt.xbm');
			Letrero=Tk.Label(parent,text="Tornasol",fg="green",font=("Arial",18))
			img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel.gif")
			imagen_inicio = Tk.Label(parent, image=img)


			Boton_select=Tk.Button(parent, text ="Ver paneles y baterias", command = self.ventana_select, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
			Boton_insert=Tk.Button(parent, text ="Insertar paneles y baterias", command = self.ventana_insert, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
			Boton_update=Tk.Button(parent, text ="Actualizar paneles y baterias", command =self.ventana_update, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
			Boton_delete=Tk.Button(parent, text ="Eliminar paneles y baterias", command = self.ventana_delete, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
			Boton_graficas=Tk.Button(parent, text ="Grafica de paneles y baterias", command =self.grafica_vista , activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
			Boton_usar=Tk.Button(parent, text ="Usar paneles y baterias", command = self.usar_panel, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
			
			Boton_salir=Tk.Button(parent, text ="Salir", command = quit,fg="green",relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")





			Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
			imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
			Boton_select.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
			Boton_insert.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
			Boton_update.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
			Boton_delete.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
			Boton_graficas.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
			Boton_usar.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
			Boton_salir.pack(side=RIGHT,padx=5, pady=5)


			#B.pack()

			# Titulo de la ventana
			parent.title( "Tornasol" )
			parent.minsize(width=260, height=650)
			parent.maxsize(width=600, height=650)
			# Dimensiones de la ventana
			#parent.geometry("700x400"
			#parent.resizable(True, False)
			
			parent.update_idletasks()
			width=500
			heigth=700
			x=(parent.winfo_width()//2)+30+(width//2)
			y=(parent.winfo_height()//2)+30-(heigth//2)
			parent.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
			parent.deiconify()


			parent.mainloop()

	def ventana_select(self):
		vis.vista_select_tabla(self)


	def ventana_insert(self):
		vis.vista_insertar(self)

	def ventana_update(self):
		vis.vista_uodate_panel(self)

	def grafica_vista(self):
		vis.vista_gfrafica(self)
		
	def ventana_delete(self):
		vis.vista_eliminar(self)
		
	def usar_panel(self):
		vis.usar_panel_bateria(self)
		




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
	
