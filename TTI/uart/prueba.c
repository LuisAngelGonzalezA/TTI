#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void * mando( void *idh );
void * recibo( void *idh );


int matar_envio=0;
int main(int argc, char const *argv[])
{

	unsigned char a=0x02;
	unsigned char b=0x02;
	unsigned char comparacion= a == b;
	printf("-----   %X  -----\n", comparacion);


	pthread_t tids[2];
	int nh[2]={0 , 1},*hilo;
	
	

	pthread_create(&tids[0],NULL,mando,(void *) & nh[0]);
	pthread_create(&tids[1],NULL,recibo,(void *) & nh[1]);

	pthread_join(tids[0],(void **)&hilo);
	printf("--->%d\n",*hilo);
	pthread_join(tids[1],(void **)&hilo);
	printf("--->%d\n",*hilo);
	printf("\n\n");
	printf("------->Finalizado<<<<<<<----\n");
}




void * mando( void *idh )
{
	while(1)
	{
	
	if(matar_envio==0)
	{
		
		printf("E2\n");
	}
	sleep(1);
	}
	pthread_exit(idh);
		
	//}
}
void * recibo( void *idh )
{
	register int i;
	unsigned char dato=0x00;
	static unsigned char comparacion_inicio= 0xC2;
	static unsigned char comparacion_final= 0xC2;
	printf("\t\t %c  %c\n", comparacion_inicio,comparacion_final);
	while(1)
	{
	sleep(1);
	fflush(stdin);
	printf("ESPERANDO DATOS\n");
	scanf("%s",&dato);
	printf("Dato ingresado--->%c    %X\n",dato,dato);
	if(dato == comparacion_inicio)
	{
		printf("\tRecibiendo datos\n");
		
		matar_envio=1;
		for ( i = 0; i <=7; i++)
		{
			//comparacion=0x30;
			
			fflush( stdin );
			scanf("%s",&dato);
			

			printf("Dato ingresado [%d]: %c --->%X--------->%c<<---\n",i,dato,dato,comparacion_final);
			if(dato == comparacion_final)
			{
				printf("EXITO AL FINALIZAR\n");
				matar_envio=0;
				break;
			}
		}
		
	}
	}
	pthread_exit(idh);
	
}
