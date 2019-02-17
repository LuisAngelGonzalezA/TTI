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


short existe(char *fname);
double mysql_voltaje();
void recalcular(double voltaje_ref,int x,int y);
void guardar_datos(int x,int y);
int * recalcular_y(double voltaje_ref,int x,int y);
int * puntos_optimos_y(int * censo_de_datos);
int * puntos_optimos_x(int * censo_de_datos);
double voltaje_mayor_y,voltaje_mayor_x;
int main()
{
	
	char *archivo="/home/pi/Desktop/archivo.txt";
	int archivo_exixte=existe(archivo);

	
	if(archivo_exixte==0){
		/*Existe el archivo se inicializo al comienzo del inicio del sistema o incluso al inicio del horario
		 * destinado para el comienzo, entonces se puede realizar la busqueda para una posición adecuada
		 * para obtener una mayor irradiación posible*/
		FILE *fichero=fopen(archivo,"r");
		int posicion_servo_x=0.0,posicion_servo_y=0.0;
		if(fichero>0){//Si el fichero se abre mal devuelve NULL
	    
			printf("File Open\n");
			int i=0;
			char lectura[100]={};
			
		
			while(!feof(fichero)){//Esperamos el fin del fichero
				//Leemos el fichero y lo printamos
				printf("-->%s", fgets(lectura, 99, fichero));
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
			}
			if(i<2)
			{
				posicion_servo_x=0.0;
				posicion_servo_y=0.0;
				printf("\n\nError faltan datos\n");
				
			}

	}else{
	    posicion_servo_x=0.0;
		posicion_servo_y=0.0;
	    printf("File not Open\n");
	    //syslog(LOG_INFO,"File not Open");
	}
	
	printf("\nValores obtenidos del archvio son %d\n",posicion_servo_x);
	printf("\nValores obtenidos del archvio son %d\n",posicion_servo_y);
	double voltaje_incial=mysql_voltaje();
	recalcular(voltaje_incial,posicion_servo_x,posicion_servo_y);
	}
	else if(archivo_exixte==-1)
	{
			/*No existe se ejecuta el comando para que se inicie los valores de default al posicionamiento 
			 * del panel solar como un default al comienzo del día.*/
		
	}
	else
	{
		/*Error con el archivo no se pudo leer debemos de atender este siniestro para poder seguir con la 
		 * ejecución del programa para el posicionamiento adecuado y así efectuar el movimiento del panel 
		 * para que simule el comportamiento del panel solar.*/	 
		 
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
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select*from panel_registro order by fecha desc limit 1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			printf("%s\n",row[1]);
			 dato=atof(row[1]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}


int * recalcular_y(double voltaje_ref,int x,int y)
{
	printf("\nCalculando parte de y\n");
	double voltaje_referencia=voltaje_ref;
	int max_x1=0,max_x2=0,max_y1=0,max_y2=0;
	int posicion_temporal_x=x;
	int posicion_temporal_y=y + 5;
	double voltaje_temporal=0.0;
	int *datos_censado;
	int bandera_positiva=0,bandera_negativa=0;
	guardar_datos(posicion_temporal_x,posicion_temporal_y);
	while(1)
	{
		voltaje_temporal=mysql_voltaje();
		
		if(voltaje_temporal>voltaje_referencia )
		{	
			
			
			if(posicion_temporal_y>=180)
			{
				voltaje_referencia=voltaje_temporal;
				printf("Se ha censado y no cambió el valor mayor 1\n");
				max_x1=posicion_temporal_x;
				max_y1=180;
				
			}
			else
			{
				bandera_positiva=1;
				voltaje_referencia=voltaje_temporal;
				max_x1=posicion_temporal_x;
				max_y1=posicion_temporal_y;
				printf("\nvalores censados  positivos %d  <-> %d\n",posicion_temporal_x,posicion_temporal_y);
				guardar_datos(posicion_temporal_x,posicion_temporal_y);
				posicion_temporal_y=posicion_temporal_y+5;
			}
		}
		else if(voltaje_referencia>=voltaje_temporal)
		{	
			
			
			if(bandera_positiva==0)
			{
				max_x1=posicion_temporal_x;
				max_y1=posicion_temporal_y;
			}
			if(max_y1>=180)
			{
				max_y1=180;
			}
			else max_y1=max_y1-5;
			printf("\nSe obtuvo el voltaje maximo\n");
			
			break;
			
		}	
	}//while de positivo
	printf("\nCensando parte negativa\n");
	usleep(5000000);
	posicion_temporal_y=y-5;
	while(1)
	{
		voltaje_temporal=mysql_voltaje();
		
		if(voltaje_temporal>voltaje_referencia)
		{	
			
			
			if(posicion_temporal_y<=0)
			{
				voltaje_referencia=voltaje_temporal;
				printf("Se ha censado y no cambió el valor mayor 2\n");
				max_x1=posicion_temporal_x;
				max_y1=0;
				
			}
			else
			{
				bandera_negativa=1;
				voltaje_referencia=voltaje_temporal;
				max_x1=posicion_temporal_x;
				max_y1=posicion_temporal_y;
				printf("\nvalores censados  negativos %d  <->   %d\n",posicion_temporal_x,posicion_temporal_y);
				guardar_datos(posicion_temporal_x,posicion_temporal_y);
				posicion_temporal_y=posicion_temporal_y-5;
			}
		}
		else if(voltaje_referencia>=voltaje_temporal)
		{	
			
			
			if(bandera_negativa==0)
			{
				max_x2=posicion_temporal_x;
				max_y2=posicion_temporal_y;
			}
			if(max_y2<=0)
			{
				max_y2=0;
			}
			else max_y2=max_y2+5;
			printf("\nSe obtuvo el voltaje maximo\n");
			
			break;
			
		}	
	}//while de negativo
	guardar_datos(x,y);
	
	datos_censado=(int*)malloc(4*sizeof(int));
	datos_censado[0]=max_x1;
	datos_censado[1]=max_y1;
	datos_censado[2]=max_x2;
	datos_censado[3]=max_y2;
	printf("%d  <->  %d \n  %d  <->  %d \n",datos_censado[0],datos_censado[1],datos_censado[2],datos_censado[3]);
	return datos_censado;
	
	
	
}


int * recalcular_x(double voltaje_ref,int x,int y)
{
	printf("\nCalculando parte de x\n");
	double voltaje_referencia=voltaje_ref;
	int max_x1=0,max_x2=0,max_y1=0,max_y2=0;
	int posicion_temporal_x=x + 5;
	int posicion_temporal_y=y;
	double voltaje_temporal=0.0;
	int *datos_censado;
	int bandera_positiva=0,bandera_negativa=0;
	guardar_datos(posicion_temporal_x,posicion_temporal_y);
	while(1)
	{
		voltaje_temporal=mysql_voltaje();
		
		if(voltaje_temporal>voltaje_referencia )
		{	
			
			
			if(posicion_temporal_x>=180)
			{
				voltaje_referencia=voltaje_temporal;
				printf("Se ha censado y no cambió el valor mayor 1\n");
				max_x1=180;
				max_y1=posicion_temporal_y;
				
			}
			else
			{
				bandera_positiva=1;
				voltaje_referencia=voltaje_temporal;
				max_x1=posicion_temporal_x;
				max_y1=posicion_temporal_y;
				printf("\nvalores censados  positivos %d  <-> %d\n",posicion_temporal_x,posicion_temporal_y);
				guardar_datos(posicion_temporal_x,posicion_temporal_y);
				posicion_temporal_x=posicion_temporal_x+5;
			}
		}
		else if(voltaje_referencia>=voltaje_temporal)
		{	
			
			
			if(bandera_positiva==0)
			{
				max_x1=posicion_temporal_x;
				max_y1=posicion_temporal_y;
			}
			if(max_x1>=180)
			{
				max_x1=180;
			}
			else max_x1=max_x1-5;
			printf("\nSe obtuvo el voltaje maximo\n");
			
			break;
			
		}	
	}//while de positivo
	printf("\nCensando parte negativa\n");
	usleep(5000000);
	posicion_temporal_x=x-5;
	while(1)
	{
		voltaje_temporal=mysql_voltaje();
		
		if(voltaje_temporal>voltaje_referencia)
		{	
			
			
			if(posicion_temporal_x<=0)
			{
				voltaje_referencia=voltaje_temporal;
				printf("Se ha censado y no cambió el valor mayor 2\n");
				max_x1=0;
				max_y1=posicion_temporal_y;
				
			}
			else
			{
				bandera_negativa=1;
				voltaje_referencia=voltaje_temporal;
				max_x1=posicion_temporal_x;
				max_y1=posicion_temporal_y;
				printf("\nvalores censados  negativos %d  <->   %d\n",posicion_temporal_x,posicion_temporal_y);
				guardar_datos(posicion_temporal_x,posicion_temporal_y);
				posicion_temporal_x=posicion_temporal_x-5;
			}
		}
		else if(voltaje_referencia>=voltaje_temporal)
		{	
			
			
			if(bandera_negativa==0)
			{
				max_x2=posicion_temporal_x;
				max_y2=posicion_temporal_y;
			}
			if(max_x2<=0)
			{
				max_x2=0;
			}
			else max_x2=max_x2+5;
			printf("\nSe obtuvo el voltaje maximo\n");
			
			break;
			
		}	
	}//while de negativo
	guardar_datos(x,y);
	
	datos_censado=(int*)malloc(4*sizeof(int));
	datos_censado[0]=max_x1;
	datos_censado[1]=max_y1;
	datos_censado[2]=max_x2;
	datos_censado[3]=max_y2;
	printf("%d  <->  %d \n  %d  <->  %d \n",datos_censado[0],datos_censado[1],datos_censado[2],datos_censado[3]);
	return datos_censado;
	
	
	
}

void recalcular(double voltaje_ref,int x,int y)
{
	int *censo_de_datos=recalcular_y(voltaje_ref,x,y);
	int *censo_de_datos_x;
	int *censo_de_datos_x_puntos;
	printf("%d  <->  %d \n  %d  <->  %d \n",censo_de_datos[0],censo_de_datos[1],censo_de_datos[2],censo_de_datos[3]);
	int * censo_de_datos_y=puntos_optimos_y(censo_de_datos);//,voltaje_mayor_x=0.0;
	printf("----------->%d  <->  %d \n \n",censo_de_datos_y[0],censo_de_datos_y[1]);
	while(1)
	{
		censo_de_datos_x=recalcular_x(voltaje_mayor_y,censo_de_datos_y[0],censo_de_datos_y[1]);
		censo_de_datos_x_puntos=puntos_optimos_x(censo_de_datos_x);
		if(voltaje_mayor_x>=voltaje_mayor_y)
		{
			censo_de_datos=recalcular_y(voltaje_ref,censo_de_datos_x_puntos[0],censo_de_datos_x_puntos[1]);
			censo_de_datos_y=puntos_optimos_y(censo_de_datos);
			
		}
		else
		{
			
			guardar_datos(censo_de_datos_x[0],censo_de_datos_x[1]);
			printf("Exito al poner los datos optimos");
			usleep(1000000);
		}
	}
	
	
}
int * puntos_optimos_y(int * censo_de_datos)
{
	double voltaje_1=0.0,voltaje_2=0.0;	
	printf("\nValor rápido inserta uno bajo y luego uno alto\n");
	guardar_datos(censo_de_datos[0],censo_de_datos[1]);
	voltaje_1=mysql_voltaje();
	printf("\nEspero ya lo cambiaras se acaba el tiempo \n");
	usleep(5000000);
	guardar_datos(censo_de_datos[2],censo_de_datos[3]);
	voltaje_2=mysql_voltaje();
	int * puntos_maximos=(int*)malloc(2*sizeof(int));
	
	if(voltaje_1>voltaje_2)
	{
		
		guardar_datos(censo_de_datos[0],censo_de_datos[1]);
		puntos_maximos[0]=censo_de_datos[0];
		puntos_maximos[1]=censo_de_datos[1];
		voltaje_mayor_y=voltaje_1;
		
	}
	else if(voltaje_2>voltaje_1)
	{
		guardar_datos(censo_de_datos[2],censo_de_datos[3]);
		puntos_maximos[0]=censo_de_datos[2];
		puntos_maximos[1]=censo_de_datos[3];
		voltaje_mayor_y=voltaje_2;
	}
	else
	{
		guardar_datos(censo_de_datos[0],censo_de_datos[1]);
		puntos_maximos[0]=censo_de_datos[0];
		puntos_maximos[1]=censo_de_datos[1];
		voltaje_mayor_y=voltaje_1;
	}
	return puntos_maximos;


}


int * puntos_optimos_x(int * censo_de_datos)
{
	double voltaje_1=0.0,voltaje_2=0.0;	
	guardar_datos(censo_de_datos[0],censo_de_datos[1]);
	voltaje_1=mysql_voltaje();
	guardar_datos(censo_de_datos[2],censo_de_datos[3]);
	voltaje_2=mysql_voltaje();
	int * puntos_maximos=(int*)malloc(2*sizeof(int));
	
	if(voltaje_1>voltaje_2)
	{
		
		guardar_datos(censo_de_datos[0],censo_de_datos[1]);
		puntos_maximos[0]=censo_de_datos[0];
		puntos_maximos[1]=censo_de_datos[1];
		voltaje_mayor_x=voltaje_1;
		
	}
	else if(voltaje_2>voltaje_1)
	{
		guardar_datos(censo_de_datos[2],censo_de_datos[3]);
		puntos_maximos[0]=censo_de_datos[2];
		puntos_maximos[1]=censo_de_datos[3];
		voltaje_mayor_x=voltaje_2;
	}
	else
	{
		guardar_datos(censo_de_datos[0],censo_de_datos[1]);
		puntos_maximos[0]=censo_de_datos[0];
		puntos_maximos[1]=censo_de_datos[1];
		voltaje_mayor_x=voltaje_1;
	}
	return puntos_maximos;


}

void guardar_datos(int x,int y)
{
	printf("\nGuardando\n");
	FILE *fichero;
	char lectura[100];
	fichero=fopen("/home/pi/Desktop/archivo.txt","wt"); //Abrimos el fichero para solo lectura
	sprintf(lectura,"%d\n%d",x,y);
	fputs(lectura,fichero);
	fclose(fichero);
	usleep(5000000);
	
	
	
}
