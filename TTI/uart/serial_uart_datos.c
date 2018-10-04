/** @brief: Este programa muestra el uso del UART
*/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define N  1024
#define EVER 1



void * mando( void *idh );
void * recibo( void *idh );

int config_serial ( char *, speed_t );

int fd_serie;
int matar_envio=0;

int main()
{
	
	pthread_t tids[2];
	int nh[2]={0 , 1},*hilo;
	
	unsigned char dato;
	

	fd_serie = config_serial( "/dev/S0", B9600 );
	printf("serial abierto con descriptor: %d\n", fd_serie);
	pthread_create(&tids[0],NULL,mando,(void *) & nh[0]);
	pthread_create(&tids[1],NULL,recibo,(void *) & nh[1]);

	pthread_join(tids[0],(void **)&hilo);
	printf("--->%d\n",*hilo);
	pthread_join(tids[1],(void **)&hilo);
	printf("--->%d\n",*hilo);
	printf("\n\n");
	printf("------->Finalizado<<<<<<<----\n");


	//Leemos N datos del UART
		dato = 0x55;
	for( ; EVER; )
	{
		read ( fd_serie, &dato, 1 );
		printf("%c", dato);
		//write( fd_serie, &dato, 1 );
		//sleep(1);
	}
	close( fd_serie );

	return 0;
}

void * mando( void *idh )
{
	static unsigned char dato_mandar= 0xE2;
	while(1)
	{
	
	if(matar_envio==0)
	{
		
		printf("0x%X\n",dato_mandar);
		write( fd_serie, &dato_mandar, 1 );
	}
	sleep(1);
	}
	pthread_exit(idh);
		
	//}
}
void * recibo( void *idh )
{
	register int i;
	unsigned char dato=0x00;
	static unsigned char comparacion_inicio= 0xC1;
	static unsigned char comparacion_final= 0xC2;
	printf("\t\t %c  %c\n", comparacion_inicio,comparacion_final);
	while(1)
	{
	sleep(1);
	fflush(stdin);
	printf("ESPERANDO DATOS\n");
	//scanf("%s",&dato);
	read ( fd_serie, &dato, 1 );
	printf("Dato ingresado--->%c    %X\n",dato,dato);
	if(dato == comparacion_inicio)
	{
		printf("\tRecibiendo datos\n");
		
		matar_envio=1;
		for ( i = 0; i <=7; i++)
		{
			//comparacion=0x30;
			
			fflush( stdin );
			//scanf("%s",&dato);
			read ( fd_serie, &dato, 1 );

			printf("Dato ingresado [%d]: %c --->%X--------->%c<<---\n",i,dato,dato,comparacion_final);
			if(dato == comparacion_final)
			{
				printf("EXITO AL FINALIZAR\n");
				matar_envio=0;
				break;
			}
		}
		
	}
	}
	pthread_exit(idh);
	
}


/** @brief: Esta funcion Configura la interfaz serie
 *  @param: dispositivo_serial, Nombre el dispositivo serial a usar: ttyUSB0, ttyUSB1, etc
 *  @param: baudios, Velocidad de comunicacion. Se usa la constante Bxxxx, donde xxxx  es la
 *          velocidad. Estan definidas en termios.h. Ejemplo: B9600, B19200..
 *  @return: fd, Descriptor del serial
 *******************************************************************************************
 */
int config_serial( char *dispositivo_serial, speed_t baudios )
{
	struct termios newtermios;
  	int fd;
/*
 * Se abre un descriptor de archivo para manejar la interfaz serie
 * O_RDWR - Se abre el descriptor para lectura y escritura
 * O_NOCTTY - El dispositivo terminal no se convertira en el terminal del proceso
 * ~O_NONBLOCK - Se hace bloqueante la lectura de datos
 */
  	fd = open( dispositivo_serial, (O_RDWR | O_NOCTTY) & ~O_NONBLOCK );
	if( fd == -1 )
	{
		printf("Error al abrir el dispositivo tty \n");
		exit( EXIT_FAILURE );
  	}
/*
 * cflag - Proporciona los indicadores de modo de control
 *	CBAUD	- Velocidad de transmision en baudios.
 * 	CS8	- Especifica los bits por dato, en este caso 8
 * 	CLOCAL 	- Ignora las lineas de control del modem: CTS y RTS
 * 	CREAD  	- Habilita el receptor del UART
 * iflag - proporciona los indicadores de modo de entrada
 * 	IGNPAR 	- Ingnora errores de paridad, es decir, comunicación sin paridad
 * oflag - Proporciona los indicadores de modo de salida
 * lflag - Proporciona indicadores de modo local
 * 	TCIOFLUSH - Elimina datos recibidos pero no leidos, como los escritos pero no transmitidos
 * 	~ICANON - Establece modo no canonico, en este modo la entrada esta disponible inmediatamente
 * cc[]	 - Arreglo que define caracteres especiales de control
 *	VMIN > 0, VTIME = 0 - Bloquea la lectura hasta que el numero de bytes (1) esta disponible
 */
	newtermios.c_cflag 	= CBAUD | CS8 | CLOCAL | CREAD;
  	newtermios.c_iflag 	= IGNPAR;
  	newtermios.c_oflag	= 0;
  	newtermios.c_lflag 	= TCIOFLUSH | ~ICANON;
  	newtermios.c_cc[VMIN]	= 1;
  	newtermios.c_cc[VTIME]	= 0;

// Configura la velocidad de salida del UART
  	if( cfsetospeed( &newtermios, baudios ) == -1 )
	{
		printf("Error al establecer velocidad de salida \n");
		exit( EXIT_FAILURE );
  	}
// Configura la velocidad de entrada del UART
	if( cfsetispeed( &newtermios, baudios ) == -1 )
	{
		printf("Error al establecer velocidad de entrada \n" );
		exit( EXIT_FAILURE );
	}
// Limpia el buffer de entrada
	if( tcflush( fd, TCIFLUSH ) == -1 )
	{
		printf("Error al limpiar el buffer de entrada \n" );
		exit( EXIT_FAILURE );
	}
// Limpia el buffer de salida
	if( tcflush( fd, TCOFLUSH ) == -1 )
	{
		printf("Error al limpiar el buffer de salida \n" );
		exit( EXIT_FAILURE );
	}
/*
 * Se establece los parametros de terminal asociados con el
 * descriptor de archivo fd utilizando la estructura termios
 * TCSANOW - Cambia los valores inmediatamente
 */
	if( tcsetattr( fd, TCSANOW, &newtermios ) == -1 )
	{
		printf("Error al establecer los parametros de la terminal \n" );
		exit( EXIT_FAILURE );
	}
//Retorna el descriptor de archivo
	return fd;
}

