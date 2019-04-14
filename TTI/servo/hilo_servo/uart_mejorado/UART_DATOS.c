#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "iniciar_serial.h" /*Mandamos a llamar la funcion de config_serial para posteriormente hacer la
							  conexion de el puerto ttyS0*/
#include <pthread.h>
#include "def.h" 			/*Mandamos a llamar el dato de Ever*/



unsigned char peticion;
int espera_de_recepcion;
int main()
{                             
	demonio();                
	espera_de_recepcion=0;
	pthread_t tids;
	int i=0;
    pthread_create(&tids,NULL,espera,NULL);
    
    while(EVER)
    {
			i=0;

			
			
			
			peticion= 0xE1;
			for(;i<2;i++)
			 {
				//printf("\n\n\n\t0x%X\n\n\n",peticion);
				syslog(LOG_INFO,"\n\n\n\t0x%X\n\n\n",peticion);
				
				//printf("0x%X\n", peticion);
				syslog(LOG_INFO,"Entrando");
				recibir_valores_de_modulos(peticion);
				
				
				peticion+=2;
			 }			
	}
	return 0;
}


