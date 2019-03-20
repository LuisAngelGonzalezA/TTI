#!/usr/bin/env python
# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np
import time
import random
import pymysql

def mysql_datos():
    db = pymysql.connect(
         user='TT',
         password='TT',
         host='localhost',
         database='tornasol')
    cursor = db.cursor()
    sql = "select voltaje from sensadoP order by hora desc limit 1"

    cursor.execute(sql)

    myresult = cursor.fetchall()
    
    for x in myresult:
      print(x[0])
      valor=x[0]
    db.close()
    return valor


leitura =[]
fig, ax = plt.subplots()
contador = 0
eixo_x = 50
while True:
    
    datostext=mysql_datos()
    
    
    try:
    	dados=float(datostext)

    except Exception as e:
    	dados=0
    
	

       #firmware deve ter um delay de pelo menos 100ms entre cada envio
    print(dados)
    ax.clear()
    ax.set_xlim([0,eixo_x])   #faixa do eixo horizontal
    ax.set_ylim([0,6]) # faixa do eixo vertical   
    #leitura.append(random.randint(0,1023))  #teste com numeros aleatorios
    leitura.append(dados)  
   
    ax.plot(leitura)
    plt.pause(.0000000000000000000001)     
    
    contador = contador + 1
    if (contador > eixo_x):
	   leitura.pop(0)
    

	#datostext.close()
    

ser.close()