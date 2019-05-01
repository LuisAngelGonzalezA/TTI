#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <mysql/mysql.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "def.h" 			/*Mandamos a llamar el dato de Ever*/
#include "iniciar_serial.h" /*Mandamos a llamar la funcion de config_serial para posteriormente hacer la
							  conexion de el puerto ttyS0*/
#include <pthread.h>			

double voltaje_mysql;
double corriente_mysql;
double corriente_mysql_descarga;
double corriente_mysql_descarga_temporal;
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
		//printf("Error al abrir el dispositivo tty \n");
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
		syslog(LOG_INFO,"Error al establecer velocidad de salida \n");
		//printf("Error al establecer velocidad de salida \n");
		exit( EXIT_FAILURE );
  	}
// Configura la velocidad de entrada del UART
	if( cfsetispeed( &newtermios, baudios ) == -1 )
	{
		//printf("Error al establecer velocidad de entrada \n" );
		syslog(LOG_INFO,"Error al establecer velocidad de entrada \n" );
		exit( EXIT_FAILURE );
	}
// Limpia el buffer de entrada
	if( tcflush( fd, TCIFLUSH ) == -1 )
	{
		//printf("Error al limpiar el buffer de entrada \n" );
		syslog(LOG_INFO,"Error al limpiar el buffer de entrada \n" );
		exit( EXIT_FAILURE );
	}
// Limpia el buffer de salida
	if( tcflush( fd, TCOFLUSH ) == -1 )
	{
		//printf("Error al limpiar el buffer de salida \n" );
		syslog(LOG_INFO,"Error al limpiar el buffer de salida \n" );
		exit( EXIT_FAILURE );
	}
/*
 * Se establece los parametros de terminal asociados con el
 * descriptor de archivo fd utilizando la estructura termios
 * TCSANOW - Cambia los valores inmediatamente
 */
	if( tcsetattr( fd, TCSANOW, &newtermios ) == -1 )
	{
		//printf("Error al establecer los parametros de la terminal \n" );
		syslog(LOG_INFO,"Error al establecer los parametros de la terminal \n" );
		exit( EXIT_FAILURE );
	}
