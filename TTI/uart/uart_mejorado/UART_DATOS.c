#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "def.h" 			/*Mandamos a llamar el dato de Ever*/
#include "iniciar_serial.h" /*Mandamos a llamar la funcion de config_serial para posteriormente hacer la
							  conexion de el puerto ttyS0*/




int main()
{
	register int validacion;           /*Se realizara la validación en la entrada de los datos los cuales nos
							             indicaran :
								   			-Si el dato de entrada es diferente del de apertura en 
								   			 este caso si es diferente a C1
								   			-Nos validara ademas los datos de entrada los cuales seran 
								   			 6 datos
								   			-Nos validara si el cierre de la entrada es igual a C2 para
								   			 el cierre de los datos
							   			 */

    int puerto_serial;                     /*El puerto serial nos indicara si el puerto serial del uart en este
											caso el ttySO si es mayor o igual nos indicara que que la apertura
											del puerto se a abierto con un entero
											*/

	unsigned char dato_recibido,dato_envio; /*La declaración las variables en char y ademas de unsigned nos 
											  denotan que los valores a recibir seran superiores a lo estableci-
											  do el cual es de un rango de -128 a 127 el cual al transformat el
											  C1 a un entero es 193 y el cierre es a 194 */

	puerto_serial = config_serial( "/dev/ttyUSB0", B9600 );
	 										/*
												Al llamar a la función de config_serial esta nos puede devolver
												 -Error al abrir el dispositivo
												 -Error del baudaje
												 -Error al tratar de leer los datos sin conectar( Valida si manda
												 o no manda mensaje o si quiera si esta conectado)
												 -


	 										*/
	printf("serial abierto con descriptor: %d\n", puerto_serial);
	dato_envio = 0xE1; 						/*
											Inicializamor la variable de dato envio la mas adelante se enviara
											*/
	dato_recibido=0x00;						/*
											Solo vamos a dar la seguridad de que al inicio la variable de dato
											recibir algo diferente de cero		
											*/
	/* inicio de un ciclo infinito el cual se va a estar conmutando con los demas moódulos de medición*/
	for( ; EVER; )
	{	
		write( puerto_serial, &dato_envio, 1 );
											/*
											En la parte del write enviamos el dato de referencia de la variable
											la cual el RS-232 la recibira atraves de nuestro conmutador
											*/
		printf("0x%X\n", dato_envio);
		
		/* En la parte de la validación vamos a recibir 8 datos
			-C1 apertura
			-Parte alta del voltaje
			-Parte baja del voltaje
			-Parte alta de la corriente
			-Parte baja de la corriente
			-Parte alta de la temperatura
			-Parte baja de la temperatura 
			-C2 el cierre de la comunicación
		*/
		for(validacion = 0; validacion < 8 ; validacion++ )
		{
			/*
			En la primera parte de la lectura lo que se procesa es la captura del datos el cual si al iniciar
			la comunicación es diferente al de apertura el dato recibido no es adecuado para la comunicación,
			lo cual se procesa el cierre del puerto para volver a sincronizar la lectura de nuestro módulo de
			medición
			*/
			if(read ( puerto_serial, &dato_recibido, 1 ) == 0 && validacion == 0)
			{	
				printf("dato_recibido no valido\n");
				close(puerto_serial);
				sleep(5);
				puerto_serial = config_serial( "/dev/ttyS0", B9600 );
			    printf("serial abierto con descriptor: %d\n", puerto_serial);
				break;
			}
			/*
			Si el valor iniciar es C1 y ademas nuestra validación es cero esto nos indica que la conexion se
			esta estableciendo correctamenta la cual se hace un comienzo de datos en esta parte la apertura
			es 
									-	C1
			*/
			else if( dato_recibido == 193 && validacion == 0)
			{
				printf("Comenzando Transmición  %X\n",dato_recibido);
			}
			/*
			Si el valor iniciar es C1 y ademas nuestra validación es cero esto nos indica que la conexion no se
			esta estableciendo correctamenta la cual se hace un comienzo de datos en esta parte la apertura no es 
			la indicada la cual se cierra el puerto para volver a sincronizar los datos.
			*/
			else if( dato_recibido != 193 && validacion == 0)
			{
				printf("Error en lectura de dato_recibidos %X\n",dato_recibido);
				close(puerto_serial);
				sleep(5);
				puerto_serial = config_serial( "/dev/ttyS0", B9600 );
			        printf("serial abierto con descriptor: %d\n", puerto_serial);
				break;
			}
			/*
			Si el valor iniciar es C2 y ademas nuestra validación es siete esto nos indica que la conexion se
			esta terminando la cual 
									-	C2
			y mostramos Terminación
			*/
			else if(dato_recibido == 194 && validacion == 7)
			{
				printf("Terminando Trasmición %X\n",dato_recibido);
			}
			/*
			Si el valor iniciar no es  C2 y ademas nuestra validación es siete esto nos indica que la conexion no se
			esta terminando la cual se hace un final de conexion
			*/
			else if( dato_recibido != 194 && validacion == 7 )
			{
				printf("Error al finalizar Trasmición %X\n",dato_recibido);
				close(puerto_serial);
				sleep(5);
				puerto_serial = config_serial( "/dev/ttyS0", B9600 );
			        printf("serial abierto con descriptor: %d\n", puerto_serial);
				break;
			}
			
			/*
			Se hace la lectura de los seis datos que nos manda el módulo de medicón 
			*/
			else
			{
			printf("0x%d     %c\n", dato_recibido,dato_recibido);
			
			}
		}
		/* Esperamos dos segundo para la siguiente lectura de datos*/
		sleep(2);
		printf("--->finaliza la transmision\n");
	}
	close( puerto_serial );

	return 0;
}
