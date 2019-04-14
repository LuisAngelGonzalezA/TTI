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
	int *datos;
	int pipefd[2], edo_pipe;
	datos = reservarMemoria();
	llenarArreglo( datos );
	imprimirArreglo( datos );
	printf("\n\n");

	edo_pipe = pipe(pipefd);

	if( edo_pipe == -1 ){
		perror("Error al crear el pipe\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid;
        register int np;

        for(np = 0; np < NUM_PROC; np++ ){

                pid = fork();

                if( pid == -1){
                        perror("Error al crear el proceso hijo\n");
                        exit(EXIT_FAILURE);
                }

                if( !pid ){
                        proceso_hijo( np, datos, pipefd );
                }
        }

        proceso_padre( pipefd );


	free(datos);
	return 0;

}
