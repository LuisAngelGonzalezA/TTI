#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
int posicion_panel(int grado);
int main(int argc, char* argv[])
{

  int div = 390;
  int range = 1024;
  
  wiringPiSetupGpio();

  pinMode(18,PWM_OUTPUT);
  pinMode(13,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(div);
  pwmSetRange(range);


  for(;;) {
    int grado=0,grados_y=0;
    int posicion=0;
    printf("Grados en X:\n");
    scanf("%d",&grado);
    printf("Grados en Y:\n");
    scanf("%d",&grados_y);

    posicion=posicion_panel(grado);
    pwmWrite(18,posicion);
    delay(1000);

    posicion=posicion_panel(grados_y);
    pwmWrite(13,posicion);
    delay(1000);
    }
}


int posicion_panel(int grado)
{
	int posicion=(.522*grado)+29;
	return posicion;
}
