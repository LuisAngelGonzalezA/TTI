#!/usr/bin/env python
# -*- coding: utf-8 -*-
import tkinter as Tk
import threading
from tkinter import messagebox
import time
import sys
import os



siguiente=0;
graficar_panel=0
inicio_bandera=0

siguiente1=0;
graficar_bateria=0
inicio_bandera1=0


siguiente2=0;
graficar_bateria2=0
inicio_bandera2=0





def guardar():
    f = open ('/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/inicio.txt','w')
    f.write('0')
    f.close()

def panel():
    f = open ('/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/inicio.txt','r')
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
        messagebox.showinfo("Precaucion", "En ejecucion grafica")
    



def ventana_grafica():
    os.system('python /home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/grafica.py')
    
    
    
    
    
    
"""

		B A T E R Í A

"""


def guardar1():
    f = open ('/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/inicio1.txt','w')
    f.write('0')
    f.close()

def bateria():
    f = open ('/home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/inicio1.txt','r')
    mensaje = f.read()
    #print(mensaje)
    f.close()
    
    global inicio_bandera1
    if inicio_bandera1==0:
        guardar1();
        mensaje='0'

    if mensaje=='0':
        #global inicio_bandera

        inicio_bandera1=1
        t = threading.Thread(target=ventana_grafica_bateria)
        t.start()
        
    else:
        messagebox.showinfo("Precaucion", "En ejecucion grafica")
    



def ventana_grafica_bateria():
    os.system('python /home/pi/TTI/TTI/Interfaz_grafica_python/Documentos/pruebas_python/sistema/grafica1.py')
    


   
