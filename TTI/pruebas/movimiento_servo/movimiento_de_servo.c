#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>

short existe(char *fname);
int posicion_panel(int grado);



int main()
{
	int div = 390;
	int range = 1024;
	wiringPiSetupGpio();
	pinMode(18,PWM_OUTPUT);
	pinMode(13,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(div);
	pwmSetRange(range);
	char *archivo="/home/pi/Desktop/archivo.txt";
	int archivo_exixte=existe(archivo);
	while(1)
	{
		usleep(100000);
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
	
	printf("\nValores obtenidos del archvio son %d",posicion_servo_x);
	printf("\nValores obtenidos del archvio son %d\n",posicion_servo_y);	 
	 	 
		
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
	
}


short existe(char *fname)
{
	int fd=open(fname,O_RDONLY);
	if(fd<0)
		return (errno==ENOENT)?-1:-2;
	return 0; 
	
	
	
	
	return 0;
}


int posicion_panel(int grado)
{
	int posicion=(.522*grado)+29;
	return posicion;
}











