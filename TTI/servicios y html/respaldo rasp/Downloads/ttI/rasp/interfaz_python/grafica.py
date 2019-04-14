#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import division

#----------------------------------------------------------------------
# Nombre:       ejemplo_matplotlib_grafica_completa.py
# PropÃ³sito:    Aprender a realizar una grÃ¡fica lo mÃ¡s completa posible
#
# Origen:        Propio.
# Autor:         Luis Miguel SÃ¡nchez-Brea,JosÃ© MarÃ­a Herrera-Fernandez  
#
# CreaciÃ³n:        18 de Septiembre de 2013
# Historia:
#
# Dependencias:    numpy, matplotlib
# Licencia:        GPL
#----------------------------------------------------------------------


"""
DescripciÃ³n: Doble grÃ¡fica senoidal donde se muestran la mayorÃ­a de los complementos 
que se pueden aÃ±adir a una grÃ¡fica
"""

import numpy as np                  # Cargamos numpy como el alias np
import matplotlib.pyplot as plt     # Crgagamos matplotlib.pyplot como el alias plt

# Definimos el periodo de la funciÃ³n
periodo = 0.5

# Definimos el array dimensional
x = np.linspace(0, 2, 1000)

# Definimos la funciÃ³n senoidal
y = np.sin(2*np.pi*x/periodo)

# Creamos la figura
plt.figure()

# Dibujamos  en negro discontinuo con etiqueta y1
plt.plot(x, y, 'k--', linewidth = 2, label = 'y1')

# Mantenemos la misma figura parta la siguiente grÃ¡fica
plt.hold(True)

# Esta vez dibujamos - y en rojo co etiqueta y2
plt.plot(x,-y,'r', linewidth = 2, label = 'y2')

# AÃ±adimos la leyenda
plt.legend(loc = 2)

# AÃ±adimos las etiquetas poniermo en Latex "mu" sÃ­mbolo de micras
plt.xlabel(r"$x (\mu m)$", fontsize = 24, color = (1,0,0))
plt.ylabel(r"$y (\mu m)$", fontsize = 24, color = 'blue')

# AÃ±adimos texto
plt.text(x = 1, y = 0.0, s = u'T = 0.05', fontsize = 24)

# AÃ±adimos la rejilla
plt.grid(True)
plt.grid(color = '0.5', linestyle = '--', linewidth = 1)

# AÃ±adimos los ejes
plt.axis('tight')

# AÃ±adimos el tÃ­tulo 
plt.title('(a)',fontsize = 28, color = '0.75', verticalalignment = 'baseline', horizontalalignment = 'center')

# Guardamos
plt.savefig('plotCompleta.png')
	
# Mostramos en pantalla
plt.show()