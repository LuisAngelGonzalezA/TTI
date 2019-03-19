#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void guardar(int *datos);

int main()
{
double voltaje_mysql=40.9;
double temperatura_mysql=40.1;
double corriente_mysql=5.211;
  char temporal[200]={};
  char datos[400]="insert into sensadoB values(null,(select id_bateria from historial_bateria_panel where activo=1),now(),";
  sprintf(temporal,"%lf",voltaje_mysql);
  strcat(datos,temporal);
  memset(temporal,'\0',100);
  strcat(datos,",");
  sprintf(temporal,"%lf",corriente_mysql);
  strcat(datos,temporal);
  strcat(datos,",");
  memset(temporal,'\0',100);
  sprintf(temporal,"%lf",temperatura_mysql);
  strcat(datos,temporal);
  
  strcat(datos,")");
  printf("\n\n-> %s  \n\n",datos);
	
unsigned char peticion= 0xE1;
int i=0,j=0;

while(j<10)
{
	i=0;
	peticion= 0xE1;
	for(;i<3;i++)
	{
		printf("0x%X\n", peticion);
		peticion++;
	}
	printf("\n");
	j++;
}


int valores[6]={1,2,10,0,100,2};
int a=33;
int b=9;
double c=0;
c=a;
c+=(double)b/10;

//guardar(valores);



}

void guardar(int *datos)
{
	int i=0;
	for(;i<6;i++)
		printf("\n datos-->%d\n",datos[i]);
	
}
