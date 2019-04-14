#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  if (argc < 6) {
    printf("Usage: %s divisor rango min max\n", argv[0]);
    exit(0);
  }

  int div = atoi(argv[1]);
  int range = atoi(argv[2]);
  int min = atoi(argv[3]);
  int max = atoi(argv[4]);
  int media = atoi(argv[5]);

  wiringPiSetupGpio();

  pinMode(18,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(div);
  pwmSetRange(range);

  for(;;) {
    pwmWrite(18,min);
    delay(1000);
    pwmWrite(18,media);
    delay(1000);
    pwmWrite(18,max);
    delay(1000);
  }
}