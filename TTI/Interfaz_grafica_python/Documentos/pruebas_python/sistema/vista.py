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
import mostrar_grafica
import eliminar
from functools import partial
from tkinter import messagebox


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
		del lista[6]
		del lista[6]
		lista=tuple(lista)
		print(lista)

		tabla_baterias = table.Table(self.dialogo, title="Baterias registradas", headers=lista)
		lista=tuple()
		cursor.execute("select*from bateria where isEliminado=0")
		for row in cursor:
			lista=list(row)
			del lista[0]
			del lista[0]
			del lista[6]
			del lista[6]
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
		del lista[3]
		lista=tuple(lista)
		print(lista)

		tabla_panel = table.Table(self.dialogo, title="Paneles Fotovoltaicos registradas", headers=lista)
		lista=tuple()
		cursor.execute("select*from panel_solar where isEliminado=0")
		for row in cursor:
			lista=list(row)
			del lista[0]
			del lista[0]
			del lista[3]
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
		action_insert_ventana_bateria = partial(update_ventana.update_ven_bateria, self.dialogo)
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





def vista_gfrafica(self):
	
	
		self.dialogo = Toplevel(self.parent)
		cerrar_select_dialogo=cerrar_ven.cerrar_select(self.dialogo)
		self.dialogo.transient(master=self.parent)
		Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel.gif")
		action_insert_ventana_bateria = partial(update_ventana.update_ven_bateria, self.dialogo)
		action_insert_ventana_panel = partial(update_ventana.update_ven, self.dialogo)
		
		imagen_inicio = Tk.Label(self.dialogo, image=img)

		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		Boton_PANEL=Tk.Button(self.dialogo, text ="Gráfica de Panel", command =mostrar_grafica.panel, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		Boton_Baterias=Tk.Button(self.dialogo, text ="Gráficar de Bateria", command = mostrar_grafica.bateria, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		#Boton_Baterias_descarga=Tk.Button(self.dialogo, text ="Gráficar de Bateria descarga", command = action_insert_ventana_bateria, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)



		
		Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		Boton_PANEL.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		Boton_Baterias.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
		Boton_Baterias_descarga.pack(side=TOP, fill=BOTH, expand=True,padx=5, pady=5)
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






def vista_eliminar(self):
	
	
		self.dialogo = Toplevel(self.parent)
		self.panel_eliminado=StringVar()
		self.bateria_eliminado=StringVar()
		cerrar_select_dialogo=cerrar_ven.cerrar_select(self.dialogo)
		self.dialogo.transient(master=self.parent)
		Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel.gif")
		action_insert_ventana_bateria = partial(update_ventana.update_ven_bateria, self.dialogo)
		action_insert_ventana_panel = partial(update_ventana.update_ven, self.dialogo)
		action_eliminar_panel = partial(eliminar.eliminar_panel,self)
		action_eliminar_bateria = partial(eliminar.eliminar_bateria,self)
		
		imagen_inicio = Tk.Label(self.dialogo, image=img)
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select nombre from panel_solar where isEliminado=0")
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
			lista.append("No hay paneles para eliminar ")
			
		db.close()
		self.panel=Tk.Label(self.dialogo, text="Eliminar panel",font="Arial 14",justify=Tk.CENTER) 
		self.panel_select= Tk.OptionMenu(self.dialogo, self.panel_eliminado,*lista)
		self.Boton_aceptar_eliminar_panel=Tk.Button(self.dialogo, text ="Eliminar panel", command =action_eliminar_panel , activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		
		
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select nombre from bateria where isEliminado=0")
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
			lista.append("No hay paneles para eliminar ")
			
		db.close()
		
		
		
		self.bateria=Tk.Label(self.dialogo, text="Eliminar panel",font="Arial 14",justify=Tk.CENTER) 
		self.bateria_select= Tk.OptionMenu(self.dialogo, self.bateria_eliminado,*lista)
		self.Boton_aceptar_eliminar_bateria=Tk.Button(self.dialogo, text ="Eliminar batería", command =action_eliminar_bateria , activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		
		
		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		
		


		
		Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.panel.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.panel_select.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.Boton_aceptar_eliminar_panel.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		self.bateria.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.bateria_select.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.Boton_aceptar_eliminar_bateria.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		
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
		
		
		
def usar_panel_bateria(self):
		self.dialogo = Toplevel(self.parent)
		self.panel_eliminado=StringVar()
		self.bateria_eliminado=StringVar()
		cerrar_select_dialogo=cerrar_ven.cerrar_select(self.dialogo)
		self.dialogo.transient(master=self.parent)
		Letrero=Tk.Label(self.dialogo,text="Tornasol",fg="green",font=("Arial",18))
		img = Tk.PhotoImage(file="/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/panel.gif")
		imagen_inicio = Tk.Label(self.dialogo, image=img)
		action_insert_ventana_bateria = partial(update_ventana.update_ven_bateria, self.dialogo)
		action_insert_ventana_panel = partial(update_ventana.update_ven, self.dialogo)
		action_usar = partial(usar_panel_bateria_vista,self)
		imagen_inicio = Tk.Label(self.dialogo, image=img)
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select nombre from panel_solar where isEliminado=0")
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
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select b.nombre from bateria b,historial_bateria_panel hpb where hpb.id_bateria=b.id_bateria and hpb.activo=1")
		print("--->",type(cursor))
		print("\n\n")
		nombre_noti="No hay bateria usada actualmente"
		for row in cursor:
		    
		    nombre_noti="Actualmente se usa \n '{nombre_bateria}'".format(nombre_bateria=row[0])
		    
		    #lista.extend(row[0])
		    #print(row[0])
		db.close()

		
		
		self.panel_notificacion=Tk.Label(self.dialogo, text=nombre_noti,font="Arial 14",justify=Tk.CENTER)
		self.panel=Tk.Label(self.dialogo, text="Usar panel",font="Arial 14",justify=Tk.CENTER) 
		self.panel_select= Tk.OptionMenu(self.dialogo, self.panel_eliminado,*lista)
		
		
		
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select nombre from bateria where isEliminado=0")
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
		
		
		
		self.bateria=Tk.Label(self.dialogo, text="Usar panel",font="Arial 14",justify=Tk.CENTER) 
		self.bateria_select= Tk.OptionMenu(self.dialogo, self.bateria_eliminado,*lista)
		self.Boton_aceptar_eliminar_bateria=Tk.Button(self.dialogo, text ="Usar", command = action_usar, activebackground="yellow",relief=Tk.SOLID,bg="green",font="Times 12",bd=4)
		
		
		boton_regresar = Tk.Button(self.dialogo, text='Regresar',command=self.dialogo.destroy,relief=Tk.SOLID,font="Times 12",bd=4,width=20, height=1,activebackground="red")
		
		


		
		Letrero.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		imagen_inicio.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		self.panel_notificacion.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.panel.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.panel_select.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		
		self.bateria.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.bateria_select.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		self.Boton_aceptar_eliminar_bateria.pack(side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
		
		
		boton_regresar.pack(side=TOP,padx=10, pady=5)
		self.dialogo.minsize(width=380, height=680)
		self.dialogo.maxsize(width=500, height=680)
		width=450
		heigth=680
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
	
	

def usar_panel_bateria_vista(self):
	
	if not self.panel_eliminado.get().strip() and not self.bateria_eliminado.get().strip():
		messagebox.showinfo("Error","No ha seleccionado panel y bateria a usar")
	
	elif not self.panel_eliminado.get().strip() :
		messagebox.showinfo("Error","No ha seleccionado panel a usar")	
	elif not self.bateria_eliminado.get().strip():
		messagebox.showinfo("Error","No ha seleccionado bateria a usar")
	else:
		consulta="update historial_bateria_panel set activo ='0' where activo='1'"
		print(consulta)
		mysql=mysql_conection.mysql_conexion_tornasol()
		cursor = mysql.cursor()
		resultado=cursor.execute(consulta)
		mysql.commit()
		mysql.close
		consulta="insert into historial_bateria_panel values(null,(select id_panel from panel_solar where nombre='{nombre_panel}' and isEliminado=0),(select id_bateria from bateria where nombre='{nombre_bateria}' and isEliminado=0),now(),1)".format(nombre_panel=self.panel_eliminado.get(),nombre_bateria=self.bateria_eliminado.get())
		print(consulta)
		mysql=mysql_conection.mysql_conexion_tornasol()
		cursor = mysql.cursor()
		resultado=cursor.execute(consulta)
		mysql.commit()
		print(resultado)
		if resultado>=1:
			messagebox.showinfo("OK","Se seleccionado panel y bateria a usar")
		else:
			messagebox.showinfo("Error","No ha seleccionado panel y bateria a usar")
		mysql.close()
		db =mysql_conection.mysql_conexion_tornasol()
		cursor = db.cursor()
		cursor.execute("select b.nombre from bateria b,historial_bateria_panel hpb where hpb.id_bateria=b.id_bateria and hpb.activo=1")
		print("--->",type(cursor))
		print("\n\n")
		nombre_noti="No hay bateria usada actualmente"
		for row in cursor:
		    
		    nombre_noti="Actualmente se usa \n '{nombre_bateria}'".format(nombre_bateria=row[0])
		    
		    #lista.extend(row[0])
		    #print(row[0])
		db.close()

		
		
		self.panel_notificacion.configure(text=nombre_noti)

