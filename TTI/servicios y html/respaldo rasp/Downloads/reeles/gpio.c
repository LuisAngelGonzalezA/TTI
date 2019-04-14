/** @brief: Este programa configura el BCM_GPIO 17 usando la libreria wiringPi
 * El GPIO 17 corresponde con el pin 0 en wiring Pi
 * Se debe compilar con: gcc gpio.c -o gpio -lwiringpi
 * 
 * 
 * gcc gpio.c -o gpio -lwiringPi
 * 
 * 
 */

#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>

int main( )
{
//Se inicializa la libreria wiring Pi
	wiringPiSetup();
//Se configura el GPIO 17 como salida
	pinMode( 0, OUTPUT );
	pinMode( 2, OUTPUT );
//Se escribe un valor digital al GPIO
	while( 1 )
	{
		digitalWrite( 0,0 );
		digitalWrite( 2,0 );
		printf("\nReele se cierra en cero \n");
		sleep(4);
		printf("\nReele se abre en uno\n");
		digitalWrite( 0, 1 );
		digitalWrite( 2, 1 );
		sleep(4);
	}
	return 0;
}
