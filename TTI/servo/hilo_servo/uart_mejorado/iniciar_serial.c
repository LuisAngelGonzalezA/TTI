#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <mysql/mysql.h>
#include <string.h>
#include "def.h" 			/*Mandamos a llamar el dato de Ever*/
#include "iniciar_serial.h" /*Mandamos a llamar la funcion de config_serial para posteriormente hacer la
							  conexion de el puerto ttyS0*/
#include <pthread.h>			

double voltaje_mysql;
double corriente_mysql;
double temperatura_mysql;
extern int espera_de_recepcion;
int puerto_serial;  
extern unsigned char peticion;

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
void insert_voltaje(char *voltaje)
{
  
	//printf("\nSe insertara = %s\n",voltaje);
  
	MYSQL *con;

	char *server="localhost";
	char *user="TT";
	char *pass="TT";
	char *database="tornasol";

	con=mysql_init(NULL);
	if(!mysql_real_connect(con,server,user,pass,database,0,NULL,0))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
	}
	if (mysql_query(con, voltaje)) 
	{
		mysql_error(con);
	}
	//else printf("\nInsertamos en la base y consultamos nuevo registro\n");


	mysql_close(con);  
}


void hexadecimal_a_voltaje(int voltaje_alto,int voltaje_bajo)
{
  
  voltaje_mysql=(double) voltaje_alto;
  voltaje_mysql+=(double) voltaje_bajo/100;
  printf("\nVoltaje médido  :  %lf\n",voltaje_mysql);
  
  /*En la comparación de voltaje alto es por si el voltaje fuera menor a 9 en este caso al tratar de 
    visualizar el valor no se podria y se confundiria con el noventa si solo se convierte directo,
    esto quiere decir que entonces estaríamos leyendo datos sumamente diferente con respecto a lo
    medido*/
    
  /*if(voltaje_bajo <=9) 
  {
    printf("%d.0%d V\n",voltaje_alto,voltaje_bajo);
    char temporal[100]={};
    char datos[100]="insert into sensadoP(id_panel,voltaje,hora) values(1,";
    sprintf(temporal,"%d",voltaje_alto);
    strcat(datos,temporal);
    sprintf(temporal,".0%d,",voltaje_bajo);
    strcat(datos,temporal);
    strcat(datos,"now())");
    insert_voltaje(datos);
  }*/
  /*En el caso contrario lo que se esta analizando en esta parte es que el valor leído atraves del UART despúes
  para procesar en el printf lo que se hace es 
  
   ->Como es un valor entero al hacer la división del divisor entre el dividendo obtenemos el cociente 
   ->Siguiendo la logica el residuo seria nuestra parte de decimal el cual nos sirve para despues solo unirlo


  */
  /*else
  {
    printf("%d.%d V\n",voltaje_alto,voltaje_bajo);
    char temporal[100]={};
    char datos[100]="insert into sensadoP(id_panel,voltaje,hora) values(1,";
    sprintf(temporal,"%d",voltaje_alto);
    strcat(datos,temporal);
    sprintf(temporal,".%d,",voltaje_bajo);
    strcat(datos,temporal);
    strcat(datos,"now())");
    insert_voltaje(datos);
  }*/
  
  

}
void hexadecimal_a_corriente(int corriente_alto,int corriente_bajo)
{
  
  corriente_mysql=(double)corriente_alto;
  corriente_mysql+=(double) corriente_bajo/1000;
   printf("\nCorriente médida  :  %lf\n",corriente_mysql);
  
  
 /* int valor;
  valor=corriente_alto;
  
  
  En la parte de corriemiento para que unamos la parte alta y baja de los datos leídos del modulo RS-232
  atraves del módulo UART de la raspberry el cual se va a agregar los siguientes 8 bits .
  
  valor=corriente_alto<<8;
  ¿Porque se usa un or?
	Bueno principalmente para que nuestros datos de corrimiento no se vean afectados ademas que la operacion 
	booleana de or es una suma de numero.
	
  valor=valor | corriente_bajo;
  //valor=valor & BAJO;
  if(valor <=9)
  {
    printf("0.00%d A\n",valor);
  }
  else if(valor <=99)
  {
    printf("0.0%d A\n",valor);
  }
  
  Se hace en el envio de el PIC16F876A es enviar todo el valor pero lo que se hace es mandar
  el dato en hexadecima para despues solo convertirlo en decimal y ese valor sea nuestra corriente
  como en el caso del voltaje.| estado_fase             |

  
  else printf("%d.%d A\n",valor/1000,valor%1000);
  */
}
void hexadecimal_a_temperatura(int temperatura_alto,int temperatura_bajo)
{
    /*
	La parte de la medición de datos es la siguiente dato que se leé de parte alta como parte baja 
	va a dar como resultado su total en decimal es por eso que solo se imprime lo que nos manda los
	como se muestra es solo un print de esos valore hexadecimales convertidos a enteros.

    */
    temperatura_mysql=(double)temperatura_alto;
    temperatura_mysql+=(double)temperatura_bajo/10;
    printf("\nTemperatura médida : %lf °C\n",temperatura_mysql);


}

