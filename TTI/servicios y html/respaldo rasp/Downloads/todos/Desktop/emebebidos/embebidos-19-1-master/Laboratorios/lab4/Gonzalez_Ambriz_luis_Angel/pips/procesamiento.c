#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "defs.h"

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

