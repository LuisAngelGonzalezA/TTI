/*
 * 
 * compilar como
 * 
 * 
 * 			gcc movimiento_servo_de_servo.c -o servo `mysql_config --cflags` `mysql_config --libs`
 * 
 * 
 * 
 * 
 * 
 * */






#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <mysql/mysql.h>
#include <wiringPi.h>
#include <pthread.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>

/*---------Funciones de lógica de servo-----------*/
short existe(char *fname);
double mysql_voltaje();
void recalcular();
void guardar_datos(int x,int y);
void recalcular_y();
void recalcular_x();

/*---------Funciones de servo---------------------*/
int posicion_panel(int grado);
void * movimiento_x(void *arg);
void * movimiento_y(void *arg);


void demonio();

double voltaje_mayor_y,voltaje_mayor_x;
int grados_dados=10;
int grado_x,grados_y;
int divisor = 390;
int range = 1024;
int tiempo_espera=1;


int main()
{
	demonio(); 
	
	wiringPiSetupGpio();

	pinMode(13,PWM_OUTPUT);
	pinMode(19,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(divisor);
	pwmSetRange(range);
	pthread_t tids[2];

	pthread_create(&tids[0],NULL,movimiento_x,NULL);
	pthread_create(&tids[1],NULL,movimiento_y,NULL);

	char *archivo="/home/pi/TTI/TTI/servo/hilo_servo/logica_movimiento_servo/archivo.txt";
	int archivo_exixte=existe(archivo);

	
	if(archivo_exixte==0){
		/*Existe el archivo se inicializo al comienzo del inicio del sistema o incluso al inicio del horario
		 * destinado para el comienzo, entonces se puede realizar la busqueda para una posición adecuada
		 * para obtener una mayor irradiación posible*/
		FILE *fichero=fopen(archivo,"r");
		int posicion_servo_x=0.0,posicion_servo_y=0.0;
		if(fichero>0){//Si el fichero se abre mal devuelve NULL
	    
			//printf("	File Open\n");
			syslog(LOG_INFO,"	File Open\n");
			int i=0;
			char lectura[100]={};
			syslog(LOG_INFO,"	File Open2\n");
		
			while(!feof(fichero)){//Esperamos el fin del fichero
				//Leemos el fichero y lo printamos
				//printf("-->%s", fgets(lectura, 99, fichero));
				syslog(LOG_INFO,("-->%s", fgets(lectura, 99, fichero)));
				if(i==0)
				{
					//sscanf(lectura,"%f",&voltaje_ingresado);
					posicion_servo_x=(int)atof(lectura);
					i++;
				}
				else if(i==1) 
				{	
					//sscanf(lectura,"%f",&voltaje_deseado);
					posicion_servo_y=(int)atof(lectura);
	
	
					i++;
				}
				syslog(LOG_INFO,"	File Open3\n");	
			}
			if(i<2)
			{
				posicion_servo_x=0.0;
				posicion_servo_y=0.0;
				//printf("\n\nError faltan datos\n");
				
			}

	}else{
	    posicion_servo_x=0.0;
		posicion_servo_y=0.0;
	    //printf("File not Open\n");
	    //syslog(LOG_INFO,"File not Open");
	}
	
	//printf("\nValores obtenidos del archvio son %d\n",posicion_servo_x);
	//printf("\nValores obtenidos del archvio son %d\n",posicion_servo_y);
	syslog(LOG_INFO,"\nvalores grados   %d:%d",grado_x,grados_y);
	grado_x=posicion_servo_x;
	grados_y=posicion_servo_y;
	fclose(fichero);
	sleep(1);
	recalcular();
	}
	
	
	

	
}


short existe(char *fname)
{
	int fd=open(fname,O_RDONLY);
	if(fd<0)
		return (errno==ENOENT)?-1:-2;
	return 0; 
	
	
	
	
	return 0;
}



double mysql_voltaje()
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

	if(mysql_query(con,"select *,now()from sensadoP where hora between (now() -INTERVAL 40 SECOND) and (now()) order by hora desc limit 1"))
	{
		//fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			//printf("%s\n",row[3]);
			 dato=atof(row[3]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}


void recalcular_y()
{
	//printf("\nCalculando parte de y\n");
	syslog(LOG_INFO,"	File Open\n");
	double voltaje_referencia=mysql_voltaje(),voltaje_positivo_max,voltaje_negativo_max;
	int posicion_temporal_y_positiva=grados_y,posicion_temporal_y_negativa=grados_y;
	int bandera1=0,bandera2=0,bandera3=0,bandera4=0;
	double voltaje_temporal;
	if(posicion_temporal_y_positiva<180)
	{
		posicion_temporal_y_positiva=posicion_temporal_y_positiva+grados_dados;
		if(posicion_temporal_y_positiva>=180)
		{
			bandera2=1;
			posicion_temporal_y_positiva=180;
		}
	}
	else 
	{
		bandera1=1;
		posicion_temporal_y_positiva=180;
	}
	grados_y=posicion_temporal_y_positiva;
	sleep(tiempo_espera);
	while(1)
	{
		voltaje_temporal=mysql_voltaje();
		sleep(tiempo_espera);
		//printf("\nValore de comparación   %f :: %f\n",voltaje_temporal,voltaje_referencia);
		
		if(voltaje_temporal>voltaje_referencia )
		{	
			
			
			if(posicion_temporal_y_positiva>=180)
			{
				voltaje_referencia=voltaje_temporal;
				//printf("\nSe llegó al limite del panel en y : 180\n");
				posicion_temporal_y_positiva=180;
				grados_y=posicion_temporal_y_positiva;
				bandera3=1;
			}
			else
			{
				bandera4=1;
				voltaje_referencia=voltaje_temporal;
				//printf("\nValores censados  positivos %d  <-> %d\n",grado_x,posicion_temporal_y_positiva);

				posicion_temporal_y_positiva=posicion_temporal_y_positiva+grados_dados;
				if(posicion_temporal_y_positiva>=180)
				{
					posicion_temporal_y_positiva=180;
				}
				grados_y=posicion_temporal_y_positiva;
				sleep(tiempo_espera);
			}
		}
		else if(voltaje_referencia>=voltaje_temporal)
		{	
			voltaje_positivo_max=voltaje_referencia;
			
			if(bandera1==1)
			{
				posicion_temporal_y_positiva=posicion_temporal_y_positiva;
				
			}
			else if(bandera2==1 && bandera3==1)
			{
				
				posicion_temporal_y_positiva=posicion_temporal_y_positiva;
				
			}
			else if(bandera2==1)
			{
				posicion_temporal_y_positiva=posicion_temporal_y_positiva-grados_dados;
				
			}
			else if(bandera4==1 && bandera3==1)
			{
				posicion_temporal_y_positiva=posicion_temporal_y_positiva;
			}
			else if(bandera4==4)
			{
				posicion_temporal_y_positiva=posicion_temporal_y_positiva-grados_dados;
				
			}
			else
			{
				posicion_temporal_y_positiva=posicion_temporal_y_positiva-grados_dados;
			}
			//printf("\n-->Fin--- El voltaje máximo obtenido es =%f con las posiciones x:%d <=> y:%d\n",voltaje_positivo_max,grado_x,posicion_temporal_y_positiva );
			break;
			
		}	
	}//while de positivo
	bandera1=0;bandera2=0;bandera3=0;bandera4=0;
	//printf("\nCensando parte negativa\n");
	grados_y=posicion_temporal_y_negativa;
	sleep(tiempo_espera);
	voltaje_referencia=mysql_voltaje();
	sleep(1);

	if(posicion_temporal_y_negativa>0)
	{
		posicion_temporal_y_negativa=posicion_temporal_y_negativa-grados_dados;
		if(posicion_temporal_y_negativa<0)
		{
			posicion_temporal_y_negativa=0;
			bandera2=1;
		}
	}
	else
	{
		posicion_temporal_y_negativa=0;
		bandera1=1;
	}
	grados_y=posicion_temporal_y_negativa;
	sleep(1);
	while(1)
	{
		voltaje_temporal=mysql_voltaje();
		sleep(1);
		//printf("\nValore de comparación   %f :: %f\n",voltaje_temporal,voltaje_referencia);
		
		if(voltaje_temporal>voltaje_referencia )
		{	
			
			
			if(posicion_temporal_y_negativa<0)
			{
				voltaje_referencia=voltaje_temporal;
				//printf("\nSe llegó al limite del panel en y : 0\n");
				posicion_temporal_y_negativa=0;
				grados_y=posicion_temporal_y_negativa;
				sleep(tiempo_espera);
				bandera3=1;
			}
			else
			{
				bandera4=1;
				voltaje_referencia=voltaje_temporal;
				//printf("\nValores censados  positivos %d  <-> %d\n",grado_x,posicion_temporal_y_negativa);

				posicion_temporal_y_negativa=posicion_temporal_y_negativa-grados_dados;
				if(posicion_temporal_y_negativa<0)
				{
					posicion_temporal_y_negativa=0;
				}
				grados_y=posicion_temporal_y_negativa;
				sleep(tiempo_espera);
			}
		}
		else if(voltaje_referencia>=voltaje_temporal)
		{	
			voltaje_negativo_max=voltaje_referencia;
			/*if(bandera1==1)
			{
				posicion_temporal_y_negativa=posicion_temporal_y_negativa;
				
			}
			else if(bandera2==1 && bandera3==1)
			{
				
				posicion_temporal_y_negativa=posicion_temporal_y_negativa;
				
			}
			else if(bandera2==1)
			{
				posicion_temporal_y_negativa=posicion_temporal_y_negativa-grados_dados;
				
			}
			else if(bandera4==1 && bandera3==1)
			{
				posicion_temporal_y_negativa=posicion_temporal_y_negativa;
			}
			else if(bandera4==4)
			{
				posicion_temporal_y_negativa=posicion_temporal_y_negativa-grados_dados;
				
			}
			else
			{
				posicion_temporal_y_negativa=posicion_temporal_y_negativa+grados_dados;
			}*/
			//printf("\n-->fin negativo El voltaje máximo obtenido es =%f con las posiciones x:%d <=> y:%d\n",voltaje_negativo_max,grado_x,posicion_temporal_y_negativa );
			syslog(LOG_INFO,"\n-->fin negativo El voltaje máximo obtenido es =%f con las posiciones x:%d <=> y:%d\n",voltaje_negativo_max,grado_x,posicion_temporal_y_negativa );
			break;
			
		}	
	}//while de negativo


	if(voltaje_positivo_max>voltaje_negativo_max)
	{
		grados_y=posicion_temporal_y_positiva;
		
	}
	else if(voltaje_negativo_max>voltaje_positivo_max)
	{
		grados_y=posicion_temporal_y_negativa;
	}
	else
	{
		grados_y=posicion_temporal_y_positiva;
	}

	sleep(tiempo_espera);
	//printf("\n\n ----------------Los valores que se obtuvieron son x : %d    y : %d\n\n",grado_x,grados_y);
	syslog(LOG_INFO,"\n\n ----------------Los valores que se obtuvieron son x : %d    y : %d\n\n",grado_x,grados_y);
	
	
}


void recalcular_x()
{
	//printf("\nCalculando parte de x\n");
	syslog(LOG_INFO,"\nCalculando parte de x\n");
	double voltaje_referencia=mysql_voltaje(),voltaje_positivo_max,voltaje_negativo_max;
	int posicion_temporal_x_positiva=grado_x,posicion_temporal_x_negativa=grado_x;
	int bandera1=0,bandera2=0,bandera3=0,bandera4=0;
	double voltaje_temporal;
	if(posicion_temporal_x_positiva<180)
	{
		posicion_temporal_x_positiva=posicion_temporal_x_positiva+grados_dados;
		if(posicion_temporal_x_positiva>=180)
		{
			posicion_temporal_x_positiva=180;
			bandera2=1;
		}
	}
	else
	{
		posicion_temporal_x_positiva=180;
		bandera1=1;
	}
	grado_x=posicion_temporal_x_positiva;
	sleep(tiempo_espera);
	while(1)
	{
		voltaje_temporal=mysql_voltaje();
		sleep(1);
		//printf("\nValore de comparación   %f :: %f\n",voltaje_temporal,voltaje_referencia);
		
		if(voltaje_temporal>voltaje_referencia )
		{	
			
			
			if(posicion_temporal_x_positiva>=180)
			{
				voltaje_referencia=voltaje_temporal;
				//printf("\nSe llegó al limite del panel en y : 180\n");
				posicion_temporal_x_positiva=180;
				grado_x=posicion_temporal_x_positiva;
				bandera3=1;
				sleep(tiempo_espera);
			}
			else
			{
				bandera4=1;
				voltaje_referencia=voltaje_temporal;
				//printf("\nValores censados  positivos %d  <-> %d\n",posicion_temporal_x_positiva,grados_y);

				posicion_temporal_x_positiva=posicion_temporal_x_positiva+grados_dados;
				if(posicion_temporal_x_positiva>=180)
				{
					posicion_temporal_x_positiva=180;
				}
				grado_x=posicion_temporal_x_positiva;
				sleep(tiempo_espera);
			}
		}
		else if(voltaje_referencia>=voltaje_temporal)
		{	
			voltaje_positivo_max=voltaje_referencia;
			if(bandera1==1)
			{
				posicion_temporal_x_positiva=posicion_temporal_x_positiva;
				
			}
			else if(bandera2==1 && bandera3==1)
			{
				
				posicion_temporal_x_positiva=posicion_temporal_x_positiva;
				
			}
			else if(bandera2==1)
			{
				posicion_temporal_x_positiva=posicion_temporal_x_positiva-grados_dados;
				
			}
			else if(bandera4==1 && bandera3==1)
			{
				posicion_temporal_x_positiva=posicion_temporal_x_positiva;
			}
			else if(bandera4==4)
			{
				posicion_temporal_x_positiva=posicion_temporal_x_positiva-grados_dados;
				
			}
			else
			{
				posicion_temporal_x_positiva=posicion_temporal_x_positiva-grados_dados;
			}
			//printf("\n-->Fin El voltaje máximo obtenido es =%f con las posiciones x:%d <=> y:%d\n",voltaje_positivo_max,posicion_temporal_x_positiva,grados_y);
			syslog(LOG_INFO,"\n-->Fin El voltaje máximo obtenido es =%f con las posiciones x:%d <=> y:%d\n",voltaje_positivo_max,posicion_temporal_x_positiva,grados_y);
			break;
			
		}	
	}//while de positivo
	bandera1=0;bandera2=0;bandera3=0;bandera4=0;
	//printf("\nCensando parte negativa\n");
	syslog(LOG_INFO,"\nCensando parte negativa\n");
	grado_x=posicion_temporal_x_negativa;
	sleep(tiempo_espera);
	voltaje_referencia=mysql_voltaje();
	sleep(1);

	if(posicion_temporal_x_negativa>0)
	{
		posicion_temporal_x_negativa=posicion_temporal_x_negativa-grados_dados;
		if(posicion_temporal_x_negativa<0)
		{
			posicion_temporal_x_negativa=0;
			bandera2=1;
		}
	}
	else
	{
		bandera1=1;
		posicion_temporal_x_negativa=0;
	}
	grado_x=posicion_temporal_x_negativa;
	sleep(tiempo_espera);
	while(1)
	{
		voltaje_temporal=mysql_voltaje();
		sleep(1);
		//printf("\nValore de comparación   %f :: %f\n",voltaje_temporal,voltaje_referencia);
		
		if(voltaje_temporal>voltaje_referencia )
		{	
			
			
			if(posicion_temporal_x_negativa<0)
			{
				voltaje_referencia=voltaje_temporal;
				//printf("\nSe llegó al limite del panel en y : 0\n");
				posicion_temporal_x_negativa=0;
				grado_x=posicion_temporal_x_negativa;
				bandera3=1;
				sleep(tiempo_espera);
				
			}
			else
			{
				bandera4=1;
				voltaje_referencia=voltaje_temporal;
				//printf("\nValores censados  positivos %d  <-> %d\n",posicion_temporal_x_negativa,grados_y);

				posicion_temporal_x_negativa=posicion_temporal_x_negativa-grados_dados;
				if(posicion_temporal_x_negativa<0)
				{
					posicion_temporal_x_negativa=0;
				}
				grado_x=posicion_temporal_x_negativa;
				sleep(tiempo_espera);
			}
		}
		else if(voltaje_referencia>=voltaje_temporal)
		{	
			
			voltaje_negativo_max=voltaje_referencia;
			/*if(bandera1==1)
			{
				posicion_temporal_x_negativa=posicion_temporal_x_negativa;
				
			}
			else if(bandera2==1 && bandera3==1)
			{
				
				posicion_temporal_x_negativa=posicion_temporal_x_negativa;
				
			}
			else if(bandera2==1)
			{
				posicion_temporal_x_negativa=posicion_temporal_x_negativa-grados_dados;
				
			}
			else if(bandera4==1 && bandera3==1)
			{
				posicion_temporal_x_negativa=posicion_temporal_x_negativa;
			}
			else if(bandera4==4)
			{
				posicion_temporal_x_negativa=posicion_temporal_x_negativa+grados_dados;
				
			}
			else
			{
				posicion_temporal_x_negativa=posicion_temporal_x_negativa+grados_dados;
			}*/
			//printf("\n-->Fin El voltaje máximo obtenido es =%f con las posiciones x:%d <=> y:%d\n",voltaje_negativo_max,posicion_temporal_x_negativa,grados_y);
			syslog(LOG_INFO,"\n-->Fin El voltaje máximo obtenido es =%f con las posiciones x:%d <=> y:%d\n",voltaje_negativo_max,posicion_temporal_x_negativa,grados_y);
			break;
			
		}	
	}//while de negativo


	if(voltaje_positivo_max>voltaje_negativo_max)
	{
		grado_x=posicion_temporal_x_positiva;
		
	}
	else if(voltaje_negativo_max>voltaje_positivo_max)
	{
		grado_x=posicion_temporal_x_negativa;
	}
	else
	{
		grado_x=posicion_temporal_x_positiva;
	}
	sleep(tiempo_espera);
	//printf("\n\n ----------------Los valores que se obtuvieron son x : %d    y : %d\n\n",grado_x,grados_y);
	syslog(LOG_INFO,"\n\n ----------------Los valores que se obtuvieron son x : %d    y : %d\n\n",grado_x,grados_y);
	
}
void recalcular()
{
	while(1)
	{

		recalcular_y();
		sleep(tiempo_espera);
		recalcular_x();
		guardar_datos(grado_x,grados_y);
	}
	
	
	
}

void guardar_datos(int x,int y)
{
	//printf("\nGuardando\n");
	FILE *fichero;
	char lectura[100];
	fichero=fopen("/home/pi/Desktop/archivo.txt","wt"); //Abrimos el fichero para solo lectura
	sprintf(lectura,"%d\n%d",x,y);
	fputs(lectura,fichero);
	fclose(fichero);
	usleep(1000000);

}



int posicion_panel(int grado)
{
	int posicion=(.522*grado)+29;
	return posicion;
}

void * movimiento_x(void *arg)
{
  while(1)
  {
    int posicion=posicion_panel(grado_x);
    pwmWrite(13,posicion);
    //usleep(1000000);
    sleep(1);
  }
}
void * movimiento_y(void *arg)
{
  while(1)
  {
    int posicion=posicion_panel(grados_y);
    //syslog(LOG_INFO,"\tRecalcular la ecuacion: \tgrados=%d  --  pwm %d\n",posicion,grados_y);
    pwmWrite(19,posicion);
    usleep(1000000);
    sleep(1);
  }
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
		apArch = fopen("/home/pi/servo_prueba.pid", "w");
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
    openlog( "servo_prueba", LOG_NDELAY | LOG_PID, LOG_LOCAL0 );

    
    closelog( );


}
