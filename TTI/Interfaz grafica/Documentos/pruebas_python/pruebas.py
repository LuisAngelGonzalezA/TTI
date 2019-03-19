from tkinter import *
import tkinter as Tk
import threading
from tkinter import messagebox
import time
import sys
import os
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
    #print(mensaje)
    f.close()
    
    global inicio_bandera
    if inicio_bandera==0:
        guardar();
        mensaje='0'

    if mensaje=='0':
        #global inicio_bandera

        inicio_bandera=1
        t = threading.Thread(target=ventana_grafica)
        t.start()
        
    else:
        me.showinfo("Precaucion", "En ejecucion grafica")
    



def ventana_grafica():
    os.system('python /home/luis/Documentos/pruebas_python/grafica.py')
   

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
        self.top.transient(parent=self.parent)

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
        self.parent.wait_window(d.top)

if __name__ == "__main__":
    
    # Ahora preparamos a la ventana
    root = Tk.Tk()
    app = MyApp(root)
    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)
    root.columnconfigure(1, weight=1)
    root.rowconfigure(1, weight=1)
    root.columnconfigure(2, weight=1)
    root.rowconfigure(2, weight=1)
    root.columnconfigure(3, weight=1)
    root.rowconfigure(4, weight=1)
    
    img = Tk.PhotoImage(file="panel.gif")
    widget = Tk.Label(root, image=img).grid(row=0, column=0, columnspan=3,sticky="w")
    

    label=Tk.Label(root, text="Tornasol",width=10, height=5,fg="green",font=("Arial",18)).grid(row=0, column=0, columnspan=3,side=TOP, fill=BOTH, expand=True,padx=10, pady=5)
 
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