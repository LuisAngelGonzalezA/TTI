#include <stdio.h>
#include <stdlib.h>

void guardar(int *datos);

int main()
{
int valores[6]={1,2,10,0,100,2};
int a=33;
int b=9;
double c=0;
c=a;
c+=(double)b/10;
printf("Valor de b=%lf\n",c);
guardar(valores);



}

void guardar(int *datos)
{
	int i=0;
	for(;i<6;i++)
		printf("\n datos-->%d\n",datos[i]);
	
}
