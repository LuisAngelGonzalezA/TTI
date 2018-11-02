#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "def.h"
#include "iniciar_serial.c"




int main()
{
	register int i,bandera;
	int fd_serie;
	static unsigned char dato,dato_envio;
	unsigned short int tempL, tempH, temp;
	fd_serie = config_serial( "/dev/ttyS0", B9600 );
	printf("serial abierto con descriptor: %d\n", fd_serie);
	dato_envio = 0xE1;
	dato=0x00;
	bandera=0;
	for( ; EVER; )
	{	
		write( fd_serie, &dato_envio, 1 );
		printf("0x%X\n", dato_envio);
		
		for(i=0;i<9-1;i++)
		{
			if(read ( fd_serie, &dato, 1 )==0 && i==0)
			{	
				printf("Dato no valido");
				close(fd_serie);
				sleep(5);
				fd_serie = config_serial( "/dev/ttyS0", B9600 );
			    printf("serial abierto con descriptor: %d\n", fd_serie);
				break;
			}
			else if(dato==193 && i==0)
			{
				printf("Comenzando Transmición  %X\n",dato);
			}
			else if(dato!=193 && i==0)
			{
				printf("Error en lectura de datos %X\n",dato);
				close(fd_serie);
				sleep(5);
				fd_serie = config_serial( "/dev/ttyS0", B9600 );
			        printf("serial abierto con descriptor: %d\n", fd_serie);
				break;
			}
			else if(dato==194 && i==7)
			{
				printf("Terminando Trasmición %X\n",dato);
			}
			else if(dato!=194 && i==7)
			{
				printf("Error al finalizar Trasmición %X\n",dato);
				close(fd_serie);
				sleep(5);
				fd_serie = config_serial( "/dev/ttyS0", B9600 );
			        printf("serial abierto con descriptor: %d\n", fd_serie);
				break;
			}
			

			else
			{
			printf("0x%d     %c\n", dato,dato);
			bandera++;	
			}
		}
		
		sleep(2);
		printf("--->finaliza la transmision\n");
	}
	close( fd_serie );

	return 0;
}
