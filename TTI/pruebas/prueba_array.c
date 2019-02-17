#include <stdio.h>
#include <stdlib.h>
int * datos();
int main()
{
	int *a;
	a=datos();
	printf("->%d",a[3]);
	
}



int * datos()
{
	
	int *a;
	a=(int*)malloc(4*sizeof(int));
	a[0]=1;
	a[1]=21111;
	a[2]=3;
	a[3]=4001010;
	return a;
}
