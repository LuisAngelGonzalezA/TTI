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
        
         if(proc >> 8 ==0)
         {
	
			read( pipefd[0], &resultado, sizeof(int) );
			printf("******Proceso hijo con id %d con pid %d y numero mayor =  %d  \n\n", proc>>8 , pid, resultado);
		
         }
         else if(proc >> 8 ==1)
         {
	
			read( pipefd[0], &resultado, sizeof(int) );
			printf("******Proceso hijo con id %d con pid %d y numero menor =  %d  \n\n", proc>>8 , pid, resultado);
		
         }
         if(proc >> 8 ==2)
         {
	
			read( pipefd[0], &resultado, sizeof(int) );
			printf("******Proceso hijo con id %d con pid %d y promedio =  %d  \n\n", proc>>8 , pid, resultado);
		
         }


		if((proc>>8) == 3){
			resultado2 = reservarMemoria();
			read( pipefd[0], resultado2, sizeof(int)*N );
			printf("******Proceso hijo con id %d con pid %d y ordenamiento  \n\n", proc>>8 , pid);
			
			imprimirArreglo(resultado2);
			free(resultado2);

		}
		
	}
	close( pipefd[0] );
}


void proceso_hijo( int np, int datos[], int pipefd[] ){

		int mayor, menor;
	int promedio;
	printf("----> Proceso hijo %d con pid %d \n\n", np, getpid());

	close( pipefd[0] );

	if( np == 0 ){
		mayor = mayorArreglo( datos );
		write( pipefd[1], &mayor, sizeof(int));
		close(pipefd[1]);
	}
	else if( np == 1 ){
		menor = menorArreglo( datos );
		write( pipefd[1], &menor, sizeof(int));
		close(pipefd[1]);
	}
	else if( np == 2 ){
		promedio = promedioArreglo( datos );
		write( pipefd[1], &promedio, sizeof(int));
		close(pipefd[1]);
	}
	else if( np == 3 ){
		ordenarArreglo( datos );
		write( pipefd[1], datos, sizeof(int)*N);
		close(pipefd[1]);
	}
	exit( np );
}
