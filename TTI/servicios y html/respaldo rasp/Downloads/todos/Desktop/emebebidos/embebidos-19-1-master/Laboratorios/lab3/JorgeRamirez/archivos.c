#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void guarda_datos(float datos[]){
	FILE *ap_arch;
	register int n;

	ap_arch = fopen("seno.dat", "w");
	if(!ap_arch){
		perror("error al abrir el archivo");
	}
	for(n= 0; n<MUESTRAS; n++){
		fprintf(ap_arch, "%f \n", datos[n]);
	}
	fclose(ap_arch);
}
