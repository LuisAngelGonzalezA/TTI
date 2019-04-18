/** @brief: Este programa configura el BCM_GPIO 17 usando la libreria wiringPi
 * El GPIO 17 corresponde con el pin 0 en wiring Pi
 * Se debe compilar con: gcc gpio.c -o gpio -lwiringpi
 */
 
 
/*
 * 
 * gcc gpio.c -o ggpio -lm -lwiringPi `mysql_config --cflags` `mysql_config --libs`
 * ./gpio
 * 
 * */ 

#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <mysql/mysql.h>




double mysql_voltaje();
double mysql_voltaje_bateria();
double mysql_voltaje_bateria_sensado();
int mysql_voltaje_bateria_cierre_abertura();
void * hilo_panel(void *arg);
void * hilo_panel2(void *arg);
int main( )
{
	pthread_t tids[4];
	pthread_create(&tids[0],NULL,hilo_panel,NULL);
	//pthread_create(&tids[1],NULL,hilo_panel2,NULL);
	while( 1 )
	{
		
		
		
	/*	
		double panel=mysql_voltaje(),bateria=mysql_voltaje_bateria();
		printf("\nPanel = %lf  Bateria = %lf \n",panel,bateria);
		if(panel>=bateria)
		{
//Entonces el reelé se cierra
			digitalWrite( 0, LOW );
			printf("\nSe cierra el reelé de panel\n");
		}
		else
		{
			
			digitalWrite( 0, HIGH );
			printf("Se abré el reelé de panel\n");
		}
		
		if(mysql_voltaje_bateria_cierre_abertura())
		{
			printf("\nEl reelé de batería esta cerrado\n");
		}
		else {
			printf("\nEl reelé de batería esta abierto\n");
		}
	*/
	printf("\nSolo espero al hilo\n");
	usleep(1000000);
		
		
		
		
		
	}
	
	return 0;
}


void * hilo_panel(void *arg)
{
	//Se inicializa la libreria wiring Pi
	wiringPiSetup();
//Se configura el GPIO 17 como salida
	pinMode( 0, OUTPUT );
	pinMode( 2, OUTPUT );
//Se escribe un valor digital al GPIO
	while( 1 )
	{			
		digitalWrite( 0, HIGH );
		digitalWrite( 2, HIGH );
		printf("\nEl reelé del panel esta abierto\n");
		usleep(1000000);
		digitalWrite( 0, LOW );
		digitalWrite( 2, LOW );
		printf("\nEl reelé del panel esta cerrado\n");
		usleep(1000000);
	}


	
}

void * hilo_panel2(void *arg)
{
	//Se inicializa la libreria wiring Pi
	wiringPiSetup();
//Se configura el GPIO 17 como salida
	
	pinMode( 2, OUTPUT );
//Se escribe un valor digital al GPIO
	while( 1 )
	{
		digitalWrite( 2, HIGH );
		printf("\nEl reelé de batería esta abierto\n");
		usleep(1000000);
		digitalWrite( 2, LOW );
		printf("\nEl reelé de batería esta cerrado\n");
		usleep(1000000);
	}
	
}




//Reele de Panel


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
	
	if(mysql_query(con,"select*from sensadoP order by hora desc limit 1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			printf("%s\n",row[3]);
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

	if(mysql_query(con,"select b.voltaje_max from historial_bateria_panel hbp,bateria b where hbp.id_bateria=b.id_bateria and hbp.activo=1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			printf("%s\n",row[0]);
			 dato=atof(row[0]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}




//Reelé de Bataeria








double mysql_voltaje_bateria_sensado()
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
	
	if(mysql_query(con,"select*from sensadoB order by hora desc limit 1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			printf("%s\n",row[3]);
			 dato=atof(row[3]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}

int mysql_voltaje_bateria_cierre_abertura()
{
	
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row; 	 	
	int valor=0;

	char *server="localhost";
	char *user="TT";
	char *pass="TT";
	char *database="tornasol";
	
	con=mysql_init(NULL);
	if(!mysql_real_connect(con,server,user,pass,database,0,NULL,0))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select b.voltaje_max,b.voltaje_min,b.nu_celdas from historial_bateria_panel hbp,bateria b where hbp.id_bateria=b.id_bateria and hbp.activo=1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double voltaje_max=0.0,voltaje_min=0.0,celda=0.0,voltaje_censado=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			printf("%s\n",row[0]);
			 voltaje_max=atof(row[0]);
			 voltaje_min=atof(row[1]);
			 celda=atof(row[2]);
			
		}
	
	voltaje_max=voltaje_max*celda;
	voltaje_min=voltaje_min*celda;
	voltaje_censado=mysql_voltaje_bateria_sensado();
	//digitalWrite( 0, HIGH );
	printf("\nVoltaje de censado es :%lf y max es %lf y min es %lf\n",voltaje_censado,voltaje_max,voltaje_min);
	if(voltaje_censado>=voltaje_min)
	{
			//digitalWrite( 0, HIGH );
			
			valor=1;
	}
	else
	{
			//digitalWrite( 0, LOW );
			
			valor=0;
	}
	
	
	
		
	mysql_free_result(res);
	mysql_close(con);
		
	return valor;
}
