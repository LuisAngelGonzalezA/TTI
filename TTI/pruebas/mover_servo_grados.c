/*
 * 
 * Recordar
 * compilar con
 *    gcc -lwiringPi mover_servo_grados.c -o prueba_hora -lpthread `mysql_config --cflags` `mysql_config --libs`

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
#include <mysql/mysql.h>
#include <time.h>
int grado=90,grados_y=90;

int divisor = 390;
int range = 1024;
void mysql();
void * movimiento_x(void *arg);
void * movimiento_y(void *arg);
void * prueba(void *arg);
void demonio();
void mover_servo();
int main(int argc, char* argv[])
{
  demonio();
  wiringPiSetupGpio();

  pinMode(18,PWM_OUTPUT);
  pinMode(13,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(divisor);
  pwmSetRange(range);

  pthread_t tids[2];
  //pthread_create(&tids[0],NULL,prueba,NULL);
  pthread_create(&tids[0],NULL,movimiento_x,NULL);
  pthread_create(&tids[1],NULL,movimiento_y,NULL);

  //pthread_join(tids,NULL);
  for(;;) {
    

    mover_servo();
    }
}

void mover_servo()
{
    time_t t;
  struct tm *tm;
  char fechayhora[100];
  int tiempo_estimado=1;
  int h,m,s;
  int min_bandera;
  t=time(NULL);
  tm=localtime(&t);
  strftime(fechayhora, 100, "%H", tm);
  h=atoi(fechayhora);
  strftime(fechayhora, 100, "%M", tm);
  m=atoi(fechayhora);
  min_bandera=m+tiempo_estimado;
  if(min_bandera>=59)
  {
    min_bandera=min_bandera - 60;
  }
  //else
    
  
  strftime(fechayhora, 100, "%S", tm);
  s=atoi(fechayhora);

  
  syslog(LOG_INFO,"Hoy es: %d : %d : %d\n\n", h,m,s);
  syslog(LOG_INFO,"\nTiempo para acabar = %d  min\n",min_bandera);
 	
  while(1)
 	{
    
  syslog(LOG_INFO,"\nTiempo para acabar = %d  min\n",min_bandera);
  //printf("-->\n");
  t=time(NULL);
  tm=localtime(&t);

      if(m==min_bandera)
     {
 			//printf("\nYa a pasado el tiempo ya volvemos a monitorear\n");
 			syslog(LOG_INFO,"\n Ya a pasado el tiempo ya volvemos a monitorear\n");
      mysql();
      syslog(LOG_INFO,"%d  --  %d\n",grado,grados_y);
      delay(250);
      min_bandera=m+tiempo_estimado;
      if(min_bandera>=59)
      {
        min_bandera=min_bandera - 60;
      }
  
 			
 		}
 		strftime(fechayhora, 100, "%M", tm);
 	 	m=atoi(fechayhora);
    strftime(fechayhora, 100, "%S", tm);
    s=atoi(fechayhora);
 	 	usleep(1000000);
 	 	
    //printf ("\r\t->Hoy es:  %d  :  %d\r", m,s);
    



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
    printf("\n-->%d\n",i);
    i++;
    delay(2000);
  }
  
}

void * movimiento_x(void *arg)
{
  while(1)
  {
    int posicion=posicion_panel(grado);
    pwmWrite(18,posicion);
    delay(1000);
  }
}
void * movimiento_y(void *arg)
{
  while(1)
  {
    int posicion=posicion_panel(grados_y);
    pwmWrite(13,posicion);
    delay(1000);
  }
}

void mysql()
{
  MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;


	char *server="localhost";
	char *user="TT";
	char *pass="TT";
	char *database="tt1Pruebas";
	
	con=mysql_init(NULL);
	if(!mysql_real_connect(con,server,user,pass,database,0,NULL,0))
	{
		//fprintf(stderr, "%s\n", mysql_error(con));
    syslog(LOG_INFO,"%s\n", mysql_error(con));
	}

	/*if(mysql_query(con,"show databases"))
	{
		//fprintf(stderr, "%s\n", mysql_error(con));
    syslog(LOG_INFO,"%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		syslog(LOG_INFO,"%s\n",row[0]);
    //printf("%s\n",row[0]);
  */
    
    
    if(mysql_query(con, "insert into posicion_servo values (1,1,1)")!=0)//,grado,grados_y)!=0)
    {
      syslog(LOG_INFO,"%s\n", mysql_error(con));
      exit(1);
      
    }
  
  
	 if (mysql_query(con, "SELECT * FROM posicion_servo")) 
  {
      mysql_error(con);
  }
  
  res = mysql_store_result(con);
  
  if (res == NULL) 
  {
      mysql_error(con);
  }

  int num_fields = mysql_num_fields(res);
  
  while ((row = mysql_fetch_row(res))) 
  { 
      /*for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
      */
      grado=atoi(row[0]);
      grados_y=atoi(row[1]);
      
  }

	mysql_free_result(res);
	mysql_close(con);

  
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





