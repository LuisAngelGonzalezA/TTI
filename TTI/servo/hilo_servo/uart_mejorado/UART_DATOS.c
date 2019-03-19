#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "iniciar_serial.h" /*Mandamos a llamar la funcion de config_serial para posteriormente hacer la
							  conexion de el puerto ttyS0*/
#include <pthread.h>
#include "def.h" 			/*Mandamos a llamar el dato de Ever*/


  
unsigned char peticion;
int espera_de_recepcion;
int main()
{
	espera_de_recepcion=0;
	pthread_t tids;
	int i=0;
    pthread_create(&tids,NULL,espera,NULL);
    while(EVER)
    {
			i=0;
			peticion= 0xE1;
			for(;i<3;i++)
			{
				printf("0x%X\n", peticion);
				recibir_valores_de_modulos(peticion);
				peticion++;
			}
			
	}
	return 0;
}