void guardar_datos_voltaje(int * datos_recibidos_UART)
{
  hexadecimal_a_voltaje(datos_recibidos_UART[0],datos_recibidos_UART[1]);
  
  
  
}

void guardar_datos_bateria(int * datos_recibidos_UART)
{
  hexadecimal_a_voltaje(datos_recibidos_UART[0],datos_recibidos_UART[1]);
  hexadecimal_a_corriente(datos_recibidos_UART[2],datos_recibidos_UART[3]);
  hexadecimal_a_temperatura(datos_recibidos_UART[4],datos_recibidos_UART[5]);
  
  
}
void guardar_datos_bateria_descarga(int * datos_recibidos_UART)
{
  hexadecimal_a_voltaje(datos_recibidos_UART[0],datos_recibidos_UART[1]);
  hexadecimal_a_corriente(datos_recibidos_UART[2],datos_recibidos_UART[3]);
  hexadecimal_a_temperatura(datos_recibidos_UART[4],datos_recibidos_UART[5]);
  
  
}





void * espera(void *arg)
{
  while(1)
  {
  if(espera_de_recepcion<10)
  {
  sleep(1);
  //printf("\n\nHa pasado un segundo\n");

  espera_de_recepcion=espera_de_recepcion+1;
  }
  else
  {
	  switch(peticion)
	  { 
		  case 0xE1:
					printf("Error en la lectura del módulo de panel");
					printf("  ->Reinicie si se desconcto\n");
					close( puerto_serial );
					sleep(5);
					puerto_serial = config_serial( "/dev/ttyS0", B9600 );
					write( puerto_serial, &peticion, 1 );
					close( puerto_serial );
					sleep(5);
					break;
		  case 0xE2:
					printf("Error en la lectura del módulo de bateria");
					printf("  ->Reinicie si se desconcto\n");
					break;
		  case 0xE3:
					printf("Error en la lectura del módulo de bateria descarga ");
					printf("  ->Reinicie si se desconcto\n");
					break;
		  default:
					break;
		  
	
		  
	  }
  } 
}
}


void recibir_valores_de_modulos(unsigned char dato_envio)
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
	int bandera_de_salida=0;

                       /*El puerto serial nos indicara si el puerto serial del uart en este
											caso el ttySO si es mayor o igual nos indicara que que la apertura
											del puerto se a abierto con un entero
											*/

	unsigned char dato_recibido; /*La declaración las variables en char y ademas de unsigned nos 
											  denotan que los valores a recibir seran superiores a lo estableci-
											  do el cual es de un rango de -128 a 127 el cual al transformat el
											  C1 a un entero es 193 y el cierre es a 194 */
	int datos_recibidos_UART[6];       /*Almacenar los datos leídos de la Raspberry para posteriormente ser
										llamados en las funciones de:
														- void hexadecimal_a_voltaje
														- void hexadecimal_a_corriente
														- void hexadecimal_a_temperatura


											*/

	puerto_serial = config_serial( "/dev/ttyS0", B9600 );
	 										/*
												Al llamar a la función de config_serial esta nos puede devolver
												 -Error al abrir el dispositivo
												 -Error del baudaje
												 -Error al tratar de leer los datos sin conectar( Valida si manda
												 o no manda mensaje o si quiera si esta conectado)
												 -


	 										*/
	printf("serial abierto con descriptor: %d\n", puerto_serial);
	/*dato_envio = 0xE1;*/ 						/*
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
	
->Ilustración



		    Envió                   | E1 --------------->     |Recibé
		    Empieza comunicaión	    |    <-------------- C1   |Envió de aceptación
			Recibé Alta Voltaje     | 	 <-------------- Dato |Parte Alta Voltaje
			Recibé Baja Voltaje     | 	 <-------------- Dato |Parte Baja Voltaje
 Raspberry	Recibé Alta Corriente   | 	 <-------------- Dato |Parte Alta Corriente    PIC16F876A
		    Recibé Baja Corriente   | 	 <-------------- Dato |Parte Baja Corriente
		    Recibé Alta Temperatura | 	 <-------------- Dato |Parte Alta Temperatura
			Recibé Baja Temperatura | 	 <-------------- Dato |Parte Baja Temperatura
			Termina recepción       | 	 <-------------- C2   |Envió de terminación






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
				espera_de_recepcion=0;
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
				//printf("\"Datos leídos\"\n\n");
				guardar_datos_voltaje(datos_recibidos_UART);
				bandera_de_salida=1;
				printf("Terminando Trasmición %X\n",dato_recibido);
				espera_de_recepcion=0;
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
			//printf("0x%d     %c\n", dato_recibido,dato_recibido);
			datos_recibidos_UART[validacion-1]=(int)dato_recibido;
			
			}
		
		}
		/* Esperamos dos segundo para la siguiente lectura de datos*/
		usleep(300000);
		if(bandera_de_salida==2)
		{
		break;
		}
		//printf("--->finaliza la transmision\n");
	}
	close( puerto_serial );
	
}



