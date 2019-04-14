#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
//#include <sys/stat.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>







extern char *latitud;
extern char *longitud;
extern char *hora;
#define TAM_BUFFER  2000
void mandar(int cd)
{
	printf("\nEnviando\n");
	printf("%s\n",latitud);
	printf("%s\n",longitud);
	printf("%s\n",hora);
	char leer_mensaje[TAM_BUFFER];
	if( write (cd, latitud, strlen(latitud)) < 0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
   	}
   	if( read (cd, &leer_mensaje, TAM_BUFFER) < 0 )
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
   	}
   	printf ("El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);




   	printf("Concluimos la ejecución de la aplicacion Servidor \n");

   	if( write (cd, longitud, strlen(longitud)) < 0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
   	}
   	if( read (cd, &leer_mensaje, TAM_BUFFER) < 0 )
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
   	}
   	printf ("El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
   	printf("Concluimos la ejecución de la aplicacion Servidor \n");

   	if( write (cd, hora, strlen(hora)) < 0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
   	}
   	if( read (cd, &leer_mensaje, TAM_BUFFER) < 0 )
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
   	}
   	printf ("El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
   	printf("Concluimos la ejecución de la aplicacion Servidor \n");
}


