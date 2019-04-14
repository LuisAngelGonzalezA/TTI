/** @brief: Este programa configura el BCM_GPIO 17 usando la libreria wiringPi
 * El GPIO 17 corresponde con el pin 0 en wiring Pi
 * Se debe compilar con: gcc gpio.c -o gpio -lwiringpi
 */
 
 
/*
 * 
 * gcc voltaje_pwm.c -o voltaje_pwm -lm -lwiringPi `mysql_config --cflags` `mysql_config --libs`
 * 
 * */ 

#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>

int main( )
{
//Se inicializa la libreria wiring Pi
	wiringPiSetup();
//Se configura el GPIO 17 como salida
	pinMode( 0, OUTPUT );
	pinMode( 3, OUTPUT );
//Se escribe un valor digital al GPIO
	while( 1 )
	{
		digitalWrite( 0, HIGH );
		digitalWrite( 3, HIGH );
		printf("Prendido el reele : 1 \n");
		sleep(2);
		printf("Apagado         el reele : 0\n");
		digitalWrite( 0, LOW );
		digitalWrite( 3, LOW );
		sleep(2);
	}
	return 0;
}
