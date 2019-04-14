
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_HILOS 4
#define N 8192 //Con números grandes hay problemas con la sinconía pero 

//programa para crear muchos hilos

/*
int * reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);
void * mayorArreglo(void *datos);
void * menorArreglo(void *datos);
*/

void * funHilo(void *arg);
pthread_mutex_t bloqueo;

int contador;

int main(){
	int nhs[NUM_HILOS], *res;
	register int nh;

	pthread_t tids[NUM_HILOS];

	contador = 0;

	//Se agregó para tener exclusión mutua; Se inicializa en el proceso padre una vez
	pthread_mutex_init(&bloqueo, NULL);
	
	printf("Probando hilos...\n");

/*
	datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);
*/
	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		nhs[nh] = nh;
		pthread_create(&tids[nh], NULL, funHilo, (void *)&nhs[nh]);
	}
	
	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		pthread_join(tids[nh], (void **)&res);
		printf("Hilo %d terminado\n", *res);
	}

	pthread_mutex_destroy(&bloqueo);

	return 0;
}


void * funHilo(void *arg){
	register int i = 0;
	int nh = *(int*) arg;

	//Se agregó esto para crear una zona crítica y que los demás hilos no puedan acceder a ella mientras uno la esté ocupando
	pthread_mutex_lock(&bloqueo);
	contador++;	

	printf("Iniciando hilo %d con contador %d\n", nh, contador);
	while(--i); //Para que sea reentrante
	//sleep(5);	//Es no reentrante
	printf("Terminando hilo %d con contador %d\n", nh, contador);

	pthread_mutex_unlock(&bloqueo);

	pthread_exit(arg);
}

// *Ap : Contenido de Ap
//Con el cast se conoce los bytes que tiene que obtener a partir de la dirección de Ap

/*
int * reservarMemoria(){
	int *mem;

	mem = (int *) malloc(sizeof(int)*N);
	if(!mem){
		perror("Error al asignar memoria...\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}


void llenarArreglo(int *datos){
	register int i;

	srand(getpid()); //Semilla para generar random del número de proceso

	for(i = 0; i < N; i++){
		datos[i] = rand() % 255;
	}
}


void * mayorArreglo(void *arg){
	register int i;
	static int mayor;
	int *datos = (int*) arg;

	mayor = datos[0];

	for(i = 1; i < N; i++){
		if(datos[i]>mayor)
			mayor = datos[i];
	}

	pthread_exit((void*) &mayor);
}

void * menorArreglo(void *arg){
	register int i;
	static int menor;
	int *datos = (int*) arg;

	menor = datos[0];

	for(i = 1; i < N; i++){
		if(datos[i]<menor)
			menor = datos[i];
	}

	pthread_exit((void *) &menor);
}

void imprimirArreglo(int *datos){
	register int i;

	for(i = 0; i < N; i++){

		if(!(i%16))
			printf("\n");

		printf("%3d ", datos[i]);
	}
	printf("\n");
}
*/