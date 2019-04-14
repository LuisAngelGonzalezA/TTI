/*

Recordar la bandera de -lwiringPi en raspberry 

gcc uart_prueba.c -lwiringPi -o he

*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int fd ;
  int count=0xe2;
  unsigned int nextTime ;

  if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  

  for (;;)
  {
      printf ("\nOut--> %3d: ", count) ;
      serialPutchar (fd, count);


    delay (1000);

    while (serialDataAvail (fd))
    {
      printf ("Contestando-> %3s\n", serialGetchar (fd)) ;
      fflush (stdout) ;
      printf("Si entro");
	

    }
  }

  printf ("\n") ;
  return 0 ;
}
