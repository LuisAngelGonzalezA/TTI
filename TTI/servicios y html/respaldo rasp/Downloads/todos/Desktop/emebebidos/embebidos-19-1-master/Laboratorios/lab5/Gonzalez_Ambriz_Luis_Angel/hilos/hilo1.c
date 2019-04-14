#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


void * suma( void * arg);
void * resta( void * arg);
void * multi( void * arg);
void * divi( void * arg);
int num=12,num2=12;
int main()
{

	int * res_suma,*res_resta,*res_mult,*res_div;
	pthread_t tid_sum,tid_resta,tid_multi,tid_divi;
	printf("Probando hilos\n");
	pthread_create(&tid_sum,NULL,suma,NULL);
	pthread_create(&tid_resta,NULL,resta,NULL);
	pthread_create(&tid_multi,NULL,multi,NULL);
	pthread_create(&tid_divi,NULL,divi,NULL);


	pthread_join(tid_sum,  (void **) &res_suma);
	pthread_join(tid_resta,(void **) &res_resta);
	pthread_join(tid_multi,(void **) &res_mult);
	pthread_join(tid_divi, (void **)&res_div);


	printf("suma es:%d\n", *res_suma);
	printf("resta es:%d\n", *res_resta);
	printf("multiplicación es:%d\n", *res_mult);
	printf("divición es:%d\n", *res_div);


	return 0;

}

void * suma(void * arg){

	int *res=(int *)malloc(sizeof(int));
	*res=num+num2;
	pthread_exit((void*)  res);

}



void * resta(void * arg){


	int *res=(int *)malloc(sizeof(int));
	*res=num-num2;
	pthread_exit((void*)  res);
	
}

void * multi(void * arg){


	static int res;
	res=num*num2;
	pthread_exit((void*)  &res);

	
}

void * divi(void * arg){

	static int res;
	res=num/num2;
	pthread_exit((void*)  &res);

	
}





/*

 Formas de guardas valores es :
 	- Reservar memoria en malloc
 	- Reservar una variable usamos el static 

*/