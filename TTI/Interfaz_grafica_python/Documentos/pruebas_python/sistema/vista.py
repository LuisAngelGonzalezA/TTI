from tkinter import *
import tkinter as Tk
import mysql_conection
from tkinter import ttk
import tkinter.font as tkFont
import vista as vis
import cerrar_ven
import table 
import insert
import update_ventana
from functools import partial

def vista_select_tabla(self):
		self.dialogo = Toplevel(self.parent)
		cerrar_select_dialogo=cerrar_ven.cerrar_select(self.dialogo)
		self.dialogo.transient(master=self.parent)
		Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel2.gif")
		imagen_inicio = Tk.Label(self.dialogo, image=img)
		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		boton_aceptar =Tk.Button(self.dialogo, text='Cerrar',command=self.dialogo.destroy)



		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("desc bateria")
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
		del lista[0]
		del lista[0]
		lista=tuple(lista)
		print(lista)

		tabla_baterias = table.Table(self.dialogo, title="Baterias registradas", headers=lista)
		lista=tuple()
		cursor.execute("select*from bateria")
		for row in cursor:
			lista=list(row)
			del lista[0]
			del lista[0]
			lista=tuple(lista)
			tabla_baterias.add_row(lista)

		cursor.execute("desc panel_solar")
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
		del lista[0]
		del lista[0]
		lista=tuple(lista)
		print(lista)

		tabla_panel = table.Table(self.dialogo, title="Paneles Fotovoltaicos registradas", headers=lista)
		lista=tuple()
		cursor.execute("select*from panel_solar")
		for row in cursor:
			lista=list(row)
			del lista[0]
			del lista[0]
			lista=tuple(lista)
			tabla_panel.add_row(lista)
	
		boton_regresar.pack(side=BOTTOM,padx=10, pady=5)
		tabla_baterias.pack(side=BOTTOM, fill=BOTH, expand=True,padx=10, pady=5)
		tabla_panel.pack(side=BOTTOM, fill=BOTH, expand=True,padx=10, pady=5)
		Letrero.pack(side=LEFT, fill=BOTH, expand=True,padx=10, pady=5)
		imagen_inicio.pack(side=RIGHT, fill=BOTH, expand=True,padx=10, pady=5)
		self.dialogo.minsize(width=380, height=400)
		self.dialogo.maxsize(width=1200, height=850)
		width=500
		heigth=700
		x=(self.dialogo.winfo_width()//2)+30+(width//2)
		y=(self.dialogo.winfo_height()//2)-(heigth//2)
		self.dialogo.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
		self.dialogo.overrideredirect(0)
		

		  # El método grab_set() asegura que no haya eventos 
		  # de ratón o teclado que se envíen a otra ventana 
		  # diferente a 'self.dialogo'. Se utiliza para 
		  # crear una ventana de tipo modal que será 
		  # necesario cerrar para poder trabajar con otra
		  # diferente. Con ello, también se impide que la 
		  # misma ventana se abra varias veces. 
		  
		self.dialogo.grab_set()
		self.parent.wait_window(self.dialogo)
		
def vista_insertar(self):
		self.dialogo = Toplevel(self.parent)
		cerrar_select_dialogo=cerrar_ven.cerrar_select(self.dialogo)
		self.dialogo.transient(master=self.parent)
		Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel.gif")
		action_insert_ventana_bateria = partial(insert.insert_bateria, self.dialogo)
		action_insert_ventana_panel = partial(insert.insert_panel, self.dialogo)
		imagen_inicio = Tk.Label(self.dialogo, image=img)
		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		Boton_PANEL=Tk.Button(self.dialogo, text ="Insertar Panel Fotovoltaicos", command =action_insert_ventana_panel, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		Boton_Baterias=Tk.Button(self.dialogo, text ="Insertar Bateria", command = action_insert_ventana_bateria, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)




		
		Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		Boton_PANEL.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		Boton_Baterias.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		boton_regresar.pack(side=TOP,padx=10, pady=5)
		self.dialogo.minsize(width=380, height=400)
		self.dialogo.maxsize(width=500, height=650)
		width=450
		heigth=500
		x=(self.dialogo.winfo_width()//2)+30+(width//2)
		y=(self.dialogo.winfo_height()//2)-(heigth//2)
		self.dialogo.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
		self.dialogo.overrideredirect(0)
		

		  # El método grab_set() asegura que no haya eventos 
		  # de ratón o teclado que se envíen a otra ventana 
		  # diferente a 'self.dialogo'. Se utiliza para 
		  # crear una ventana de tipo modal que será 
		  # necesario cerrar para poder trabajar con otra
		  # diferente. Con ello, también se impide que la 
		  # misma ventana se abra varias veces. 
		  
		self.dialogo.grab_set()
		self.parent.wait_window(self.dialogo)

def vista_uodate_panel(self):
		self.dialogo = Toplevel(self.parent)
		cerrar_select_dialogo=cerrar_ven.cerrar_select(self.dialogo)
		self.dialogo.transient(master=self.parent)
		Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel.gif")
		action_insert_ventana_bateria = partial(insert.insert_bateria, self.dialogo)
		action_insert_ventana_panel = partial(update_ventana.update_ven, self.dialogo)
		
		imagen_inicio = Tk.Label(self.dialogo, image=img)

		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		Boton_PANEL=Tk.Button(self.dialogo, text ="Actualizar Panel Fotovoltaicos", command =action_insert_ventana_panel, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		Boton_Baterias=Tk.Button(self.dialogo, text ="Actualizar Bateria", command = action_insert_ventana_bateria, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		



		
		Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		Boton_PANEL.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		Boton_Baterias.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		boton_regresar.pack(side=TOP,padx=10, pady=5)
		self.dialogo.minsize(width=380, height=550)
		self.dialogo.maxsize(width=500, height=650)
		width=450
		heigth=550
		x=(self.dialogo.winfo_width()//2)+30+(width//2)
		y=(self.dialogo.winfo_height()//2)-(heigth//2)
		self.dialogo.geometry('{}x{}+{}+{}'.format(width,heigth,x,y))
		self.dialogo.overrideredirect(0)
		

		  # El método grab_set() asegura que no haya eventos 
		  # de ratón o teclado que se envíen a otra ventana 
		  # diferente a 'self.dialogo'. Se utiliza para 
		  # crear una ventana de tipo modal que será 
		  # necesario cerrar para poder trabajar con otra
		  # diferente. Con ello, también se impide que la 
		  # misma ventana se abra varias veces. 
		  
		self.dialogo.grab_set()
		self.parent.wait_window(self.dialogo)
