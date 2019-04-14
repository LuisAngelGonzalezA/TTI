#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define N 64
#define NUM_PROC 4

int * reservarMemoria( void );

void imprimirArreglo( int datos[]);
void llenarArreglo( int datos[]);

int mayorArreglo( int datos[] );
int menorArreglo( int datos[] );
void ordenarArreglo( int datos[] );
int promedioArreglo( int datos[] );

void proceso_hijo( int np, int datos[], int pipefd[] );
void proceso_padre( int pipefd[]  );

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


void proceso_hijo( int np, int datos[], int pipefd[] ){

	int mayor, menor;
	int promedio;
	printf("\t>>> Proceso hijo %d con pid %d <<<\n\n", np, getpid());

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
			printf("Proceso hijo con id %d con pid %d y numero mayor =  %d  \n\n", proc>>8 , pid, resultado);
		
         }
         else if(proc >> 8 ==1)
         {
	
			read( pipefd[0], &resultado, sizeof(int) );
			printf("Proceso hijo con id %d con pid %d y numero menor =  %d  \n\n", proc>>8 , pid, resultado);
		
         }
         if(proc >> 8 ==2)
         {
	
			read( pipefd[0], &resultado, sizeof(int) );
			printf("Proceso hijo con id %d con pid %d y promedio =  %d  \n\n", proc>>8 , pid, resultado);
		
         }


		if((proc>>8) == 3){
			resultado2 = reservarMemoria();
			read( pipefd[0], resultado2, sizeof(int)*N );
			printf("Proceso hijo con pid %d ordenando\n\n", pid);
			imprimirArreglo(resultado2);
			free(resultado2);
		}
		
	}
	close( pipefd[0] );
}

void ordenarArreglo( int datos[] ){
	register int n, m;
	int aux;

  	for ( n = 0; n < N; n++){
   		for ( m = 0; m < (N - n - 1); m++){
      			if (datos[m] > datos[m+1]){
       				aux = datos[m];
        			datos[m]   = datos[m+1];
        			datos[m+1] = aux;
      			}
    		}
  	}
}

int promedioArreglo( int datos[] ){
	register int n;
   	int suma = 0;
	int  promedio;

        for( n = 0; n < N; n++){
		suma += datos[n];
        }

	promedio = suma/N;
        return promedio;
}

int menorArreglo( int datos[] ){
        register int n;
        int menor;
        menor = datos[0];
        for( n = 0; n < N; n++){
                if( datos[n] < menor){
                        menor = datos[n];
                }
        }
        return menor;
}


int mayorArreglo( int datos[] ){
	register int n;
	int mayor;
	mayor = datos[0];

	for( n = 0; n < N; n++){
                if( datos[n] > mayor){
			mayor = datos[n];
		}
        }
	return mayor;
}

void imprimirArreglo( int datos[] ){
	register int n;
        for( n = 0; n < N; n++){
		if( !(n % 16))
			printf("\n");
        	printf("%4.d ", datos[n]);
        }
	printf("\n");
}

void llenarArreglo( int datos[] ){
        register int n;
        for( n = 0; n < N; n++){
                datos[n] = rand() % 4096;
        }
}

int * reservarMemoria( void ){
	int *mem;
	mem = (int *)malloc( sizeof(int)*N );
	if( !mem ){
		perror("Error al asignar memoria\n\n");
		exit(EXIT_FAILURE);
	}
	return mem;
}



//Dos modulos mas, ordenar (burbuja) y promedio, un proceso para cada tareita (4)
//Para el viernes entregarlo en lab
