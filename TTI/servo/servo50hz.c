#include <wiringPi.h>
#include <stdio.h>

int main (void)
{
   printf ("Colocando Ángulos\n");
   wiringPiSetupGpio();
   pinMode (18, PWM_OUTPUT) ;
   pwmSetMode (PWM_MODE_MS);
   pwmSetRange (200);
   pwmSetClock (192);
   pwmWrite(18,15);
   delay(1000);
   pwmWrite(18,20);
   delay(1000);
   pwmWrite(18,10);
   delay(1000);
   return 0;
}
/*



According to this formula:

pwmFrequency in Hz = 19.2e6 Hz / pwmClock / pwmRange
We can set pwmClock=1920 and pwmRange=200 to get pwmFrequency=50Hz:

50 Hz = 19.2e6 Hz / 1920 / 200
I test it on alarmpi:

 pacman -S wiringpi
 gpio mode 1 pwm
 gpio pwm-ms
 gpio pwmc 1920
 gpio pwmr 200     # 0.1 ms per unit
 gpio pwm 1 15     # 1.5 ms (0º)
 gpio pwm 1 20     # 2.0 ms (+90º)
 gpio pwm 1 10     # 1.0 ms (-90º)
*/
