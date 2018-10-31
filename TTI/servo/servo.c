#include <wiringPi.h>
#include <stdio.h>

int main (void)
{
   printf ("Colocando Ángulos\n");
   wiringPiSetupGpio();
   pinMode (18, PWM_OUTPUT) ;
   pwmSetMode (PWM_MODE_MS);
   pwmSetRange (2000);
   pwmSetClock (192);
   pwmWrite(18,50);
   delay(1000);
   pwmWrite(18,245);
   delay(1000);
	delay(10000);
   pwmWrite(18,150);
   delay(1000);
   pwmWrite(18,200);
   delay(1000);
   pwmWrite(18,230);
   delay(1000);
   pwmWrite(18,238);
   delay(1000);
   pwmWrite(18,50);
   delay(1000);
   pwmWrite(18,60);
   delay(1000);
   pwmWrite(18,70);
   delay(1000);
   pwmWrite(18,80);
   delay(1000);
   pwmWrite(18,150);
   delay(1000);
   pwmWrite(18,180);
   delay(1000);
   pwmWrite(18,200);
   delay(1000);
   return 0;
}
