#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int grado=90,grados_y=90;

int divisor = 390;
int range = 1024;

void * movimiento_x(void *arg);
void * movimiento_y(void *arg);
void * prueba(void *arg);
int main(int argc, char* argv[])
{
  
  wiringPiSetupGpio();

  pinMode(18,PWM_OUTPUT);
  pinMode(13,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(divisor);
  pwmSetRange(range);

  pthread_t tids[3];
  pthread_create(&tids[0],NULL,prueba,NULL);
  pthread_create(&tids[1],NULL,movimiento_x,NULL);
  pthread_create(&tids[2],NULL,movimiento_y,NULL);

  //pthread_join(tids,NULL);
  for(;;) {
    

    printf("Grados en X:\n");
    scanf("%d",&grado);
    printf("Grados en Y:\n");
    scanf("%d",&grados_y);

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

