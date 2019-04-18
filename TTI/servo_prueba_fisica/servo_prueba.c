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
#include <pthread.h>
int grado,grados_y;

int divisor = 390;
int range = 1024;



int posicion_panel(int grado);
void * movimiento_x(void *arg);
void * movimiento_y(void *arg);
void demonio();


int main(int argc, char* argv[])
{
  demonio();
  wiringPiSetupGpio();

  pinMode(19,PWM_OUTPUT);
  pinMode(13,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(divisor);
  pwmSetRange(range);

  pthread_t tids[2];

  pthread_create(&tids[0],NULL,movimiento_x,NULL);
  pthread_create(&tids[1],NULL,movimiento_y,NULL);

  //pthread_join(tids,NULL);
  for(;1;) {
    sleep(5);
    }
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
    //int posicion=posicion_panel(grado);
    syslog(LOG_INFO,"\nEmpieza servo en x con uno menor");
    pwmWrite(19,0);
    sleep(1);
    syslog(LOG_INFO,"\nEmpieza servo en x con uno medio");
    pwmWrite(19,512);
    sleep(1);
    syslog(LOG_INFO,"\nEmpieza servo en x con uno mayor");
    pwmWrite(19,1024);
    sleep(1);
    pwmWrite(19,512);
    sleep(1);
    pwmWrite(19,0);
    sleep(1);
  }
}
void * movimiento_y(void *arg)
{
  while(1)
  {
      syslog(LOG_INFO,"\nEmpieza servo en y con uno menor");
    pwmWrite(13,0);
    sleep(1);
    syslog(LOG_INFO,"\nEmpieza servo en y con uno menor");
    pwmWrite(13,512);
    sleep(1);
    syslog(LOG_INFO,"\nEmpieza servo en y con uno menor");
    pwmWrite(13,1024);
    sleep(1);
    pwmWrite(13,512);
    sleep(1);
    pwmWrite(13,0);
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





