#include <stdio.h>
#include <string.h>

void imprimir(char *imp);
int main()
{
	
double x=2.1;
char temporal[100];
char datos[100]="insert into panel_registro values(1,";
sprintf(temporal,"%lf,",x);
strcat(datos,temporal);
strcat(datos,"now())");

imprimir(datos);

return 0;	
}

void imprimir(char * imp)
{
	
printf("\n--->%s",imp);	
}

