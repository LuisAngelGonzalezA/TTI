/** @brief: Este programa muestra el uso del UART
*/


/*
Guardar los datos de GPLL y analizar la cadena en algunas variables 
las cuales las va a pedir el cliente por tcp el cual siempre se va
a calcular 


https://www.gpsinformation.org/dale/nmea.htm


Se va a leer el dato de GLL en el cual el usuario va a pedir los datos 
y se van a mandar una cadena la cual se debe de analizar para que la visualice 
el usuario

-> La cadena a analizar 


$GPGLL,4916.45,N,12311.12,W,225444,A,*1D

Where:
     GLL          Geographic position, Latitude and Longitude
     4916.46,N    Latitude 49 deg. 16.45 min. North
     12311.12,W   Longitude 123 deg. 11.12 min. West
     225444       Fix taken at 22:54:44 UTC
     A            Data Active or V (void)
     *iD          checksum data
Note that, as of the 2.3 release of NMEA, there is a new field in the GLL sentence at the end just prior to the checksum. For more information on this field see here.




Polín es usar algún bit como bandera


Termios se hace la configuración del UART 




*/


#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "datos.h"
#include "defs.h"
#include "procesos.h"






char *latitud;
char *longitud;
char *hora;
int main()
{
	latitud=limpiar_c();
	longitud=limpiar_c();
	hora=limpiar_c();
	register int i;
	int fd_serie;
	unsigned char dato;
	unsigned short int tempL,tempH,temp;
	fd_serie = config_serial( "/dev/ttyAMA0", B9600 );
	
	printf("serial abierto con descriptor: %d\n", fd_serie);
	int contador=0;
	char cadena[200];
	printf("Empezamos a leer los datos\n");
	//cadena=limpiar_cadena(cadena);
	printf("Si salimos aquí \n");
	//Leemos N datos del UART
	for( ;EVER;)
	{
		read ( fd_serie, &dato, 1 );
		
		
		printf("%c", dato);
		
		if(dato == '\n')
		{
			char validando=' ';
		 	contador=0;
		 	printf("\n\n");
		 	//imprimir(cadena);
		 	validando=validacion_de_datos(cadena);
		 	if(validando == '1')
		 	{
		 		
		 		//imprimir(cadena);
		 		printf("%s\n",cadena);
		 		obtenerdatos(cadena);
		 		printf("%s\n", latitud);
		 		//imprimir(latitud);
		 		printf("%s\n",longitud);
		 		//imprimir(longitud);
		 		printf("%s\n", hora);
		 		//imprimir(hora);
		 		
		 	}
		 	cadena=limpiar_cadena(cadena);
		}
		else 
		{
			//printf("%c",dato);
			cadena[contador]=dato;
			contador++;
		}
		/*
		if(contador>9)
		{
			contador=0;
		}
		*/
	}

	close( fd_serie );

	return 0;
}