//Retorna el descriptor de archivo
	return fd;
}
void insert_voltaje(char *voltaje)
{
  
	//printf("\nSe insertara = %s\n",voltaje);
	syslog(LOG_INFO,"\nSe insertara = %s\n",voltaje);
	MYSQL *con;

	char *server="localhost";
	char *user="TT";
	char *pass="TT";
	char *database="tornasol";

	con=mysql_init(NULL);
	if(!mysql_real_connect(con,server,user,pass,database,0,NULL,0))
	{
		//fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	if (mysql_query(con, voltaje)) 
	{
		mysql_error(con);
	}
	//else printf("\nInsertamos en la base y consultamos nuevo registro\n");


	mysql_close(con);  
}

double mysql_corriente_bateria()
{
	
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row; 	 	


	char *server="localhost";
	char *user="TT";
	char *pass="TT";
	char *database="tornasol";
	
	con=mysql_init(NULL);
	if(!mysql_real_connect(con,server,user,pass,database,0,NULL,0))
	{
		//fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	if(mysql_query(con,"select b.corriente from historial_bateria_panel hbp,bateria b where hbp.id_bateria=b.id_bateria and hbp.activo=1"))
	{
		//fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			//printf("%s\n",row[0]);
			 syslog(LOG_INFO,"%s\n",row[0]);
			 dato=atof(row[0]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}




void hexadecimal_a_voltaje(int voltaje_alto,int voltaje_bajo)
{
  
  voltaje_mysql=(double) voltaje_alto;
  voltaje_mysql+=(double) voltaje_bajo/100;
  //printf("\nVoltaje médido  :  %lf\n",voltaje_mysql);
  syslog(LOG_INFO,"\nVoltaje médido  :  %lf\n",voltaje_mysql);
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
  //corriente_mysql_descarga_temporal=corriente_mysql_descarga;
   //printf("\nCorriente médida  :  %lf\n",corriente_mysql);
   syslog(LOG_INFO,"\nCorriente médida  :  %lf\n",corriente_mysql);

  
   
  
  
  int valor=0;
  valor=corriente_alto;
  
 /* 
  En la parte de corriemiento para que unamos la parte alta y baja de los datos leídos del modulo RS-232
  atraves del módulo UART de la raspberry el cual se va a agregar los siguientes 8 bits .
  
  valor=corriente_alto<<8;
  ¿Porque se usa un or?
	Bueno principalmente para que nuestros datos de corrimiento no se vean afectados ademas que la operacion 
	booleana de or es una suma de numero.
  */
  valor=valor | corriente_bajo;
  //valor=valor & BAJO;
  if(valor <=9)
  {
    syslog(LOG_INFO,"\n-------\t\tCorriente medida especificia--------->\t0.00%d A\n",valor);
    //printf("0.00%d A\n",valor);
  }
  else if(valor <=99)
  {
    syslog(LOG_INFO,"\n-------\t\tCorriente medida especificia--------->\t0.0%d A\n",valor);
    //printf("0.0%d A\n",valor);
  }
  /*
  
  Se hace en el envio de el PIC16F876A es enviar todo el valor pero lo que se hace es mandar
  el dato en hexadecima para despues solo convertirlo en decimal y ese valor sea nuestra corriente
  como en el caso del voltaje.| estado_fase             |

  
  else printf("%d.%d A\n",valor/1000,valor%1000);
  */
}

void hexadecimal_a_corriente_descarga(int corriente_alto,int corriente_bajo)
{
  
  corriente_mysql_descarga=(double)corriente_alto;
  corriente_mysql_descarga+=(double) corriente_bajo/1000;
  corriente_mysql_descarga_temporal=corriente_mysql_descarga;
   //printf("\nCorriente médida  :  %lf\n",corriente_mysql);
   syslog(LOG_INFO,"\nCorriente médida  :  %lf\n",corriente_mysql_descarga_temporal);

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
    //printf("\nTemperatura médida : %lf °C\n",temperatura_mysql);
    syslog(LOG_INFO,"\nTemperatura médida : %lf °C\n",temperatura_mysql);

}


void procesar_datos(int * datos_recibidos_UART,unsigned char dato_envio)
{
  
  switch(dato_envio)
	  { 
		  case 0xE1:
					guardar_datos_voltaje(datos_recibidos_UART);
					break;
		  case 0xE2:
					guardar_datos_bateria(datos_recibidos_UART);
					break;
		  case 0xE3:
					guardar_datos_bateria(datos_recibidos_UART);
					break;
		  default:
					break;
		  
	
		  
	  }
  
 
  
  
}

void guardar_datos_voltaje(int * datos_recibidos_UART)
{
  hexadecimal_a_voltaje(datos_recibidos_UART[0],datos_recibidos_UART[1]);
  hexadecimal_a_corriente_descarga(datos_recibidos_UART[2],datos_recibidos_UART[3]);
  
  /*
   * query de insert en sensadoP
   * 
   * ->   insert into sensadoP values(null,select id_panel from historial_bateria_panel where activo=1,now(),V)
   * 
   * */
  if(voltaje_mysql>=1)
  {
  char temporal[100]={};
  char datos[200]="insert into sensadoP values(null,(select id_panel from historial_bateria_panel where activo=1),now(),";
  sprintf(temporal,"%lf",voltaje_mysql);
  strcat(datos,temporal);	
  strcat(datos,")");
  insert_voltaje(datos);
  }
  
  
  
  
}



void guardar_datos_bateria(int * datos_recibidos_UART)
{
  hexadecimal_a_voltaje(datos_recibidos_UART[0],datos_recibidos_UART[1]);
  hexadecimal_a_corriente(datos_recibidos_UART[2],datos_recibidos_UART[3]);
  hexadecimal_a_temperatura(datos_recibidos_UART[4],datos_recibidos_UART[5]);
  
  /*
  
  -> query de bateria
  * 
  * 	insert into sensadoB values(null,(select id_bateria from historial_bateria_panel where activo=1),now(),V,I,T);

  
  */
  if(voltaje_mysql>=1)
  {
  char temporal[200]={};
  char temporal1[200]={};
  char temporal2[200]={};
  char estado[200]={};
  
  char datos[200]="insert into sensadoB values(null,(select id_bateria from historial_bateria_panel where activo=1),now(),";
  sprintf(temporal,"%lf",voltaje_mysql);
  strcat(datos,temporal);
  strcat(datos,",");
  
  
  sprintf(temporal1,"%lf",corriente_mysql);
  strcat(datos,temporal1);
  strcat(datos,",");
  
  
  
  
  sprintf(temporal2,"%lf",temperatura_mysql);
  strcat(datos,temporal2);
  strcat(datos,",");
  
  
  sprintf(estado,"%d",etapa_de_bateria());
  strcat(datos,estado);
  
  strcat(datos,")");
  insert_voltaje(datos);
  
  
  
  
  char temporal_descarga[200]={};
  char temporal_descarga_corriente[200]={};
  char datos_descaraga[200]="insert into sensadocvd(id_fase_bateria,id_bateria,fecha,voltaje_bateria,corriente) values(null,(select id_bateria from historial_bateria_panel where activo=1),now(),";
  sprintf(temporal_descarga,"%lf",voltaje_mysql);
  strcat(datos_descaraga,temporal_descarga);	
  strcat(datos_descaraga,",");
  sprintf(temporal_descarga_corriente,"%lf",corriente_mysql_descarga_temporal);
  strcat(datos_descaraga,temporal_descarga_corriente);
  
  strcat(datos_descaraga,")");
  insert_voltaje(datos_descaraga);
  
  /*
  char sql_descarga[200]={};
  char sql_temporal1[200]={};
  char datos1[200]="insert into fase_bateria values(null,1,";
  sprintf(sql_descarga,"%lf",corriente_mysql_descarga);
  strcat(datos1,sql_descarga);
  strcat(datos1,",");
  
  
  sprintf(sql_temporal1,"%lf",voltaje_mysql);
  strcat(datos1,sql_temporal1);
  strcat(datos1,")");
  
  
  insert_voltaje(datos1);
  * */
  }
  
  
  
  
  
  
}

int etapa_de_bateria()
{

  int estado_bateria=0;
  double corriente_de_bateria_usada=mysql_corriente_bateria();
  corriente_mysql*=1000;
  //printf("\n Corriente entrante = %lf \n",corriente_mysql); 
  if(corriente_mysql<=0.0)
  {
    estado_bateria=4;
  }
  else if(corriente_de_bateria_usada<=corriente_mysql || corriente_mysql>=corriente_de_bateria_usada/5 || corriente_mysql>=corriente_de_bateria_usada/4)
  {
   estado_bateria=1;
  }
  else if(corriente_mysql<=corriente_de_bateria_usada/20)
  {
    estado_bateria=3;
  }
  else
  {
    estado_bateria=2;
  }
   
  
  return estado_bateria;

}


void guardar_datos_bateria_descarga(int * datos_recibidos_UART)
{
  
  //printf("\n\n\t\tLectura de E3 \n\n");
  syslog(LOG_INFO,"\n\n\t\tLectura de E3 \n\n");
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
  //syslog(LOG_INFO,"\n\nHa pasado un segundo\n");
  espera_de_recepcion=espera_de_recepcion+1;
  }
  else
  {
	  switch(peticion)
	  { 
		  case 0xE1:
					//printf("Error en la lectura del módulo de panel");
					syslog(LOG_INFO,"Error en la lectura del módulo de panel");
					syslog(LOG_INFO,"  ->Reinicie si se desconcto\n");
					//printf("  ->Reinicie si se desconcto\n");
					close( puerto_serial );
					
					sleep(5);
					puerto_serial = config_serial( "/dev/ttyS0", B9600 );
					syslog(LOG_INFO,"\nDescriptor %d\n",puerto_serial);
					write( puerto_serial, &peticion, 1 );
					close( puerto_serial );
					sleep(5);
					break;
		  case 0xE2:
					syslog(LOG_INFO,"Error en la lectura del módulo de batería");
					syslog(LOG_INFO,"  ->Reinicie si se desconcto\n");
					close( puerto_serial );
					sleep(5);
					puerto_serial = config_serial( "/dev/ttyS0", B9600 );
					write( puerto_serial, &peticion, 1 );
					close( puerto_serial );
					sleep(5);
					break;
		  case 0xE3:
					syslog(LOG_INFO,"Error en la lectura del módulo de panel");
					syslog(LOG_INFO,"  ->Reinicie si se desconcto\n");
					close( puerto_serial );
					sleep(5);
					puerto_serial = config_serial( "/dev/ttyS0", B9600 );
					write( puerto_serial, &peticion, 1 );
					close( puerto_serial );
					sleep(5);
					break;
		  default:
					break;
		  
	
		  
	  }
  } 
}
}


void recibir_valores_de_modulos(unsigned char dato_envio)
{
	syslog(LOG_INFO,"Entre");
	
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
	syslog(LOG_INFO,"\nDescriptor %d\n",puerto_serial);
	 										/*
												Al llamar a la función de config_serial esta nos puede devolver
												 -Error al abrir el dispositivo
												 -Error del baudaje
												 -Error al tratar de leer los datos sin conectar( Valida si manda
												 o no manda mensaje o si quiera si esta conectado)
												 -


	 										*/
	//printf("serial abierto con descriptor: %d\n", puerto_serial);
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
		syslog(LOG_INFO,"Esperando Datos");
		write( puerto_serial, &dato_envio, 1 );
											/*
											En la parte del write enviamos el dato de referencia de la variable
											la cual el RS-232 la recibira atraves de nuestro conmutador
											*/
		//printf("0x%X\n", dato_envio);
		
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
				//printf("dato_recibido no valido\n");
				
				close(puerto_serial);
				sleep(5);
				puerto_serial = config_serial( "/dev/ttyS0", B9600 );
				//printf("serial abierto con descriptor: %d\n", puerto_serial);
				syslog(LOG_INFO,"serial abierto con descriptor: %d\n", puerto_serial);
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
				//printf("Comenzando Transmición  %X\n",dato_recibido);
				syslog(LOG_INFO,"Comenzando Transmición  %X\n",dato_recibido);
				espera_de_recepcion=0;
			}
			/*
			Si el valor iniciar es C1 y ademas nuestra validación es cero esto nos indica que la conexion no se
			esta estableciendo correctamenta la cual se hace un comienzo de datos en esta parte la apertura no es 
			la indicada la cual se cierra el puerto para volver a sincronizar los datos.
			*/
			else if( dato_recibido != 193 && validacion == 0)
			{
				//printf("Error en lectura de dato_recibidos %X\n",dato_recibido);
				syslog(LOG_INFO,"Error en lectura de dato_recibidos %X\n",dato_recibido);
				close(puerto_serial);
				sleep(5);
				puerto_serial = config_serial( "/dev/ttyS0", B9600 );
				//printf("serial abierto con descriptor: %d\n", puerto_serial);
				syslog(LOG_INFO,"serial abierto con descriptor: %d\n", puerto_serial);
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
				procesar_datos(datos_recibidos_UART,dato_envio);
				bandera_de_salida=1;
				//printf("Terminando Trasmición %X\n",dato_recibido);
				syslog(LOG_INFO,"Terminando Trasmición %X\n",dato_recibido);
				espera_de_recepcion=0;
			}
			/*
			Si el valor iniciar no es  C2 y ademas nuestra validación es siete esto nos indica que la conexion no se
			esta terminando la cual se hace un final de conexion
			*/
			else if( dato_recibido != 194 && validacion == 7 )
			{
				//printf("Error al finalizar Trasmición %X\n",dato_recibido);
				syslog(LOG_INFO,"Error al finalizar Trasmición %X\n",dato_recibido);
				close(puerto_serial);
				sleep(5);
				puerto_serial = config_serial( "/dev/ttyS0", B9600 );
				//printf("serial abierto con descriptor: %d\n", puerto_serial);
				syslog(LOG_INFO,"serial abierto con descriptor: %d\n", puerto_serial);
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
		usleep(500000);
		if(bandera_de_salida==1)
		{
		break;
		}
		//printf("--->finaliza la transmision\n");
	}
	close( puerto_serial );
	
}



void demonio()
{

FILE *apArch;

    pid_t pid = 0;
    pid_t sid = 0;
// Se crea el proceso hijo
    pid = fork();
    if( pid == -1 )
    {
		perror("Error al crear el primer proceso hijo\n");
		exit(EXIT_FAILURE);
    }
/*
 * Se termina Proceso padre.
 * Al finalizar el proceso padre el proceso hijo es adoptado por init. 
 * El resultado es que la shell piensa que el comando terminó con éxito, 
 * permitiendo que el proceso hijo se ejecute de manera independiente en segundo plano.
 */
    if( pid )
    {
		printf("Se termina proceso padre, PID del proceso hijo %d \n", pid);
		exit(0);
    }
/* Se restablece el modo de archivo
 * Todos los procesos tiene una máscara que indica que permisos no deben establecerse al crear nuevos archivos. 
 * Así cuando se utilizan llamadas al sistema como open() los permisos especificados se comparan con esta máscara, 
 * desactivando de manera efectiva los que en ella se indiquen.
 * La máscara —denominada umask()— es heredada de padres a hijos por los procesos, por lo que su valor por defecto 
 * será el mismo que el que tenía configurada la shell que lanzó el demonio. Esto significa que el demonio no sabe 
 * que permisos acabarán tenido los archivos que intente crear. Para evitarlo simplemente podemos autorizar todos 
 * los permisos 
 */
    umask(0);
/*
 * se inicia una nueva sesion
 * Cada proceso es miembro de un grupo y estos a su vez se reúnen en sesiones. En cada una de estas hay un proceso 
 * que hace las veces de líder, de tal forma que si muere todos los procesos de la sesión reciben una señal SIGHUP.
 * La idea es que el líder muere cuando se quiere dar la sesión por terminada, por lo que mediante SIGHUP se 
 * notifica al resto de procesos esta circunstancia para que puedan terminar ordenadamente.
 * Obviamente no estamos interesados en que el demonio termine cuando la sesión desde la que fue creado finalice, 
 * por lo que necesitamos crear nuestra propia sesión de la que dicho demonio será el líder.
 */
    sid = setsid();
    if( sid < 0 )
    {
		perror("Error al iniciar sesion");
		exit(EXIT_FAILURE);
    }
// Se realiza un segundo fork para separarnos completamente de la sesion del padre
    pid = fork( );
    if( pid == -1 )
    {
		perror("Error al crear el segundo proceso hijo\n");
		exit(EXIT_FAILURE);
    }
    if( pid )
    {
		printf("PID del segundo proceso hijo %d \n", pid);
		apArch = fopen("/home/pi/UARTDATOS.pid", "w");
		fprintf(apArch, "%d", pid);
		fclose(apArch);

		exit(0);
    }
/* 
 * Se cambia el directorio actual por root.
 * Hasta el momento el directorio de trabajo del proceso es el mismo que el de la shell en el momento en el
 * que se ejecutó el comando. Este podría estar dentro de un punto de montaje cualquiera del sistema, por lo
 * que no tenemos garantías de que vaya a seguir estando disponible durante la ejecución del proceso.
 * Por eso es probable que prefiramos cambiar el directorio de trabajo al directorio raíz, ya que podemos
 * estar seguros de que siempre existirá
 */
    chdir("/");
/*
 * Se cierran los flujos de entrada y salida: stdin, stdout, stderr
 * Puesto que un demonio se ejecuta en segundo plano no debe estar conectado a ninguna terminal. 
 * Sin embargo esto plantea la cuestión de cómo indicar condiciones de error, advertencias u otro 
 * tipo de sucesos del programa. Algunos demonios almacenan estos mensajes en archivos específicos 
 * o en su propia base de datos de sucesos. Sin embargo en muchos sistemas existe un servicio especifico 
 * para registrar estos eventos. En lo sistemas basados en UNIX este servicio lo ofrece el demonio Syslog, 
 * al que otros procesos pueden enviar mensajes a través de la función syslog()
 */
    close( STDIN_FILENO  );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );
// Se abre un archivo log en modo de escritura.
    openlog( "UARTDATOS", LOG_NDELAY | LOG_PID, LOG_LOCAL0 );

    
    closelog( );


}
