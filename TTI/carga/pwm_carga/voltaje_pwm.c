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


void demonio();




int main(int argc, char* argv[])
{
  demonio();

  int div = 390;
  int range = 1024;
  int duty=1024;
  float pendiente=0.0;
  float b1=0.0;
  float b2=0.0;
  float b_a_usar=0.0;

  float voltaje_ingresado=0.0;
  float voltaje_deseado=0.0;
  float voltaje_min=0.0;
  
  
  wiringPiSetupGpio();

  pinMode(12,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(div);
  pwmSetRange(range);
  pwmWrite(12,duty);
  delay(1000);



    while(1)
    {
	
	FILE *fichero;
	
	char lectura[100];
	
	fichero=fopen("/home/pi/Downloads/pwm_carga/archivo.txt","r"); //Abrimos el fichero para solo lectura
	if(fichero>0){//Si el fichero se abre mal devuelve NULL
	    
	    syslog(LOG_INFO, "File Open\n");
	    int i=0;
	
	    while(!feof(fichero)){//Esperamos el fin del fichero
	        //Leemos el fichero y lo printamos
		syslog(LOG_INFO,"-->%s", fgets(lectura, 99, fichero));
		if(i==0)
		{
  			//sscanf(lectura,"%f",&voltaje_ingresado);
			voltaje_ingresado=(float)atof(lectura);
			i++;
		}
		else if(i==1) 
		{	
			//sscanf(lectura,"%f",&voltaje_deseado);
			voltaje_deseado=(float)atof(lectura);
			i++;
		}	
	    }
	    if(i<2)
	    {
		voltaje_ingresado=0.0;
	        voltaje_deseado=0.0;
		syslog(LOG_INFO,"\n\nError faltan datos\n");
	        
	    }

	}else{
	    voltaje_ingresado=0.0;
	    voltaje_deseado=0.0;
	    //printf("File not Open\n");
	    syslog(LOG_INFO,"File not Open");
	}

		syslog(LOG_INFO,"\n-->nuevo voltaje---%f\n",voltaje_ingresado);
		syslog(LOG_INFO,"-->nuevo voltaje---%f\n",voltaje_deseado);








        if (voltaje_deseado <= voltaje_ingresado)
            {
            pendiente=((1024-0)/(voltaje_min-voltaje_ingresado));
            
	    syslog(LOG_INFO,"%f\n",pendiente);
            
            b1=(100.0-pendiente*(voltaje_min));
            syslog(LOG_INFO,"-->%f\n",b1);
	    b2=0-pendiente*(voltaje_ingresado);
            syslog(LOG_INFO,"-->%f\n",b2);
            duty=round(pendiente*(voltaje_ingresado)+(b1));
            syslog(LOG_INFO,"-->%d\n",duty);
            
            if(duty>=0 && duty <= 1)
            {
                
	        syslog(LOG_INFO,"si entro en b1");
		syslog(LOG_INFO,"Duty vale --->%d\n",duty);
                b_a_usar=b1;
            }
            else
            {
                duty=round(pendiente*(voltaje_ingresado)+(b2));
                if(duty>=0 && duty <= 1)
		{
		    syslog(LOG_INFO,"si entro en b2\n");
		    syslog(LOG_INFO,"Duty vale -->%d\n",duty);
                    b_a_usar=b2;
		}
            }
            
                
	    syslog(LOG_INFO,"B a usar -->%f\n",b_a_usar);
            duty=round(pendiente*(voltaje_deseado)+b_a_usar);
            
            if(duty >= 1024)
                duty=1024;
	    syslog(LOG_INFO,"Duty :-->%d\n",duty);
            pwmWrite(12,duty);
            delay(1000);             
            }
        else
	{
	    
	    syslog(LOG_INFO,"No se puede entregar un voltaje superior al de la fuente\n");
	    pwmWrite(12,1024);
            delay(1000);
         
    	}
	//delay(1000);
 
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
		apArch = fopen("/home/pi/demonio.pid", "w");
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
    openlog( "demonio", LOG_NDELAY | LOG_PID, LOG_LOCAL0 );

    
    closelog( );


}



