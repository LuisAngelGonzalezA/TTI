#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NOM_ARCHIVO  "example.txt"
#define NUM_ELEM      100

int main(void)
{
   FILE *salida;
   int num[NUM_ELEM];
   int i;
   
   srand((unsigned) time(NULL));
   
   /* Generacion de los numeros y almacenamiento de estos en el array */
   for (i = 0; i < NUM_ELEM; i++)
      num[i] = rand() % NUM_ELEM;
   
   /* 1) Apertura del archivo */
   salida = fopen(NOM_ARCHIVO, "a+");
   if (salida == NULL){
      perror(NOM_ARCHIVO);
      return EXIT_FAILURE;
   }
   
   /* 2) Impresion de cada numero en el archivo */
   for (i = 0; i < NUM_ELEM; i++)
    { 
      salida = fopen(NOM_ARCHIVO, "a+");
      fprintf(salida, "%d\n",num[i]);
      sleep(1);
      fclose(salida);
   }
   /* 3) Cierre del archivo */
   
   
   return EXIT_SUCCESS;
}