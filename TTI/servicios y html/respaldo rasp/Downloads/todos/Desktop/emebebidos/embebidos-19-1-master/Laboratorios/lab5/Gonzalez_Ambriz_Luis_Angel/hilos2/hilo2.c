#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


 #define N 32

void * suma( void * arg);
void * resta( void * arg);
void * multi( void * arg);
void * divi( void * arg);


int * reservarmemoria();
void llenararreglo(int * datos);
void imprimirarreglo();
void imprimirarreglo(int *datos);
void * menorArreglo(void * arg);
void * mayorArreglo(void * arg);



int num=12,num2=12;
int main()
{

	int * res_mayor,*res_menor,*datos;
	pthread_t tid_mayor,tid_menor;
	printf("Probando hilos\n");
	datos=reservarmemoria();
	llenararreglo(datos);
	imprimirarreglo(datos);

	pthread_create(&tid_menor,NULL,menorArreglo,(void *)datos);
	pthread_create(&tid_mayor,NULL,mayorArreglo,(void *) datos);

	pthread_join(tid_mayor,  (void **) &res_mayor);
	pthread_join(tid_menor,(void **) &res_menor);

	printf("Mayor es:%d\n", *res_mayor);
	printf("Menor es:%d\n", *res_menor);


	return 0;

}

void * suma(void * arg){

	int *res=(int *)malloc(sizeof(int));
	*res=num+num2;
	pthread_exit((void*)  res);

}



void * resta(void * arg){


	int *res=(int *)malloc(sizeof(int));
	*res=num-num2;
	pthread_exit((void*)  res);
	
}

void * multi(void * arg){


	static int res;
	res=num*num2;
	pthread_exit((void*)  &res);

	
}

void * divi(void * arg){

	static int res;
	res=num/num2;
	pthread_exit((void*)  &res);

	
}



void llenararreglo(int *datos)
{
	register int i;
	srand(getpid());
	for ( i = 0; i <N; i++)
	{
		datos[i]=rand()%255;
	}
}


int * reservarmemoria()
{

	int *mem;
	mem=(int *) malloc(sizeof(int) * N);
	if( !mem)
	{
		perror("Error al asignar memoria ... \n");
		exit(EXIT_FAILURE);
	}
	return mem;


}



void * mayorArreglo(void * arg)
{
	register int i;
	static int mayor;
	int *datos=(int *)arg;
	mayor=datos[0];
	for (i = 1; i < N; i++)
	{	
		if(datos[i]> mayor)
			mayor=datos[i];
	}
	pthread_exit((void *)&mayor);
}

void * menorArreglo(void *arg)
{
	register int i;
	static int menor;
	int *datos=(int*)arg;
	menor=datos[0];
	for (i = 1; i < N; i++)
	{	
		if(datos[i]<menor)
			menor=datos[i];
	}

	pthread_exit((void *)&menor);
}


void imprimirarreglo(int *datos)
{
	register int i;
	for (i = 0; i < N; i++)
	{
		if(!(i%16))
		{
			printf("\n");
		}
		printf("%3d ", datos[i]);

	}
	printf("\n\n");
}









/*

 Formas de guardas valores es :
 	- Reservar memoria en malloc
 	- Reservar una variable usamos el static 

*/