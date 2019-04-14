#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "defs.h"
#include "procesamiento.h"
#include "datos.h"


void proceso_padre( int pipefd[] ){
        register int np;
        int pid, resultado, proc;
	int *resultado2;

        printf("Proceso padre con pid %d\n", getpid());
	close( pipefd[1] );
        for( np = 0; np < NUM_PROC; np++){
                pid = wait( &proc );
		if((proc>>8) == 3){
			resultado2 = reservarMemoria();
			read( pipefd[0], resultado2, sizeof(int)*N );
			printf("Proceso hijo con pid %d ordenando\n\n", pid);
			imprimirArreglo(resultado2);
			free(resultado2);
		}
		else{
			read( pipefd[0], &resultado, sizeof(int) );
			printf("Proceso hijo con pid %d y resultado =  %d \n\n", pid, resultado);
		}
	}
	close( pipefd[0] );
}


void proceso_hijo( int np, int datos[], int pipefd[] ){

	int mayor, menor;
	int promedio;
	printf(" Proceso hijo %d con pid %d\n", np, getpid());

	close( pipefd[0] );

	if( np == 0 ){
		mayor = mayorArreglo( datos );
		write( pipefd[1], &mayor, sizeof(int));
		close(pipefd[1]);
		exit( mayor );
	}
	else if( np == 1 ){
		menor = menorArreglo( datos );
		write( pipefd[1], &menor, sizeof(int));
		close(pipefd[1]);
		exit( menor );
	}
	else if( np == 2 ){
		promedio = promedioArreglo( datos );
		write( pipefd[1], &promedio, sizeof(int));
		close(pipefd[1]);
		exit( promedio );
	}
	else if( np == 3 ){
		ordenarArreglo( datos );
		write( pipefd[1], datos, sizeof(int)*N); //reservo memoria
		close(pipefd[1]);                        //mandar por tuverias
	}
	exit( np );
}
