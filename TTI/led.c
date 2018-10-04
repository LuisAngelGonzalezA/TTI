#include<wiringPi.h>
#include<stdio.h>
int main()
{

wiringPiSetup();
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);

for(;;)
{	
	printf("Prendido\n");
	digitalWrite(2,HIGH);
	delay(500);
	printf("Apagado\n");
	digitalWrite(2,LOW);
	delay(1000);
	printf("Prendido 3\n");
	digitalWrite(3,HIGH);
	delay(500);
	printf("Apagado 3\n");
	digitalWrite(3,LOW);
	delay(1000);


}


return 0;
}