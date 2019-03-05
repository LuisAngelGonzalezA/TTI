/*
 * 
 * Recordar
 * compilar con
 *    gcc -lwiringPi servo_final.c -o servo_final -lpthread `mysql_config --cflags` `mysql_config --libs`

  Guardar el service 
  * /etc/systemd/system/tu servicio
 * 
 * 
 * 
 * 
 * 
*/



#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>

int grado,grados_y;

int divisor = 390;
int range = 1024;


short existe(char *fname);
int posicion_panel(int grado);
void * movimiento_x(void *arg);
void * movimiento_y(void *arg);
void * prueba(void *arg);
void demonio();
void datos_archivo();
int main(int argc, char* argv[])
{
  demonio();
  wiringPiSetupGpio();

  pinMode(18,PWM_OUTPUT);
  pinMode(13,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(divisor);
  pwmSetRange(range);
  datos_archivo();
  pthread_t tids[2];

  pthread_create(&tids[0],NULL,movimiento_x,NULL);
  pthread_create(&tids[1],NULL,movimiento_y,NULL);

  //pthread_join(tids,NULL);
  for(;1;) {
    datos_archivo();
    }
}


int posicion_panel(int grado)
{
	int posicion=(.522*grado)+29;
	return posicion;
}

void * prueba(void *arg)
{
  int i=0;
  for(;1;)
  {
    
  }
  
}

void * movimiento_x(void *arg)
{
  while(1)
  {
    int posicion=posicion_panel(grado);
    pwmWrite(18,posicion);
    usleep(50);
  }
}
void * movimiento_y(void *arg)
{
  while(1)
  {
    int posicion=posicion_panel(grados_y);
    syslog(LOG_INFO,"\tRecalcular la ecuacion: \tgrados=%d  --  pwm %d\n",posicion,grados_y);
    pwmWrite(13,posicion);
    usleep(500);
  }
}


void datos_archivo()
{
  
	char *archivo="/home/pi/Desktop/archivo.txt";
	int archivo_exixte=existe(archivo);
	sleep(1);
	char lectura[100]={};
		/*Existe el archivo se inicializo al comienzo del inicio del sistema o incluso al inicio del horario
		 * destinado para el comienzo, entonces se puede realizar la busqueda para una posición adecuada
		 * para obtener una mayor irradiación posible*/
		FILE *fichero=fopen(archivo,"r");
		
		if(fichero>0){//Si el fichero se abre mal devuelve NULL
	    
			//printf("File Open\n");
			int i=0;
			
			
		
			while(!feof(fichero)){//Esperamos el fin del fichero
				//Leemos el fichero y lo printamos
				syslog(LOG_INFO,"-->%s", fgets(lectura, 99, fichero));
				//printf("-->%s", fgets(lectura, 99, fichero));
				if(i==0)
				{
					//sscanf(lectura,"%f",&voltaje_ingresado);
					grado=(int)atof(lectura);
					i++;
				}
				else if(i==1) 
				{	
					//sscanf(lectura,"%f",&voltaje_deseado);
					grados_y=(int)atof(lectura);
	
	
					i++;
				}	
			}
			if(i<2)
			{
				grado=0.0;
				grados_y=0.0;
				syslog(LOG_INFO,"\n\nError faltan datos\n");
				//printf("\n\nError faltan datos\n");
				
			}

		    }
	
	printf("\nValores obtenidos del archvio son %d",grado);
	printf("\nValores obtenidos del archvio son %d\n",grados_y);	 
	 	 
	fclose(fichero);	
		

}

short existe(char *fname)
{
	int fd=open(fname,O_RDONLY);
	if(fd<0)
	{
		close(fd);
		return (errno==ENOENT)?-1:-2;
	}
	close(fd);
	return 0; 
	
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
		apArch = fopen("/home/pi/demonio_servo_final.pid", "w");
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
    openlog( "demonio_servo_final", LOG_NDELAY | LOG_PID, LOG_LOCAL0 );

    
    closelog( );


}





