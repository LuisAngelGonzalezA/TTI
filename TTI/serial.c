#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<wiringPi.h>
#include<wiringSerial.h>

int main()
{



	int serial_port,serial_port_S0;
        int count=0xe1;
	char dat,*dato;
	if((serial_port = serialOpen("/dev/ttyAMA0",9600)) < 0)
	{
		fprintf(stderr,"No conexion\n");
		return 1;
	}
	if((serial_port_S0 = serialOpen("/dev/ttyS0",9600)) < 0)
	{
		fprintf(stderr,"No conexion\n");
		return 1;
	}

	if(wiringPiSetup()==-1)
	{
	fprintf(stdout,"No abrió : %s \n",strerror(errno));
	return 1;
	}

	serialFlush(serial_port);
	serialFlush(serial_port_S0);
	
	
	
	while(1)
	{
	delay(1000);
	printf ("\nOut--> %3X: ", count) ;
      	serialPutchar (serial_port, count);
	delay(1000);
	printf ("\nOut--> %3X: ", count) ;
	serialPutchar (serial_port, count);
	delay(1000);
	printf ("\nOut--> %3X: ", count) ;
	serialPutchar (serial_port, count);
	printf("\nEsperando\n");
	delay(10);
	while(serialDataAvail(serial_port_S0) >= 0)
	{
	fflush(stdout);
	serialPrintf(serial_port_S0,dato);
	//dat=serialGetchar(serial_port_S0);
	
	//printf("Contestando--->%X\n",dat);
	
	delay(10);	
}

	}
return 0;
}