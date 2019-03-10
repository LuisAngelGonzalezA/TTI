#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "iniciar_serial.h" /*Mandamos a llamar la funcion de config_serial para posteriormente hacer la
							  conexion de el puerto ttyS0*/
#include <pthread.h>


  
unsigned char peticion;
int espera_de_recepcion;
int main()
{
	espera_de_recepcion=0;
	peticion=0xE1;
	pthread_t tids;

    pthread_create(&tids,NULL,espera,NULL);
	recibir_valores_de_modulos(peticion);
	pthread_join(tids,NULL);
	return 0;
}


