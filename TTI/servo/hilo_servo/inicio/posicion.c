/** @brief: Este programa configura el BCM_GPIO 17 usando la libreria wiringPi
 * El GPIO 17 corresponde con el pin 0 en wiring Pi
 * Se debe compilar con: gcc gpio.c -o gpio -lwiringpi
 * 
 * 
 * 
 * 
 * 
 * 
 * 	gcc reeles.c -o reeles -lm -lwiringPi `mysql_config --cflags` `mysql_config --libs`
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <string.h>
#include <mysql/mysql.h>
#include <sys/types.h>
#include <sys/stat.h>

void demonio();
double formatear();
void guardar_datos(int x,int y);
void guardar_datos_validar(int x);
int main( )
{
	demonio();
	
			syslog(LOG_INFO,"\n-->Estado actual ---%lf \n",formatear());
			//digitalWrite( 2,1 );
			//usleep(100000);
			sleep(1);
			char lectura[100]={};
			FILE *fichero=fopen("/home/luis/TTI/TTI/servo/hilo_servo/inicio/validar.txt","r");
			syslog(LOG_INFO,"-->%s", fgets(lectura, 99, fichero));
			int estado=(int)atof(lectura);
			syslog(LOG_INFO,"\n-->valor ya leido : %d",estado);
			int i=0;
			for(;i<2;i++)
			{
				if(estado==0)
				{
					guardar_datos(170,90);
					estado=1;	
				}
				else
				{
					if(!formatear())
					{
						estado=0;

					}
				}
			}
			fclose(fichero);
			guardar_datos_validar(estado);
	
	
}


void guardar_datos_validar(int x)
{
	//printf("\nGuardando\n");
	FILE *fichero;
	char lectura[100];
	fichero=fopen("/home/luis/TTI/TTI/servo/hilo_servo/inicio/validar.txt","wt"); //Abrimos el fichero para solo lectura
	sprintf(lectura,"%d",x);
	fputs(lectura,fichero);
	fclose(fichero);
	usleep(1000000);

}

void guardar_datos(int x,int y)
{
	//printf("\nGuardando\n");
	FILE *fichero;
	char lectura[100];
	fichero=fopen("/home/luis/TTI/TTI/servo/hilo_servo/logica_movimiento_servo/archivo.txt","wt"); //Abrimos el fichero para solo lectura
	sprintf(lectura,"%d\n%d",x,y);
	fputs(lectura,fichero);
	fclose(fichero);
	usleep(1000000);

}




double formatear()
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

	if(mysql_query(con,"select curTime() between '07:00:00' and '12:43:20'; "))
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
			 dato=atof(row[0]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
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
		apArch = fopen("/home/luis/inicio.pid", "w");
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
    openlog( "inicio", LOG_NDELAY | LOG_PID, LOG_LOCAL0 );

    
    closelog( );


}
