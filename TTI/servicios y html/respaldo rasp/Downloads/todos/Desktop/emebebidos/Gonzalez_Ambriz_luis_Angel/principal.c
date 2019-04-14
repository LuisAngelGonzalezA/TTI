#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "datos.h"
#include "procesamiento.h"
#include "procesos.h"
#include "defs.h"


int main(){
	pid_t pid;
	int np;

	int *datos;

	datos = reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);

	printf("Probando procesos...");
	
	for (np = 0; np < NUM_PROC; np++)
	{
	
		pid = fork();
		if (pid== -1)
		{
			perror("No se creó el proceso... \n");
			exit(EXIT_FAILURE);
		}
		//Tiene pid = 0 es hijo, pid > 0 es padre
		if(!pid){
			procesoHijo(np, datos);
		}	
	}
	procesoPadre();	

	free(datos);

	return 0;
}