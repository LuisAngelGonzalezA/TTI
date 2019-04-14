#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "defs.h"
#include "procesamiento.h"
#include "datos.h"

void procesoPadre()
{
	int np, numero;
	pid_t pid_hijo;

	printf("Proceso padre ejecutado con pid %d\n", getpid());
	
	for (np=0; np<NUM_PROC;np++)
	{
		pid_hijo=wait(&numero);
		printf("Proceso hijo terminado con pid: %d\n y retorno %d \n", pid_hijo, numero>>8);
	}
	
}

void procesoHijo(int np, int *datos)
{
	int mayor, menor;
	float promedio;

	printf("Proceso hijo %d ejecutado con pid %d\n", np, getpid());
	//while(1);

	if(np == 0){
		mayor = mayorArreglo(datos);
		exit(mayor);
	}
	else if(np == 1){
		menor = menorArreglo(datos);
		exit(menor);
	}
	else if(np == 2){
		promedio = promedioArreglo(datos);
		exit(promedio);
	}
	else if(np == 3){
		//imprimirArreglo(datos); //sin ordenar
		ordenaArreglo(datos);
		imprimirArreglo(datos); //ordenado
		exit(np);
	}

}