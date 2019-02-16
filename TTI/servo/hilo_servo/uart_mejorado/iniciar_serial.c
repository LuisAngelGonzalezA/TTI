#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <mysql/mysql.h>
#include <string.h>


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
  /*En la comparación de voltaje alto es por si el voltaje fuera menor a 9 en este caso al tratar de 
    visualizar el valor no se podria y se confundiria con el noventa si solo se convierte directo,
    esto quiere decir que entonces estaríamos leyendo datos sumamente diferente con respecto a lo
    medido*/
    
  if(voltaje_bajo <=9) 
  {
    printf("%d.0%d V\n",voltaje_alto,voltaje_bajo);
    char temporal[100]={};
    char datos[100]="insert into panel_registro values(1,";
    sprintf(temporal,"%d",voltaje_alto);
    strcat(datos,temporal);
    sprintf(temporal,".0%d,",voltaje_bajo);
    strcat(datos,temporal);
    strcat(datos,"now())");
    insert_voltaje(datos);
  }
  /*En el caso contrario lo que se esta analizando en esta parte es que el valor leído atraves del UART despúes
  para procesar en el printf lo que se hace es 
  
   ->Como es un valor entero al hacer la división del divisor entre el dividendo obtenemos el cociente 
   ->Siguiendo la logica el residuo seria nuestra parte de decimal el cual nos sirve para despues solo unirlo


  */
  else
  {
    printf("%d.%d V\n",voltaje_alto,voltaje_bajo);
    char temporal[100]={};
    char datos[100]="insert into panel_registro values(1,";
    sprintf(temporal,"%d",voltaje_alto);
    strcat(datos,temporal);
    sprintf(temporal,".%d,",voltaje_bajo);
    strcat(datos,temporal);
    strcat(datos,"now())");
    insert_voltaje(datos);
  }

}
void hexadecimal_a_corriente(int corriente_alto,int corriente_bajo)
{
  int valor;
  valor=corriente_alto;
  /*En la parte de corriemiento para que unamos la parte alta y baja de los datos leídos del modulo RS-232
  atraves del módulo UART de la raspberry el cual se va a agregar los siguientes 8 bits .
  */
  valor=corriente_alto<<8;
  /*¿Porque se usa un or?
	Bueno principalmente para que nuestros datos de corrimiento no se vean afectados ademas que la operacion 
	booleana de or es una suma de numero.
	*/
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
  /*
  Se hace en el envio de el PIC16F876A es enviar todo el valor pero lo que se hace es mandar
  el dato en hexadecima para despues solo convertirlo en decimal y ese valor sea nuestra corriente
  como en el caso del voltaje.
  */
  else printf("%d.%d A\n",valor/1000,valor%1000);

}
void hexadecimal_a_temperatura(int temperatura_alto,int temperatura_bajo)
{
    /*
	La parte de la medición de datos es la siguiente dato que se leé de parte alta como parte baja 
	va a dar como resultado su total en decimal es por eso que solo se imprime lo que nos manda los
	como se muestra es solo un print de esos valore hexadecimales convertidos a enteros.

    */
    printf("%d.%d °C\n",temperatura_alto,temperatura_bajo);


}



