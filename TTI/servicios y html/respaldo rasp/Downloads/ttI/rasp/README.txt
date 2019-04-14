
Anexo del código en las lineas 289 en adelante para 
la interpretación de los datos a enviar de ras a pic.


Necesitamos mandar a pic un numero Hexadecimal de 
						
						"0xe1"

Nos mandara nuestros valores que deseemos por el serial

Pero antes de esos nos manda un inicio para mandar los valores
el cual nos estará devolviendo el pic 

						
						"0xc1"

EL cúal al recibirlo nosotros tendremos los valores de 

						-Corriente
						-Voltaje
						-Temperatura


	**Siguiendo el anaísis con respecto a nuestras
	  tablas de excel lo cual nos va a decir los
	  valores que debemos de recibír, para valir en 
	  prímera intancia el como va a ser el analísis
	  de dichos valores




Despues de mandarnos los valores recibirimos un numero de confirmación
de que los valores son todos el cual es el cierré de la comunicación entre 
las raspberry y el pic.
El último valor recibidó será el número hexadecimal 


						"0xc2"