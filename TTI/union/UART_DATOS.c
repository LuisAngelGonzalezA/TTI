#include <stdio.h>
#include <wiringPi.h>
#include <math.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>
#include <mysql/mysql.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "iniciar_serial.h" /*Mandamos a llamar la funcion de config_serial para posteriormente hacer la
							  conexion de el puerto ttyS0*/
#include <pthread.h>
#include "def.h" 			/*Mandamos a llamar el dato de Ever*/


void * carga(void *arg);
void * reles_activos(void *arg);
void * reiniciar(void *arg);
void demonio();
double mysql_voltaje();
double mysql_voltaje_bateria();
double mysql_voltaje_panel();
double mysql_voltaje_bateria_reeles();
double mysql_voltaje_bateria_max();
double mysql_voltaje_bateria_min();



unsigned char peticion;
int espera_de_recepcion;
int main()
{                             
	demonio();                
	espera_de_recepcion=0;
	pthread_t tids[4];
	int i=0;
    pthread_create(&tids[0],NULL,espera,NULL);
    pthread_create(&tids[1],NULL,carga,NULL);
    pthread_create(&tids[2],NULL,reles_activos,NULL);
    pthread_create(&tids[3],NULL,reiniciar,NULL);

    while(EVER)
    {
			i=0;

			
			
			
			peticion= 0xE1;
			for(;i<2;i++)
			 {
				//printf("\n\n\n\t0x%X\n\n\n",peticion);
				syslog(LOG_INFO,"\n\n\n\t0x%X\n\n\n",peticion);
				
				//printf("0x%X\n", peticion);
				syslog(LOG_INFO,"Entrando");
				recibir_valores_de_modulos(peticion);
				
				
				peticion+=2;
			 }			
	}
	return 0;
}

void * reiniciar(void *arg)
{
	int espera_de_reinicio=0;
	while(1)
  {
  if(espera_de_reinicio>7200)
  {
  //sleep(1);
  syslog(LOG_INFO,"\n\n\n\n\nReiniciando\n\n\n");
  exit(1);
  //printf("\n\nHa pasado un segundo\n");
  //syslog(LOG_INFO,"\n\nHa pasado un segundo\n");

  }
  else{
	 espera_de_reinicio++;
	 syslog(LOG_INFO,"\n\n\n\n\nContador %d\n\n\n",espera_de_reinicio);
	 sleep(1);
	  
	} 
	}
	
	
	
	
}


void * reles_activos(void *arg)
{

	syslog(LOG_INFO,"\n-->Reele---\n");
//Se inicializa la libreria wiring Pi
	wiringPiSetup();
//Se configura el GPIO 17 como salida
	pinMode( 0, OUTPUT );
	pinMode( 2, OUTPUT );
//Se escribe un valor digital al GPIO
	
	double voltaje_panel=0.0,voltaje_bateria=0.0,voltaje_bateria_max=0.0,voltaje_bateria_min=0.0;
	while( 1 )
	{
		
		voltaje_panel=mysql_voltaje_panel();
		voltaje_bateria=mysql_voltaje_bateria_reeles();
		voltaje_bateria_max=mysql_voltaje_bateria_max();
		voltaje_bateria_min=mysql_voltaje_bateria_min();
		
		
		if(voltaje_panel>=voltaje_bateria_max)
		{
			syslog(LOG_INFO,"\n-->Reele cerrado panel---\n");
			digitalWrite( 0,0 );
			//usleep(100000);
			sleep(1);
		}
		else
		{
			syslog(LOG_INFO,"\n-->Reele abierto panel---\n");
			digitalWrite( 0,1 );
			//usleep(100000);
			sleep(1);
		}
		
		
		if(voltaje_bateria>=voltaje_bateria_min)
		{
			syslog(LOG_INFO,"\n-->Reele cerrado Batería---\n");
			digitalWrite( 2,0 );
			//usleep(100000);
			sleep(1);
		}
		else
		{
			syslog(LOG_INFO,"\n-->Reele abierto Batería---\n");
			digitalWrite( 2,1 );
			//usleep(100000);
			sleep(1);
		}
		
	}
}







double mysql_voltaje_panel()
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
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select *,now()from sensadoP where hora between (now() -INTERVAL 10 SECOND) and (now()) order by hora desc limit 1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
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



double mysql_voltaje_bateria_reeles()
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
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select voltaje_bateria from sensadocvd where fecha between (now() -INTERVAL 10 SECOND) and (now()) order by fecha desc limit 1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			//printf("%s\n",row[0]);
			 dato=atof(row[0]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}


double mysql_voltaje_bateria_max()
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
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select b.voltaje_max*b.nu_celdas  from historial_bateria_panel hbp,bateria b where hbp.id_bateria=b.id_bateria and hbp.activo=1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			//printf("%s\n",row[0]);
			 dato=atof(row[0]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}


double mysql_voltaje_bateria_min()
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
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select b.voltaje_min*b.nu_celdas  from historial_bateria_panel hbp,bateria b where hbp.id_bateria=b.id_bateria and hbp.activo=1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			//printf("%s\n",row[0]);
			 dato=atof(row[0]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}




void * carga(void *arg)
{

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
	
	voltaje_ingresado=mysql_voltaje();
	voltaje_deseado=mysql_voltaje_bateria();
	
	
		syslog(LOG_INFO,"\n-->nuevo voltaje---%f\n",voltaje_ingresado);
		syslog(LOG_INFO,"-->nuevo voltaje---%f\n",voltaje_deseado);








        if (voltaje_deseado <= voltaje_ingresado)
            {
            pendiente=((1024-0)/(voltaje_min-voltaje_ingresado));
            
	    syslog(LOG_INFO,"%f\n",pendiente);
            
            b1=(1024.0-pendiente*(voltaje_min));
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
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select *,now()from sensadoP where hora between (now() -INTERVAL 10 SECOND) and (now()) order by hora desc limit 1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
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

double mysql_voltaje_bateria()
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
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select b.voltaje_max*b.nu_celdas  from historial_bateria_panel hbp,bateria b where hbp.id_bateria=b.id_bateria and hbp.activo=1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			//printf("%s\n",row[0]);
			 dato=atof(row[0]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}
