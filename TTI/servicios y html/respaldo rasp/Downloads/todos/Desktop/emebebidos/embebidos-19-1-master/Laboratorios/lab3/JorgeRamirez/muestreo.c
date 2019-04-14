#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "archivos.h"
#include "procesamiento.h"
#include "defs.h"

#define MUESTRAS 512

void genera_seno(float seno[]);
void guarda_datos(float datos[]);

int main(){
	float seno[MUESTRAS];
	genera_seno(seno);
	guarda_datos(seno);
	return 0;
}

