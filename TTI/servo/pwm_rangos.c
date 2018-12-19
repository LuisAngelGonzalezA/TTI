#include <wiringPi.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{


  int div = 390;
  int range = 1024;
  int min = atoi(argv[1]);
  int max = atoi(argv[2]);

  wiringPiSetupGpio();

  pinMode(18,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(div);
  pwmSetRange(range);

  for(;;) {
    delay(2000);
    pwmWrite(18,min);
    delay(1000);
    pwmWrite(18,max);
    delay(1000);
  }
}