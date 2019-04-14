#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void mover_servo();
int main(int argc, char* argv[])
{
    
    mover_servo();


}
void mover_servo()
{
    time_t t;
  struct tm *tm;
  char fechayhora[100];
  int tiempo_estimado=1;
  int h,m,s;
  int min_bandera;
  t=time(NULL);
  tm=localtime(&t);
  strftime(fechayhora, 100, "%H", tm);
  h=atoi(fechayhora);
  strftime(fechayhora, 100, "%M", tm);
  m=atoi(fechayhora);
  min_bandera=m+tiempo_estimado;
  if(min_bandera>=59)
  {
    min_bandera=min_bandera - 60;
  }
  //else
    
  
  strftime(fechayhora, 100, "%S", tm);
  s=atoi(fechayhora);

  printf ("Hoy es: %d : %d : %d\n\n", h,m,s);
  printf("\nTiempo para acabar = %d  min\n",min_bandera);
 	
  while(1)
 	{
    
  printf("\nTiempo para acabar = %d  min\n",min_bandera);
  //printf("-->\n");
  t=time(NULL);
  tm=localtime(&t);

 		if(m==min_bandera)
 		{
 			printf("\nYa a pasado el tiempo ya volvemos a monitorear\n");
 			min_bandera=m+tiempo_estimado;
      if(min_bandera>=59)
      {
        min_bandera=min_bandera - 60;
      }
  
 			
 		}
 		strftime(fechayhora, 100, "%M", tm);
 	 	m=atoi(fechayhora);
    strftime(fechayhora, 100, "%S", tm);
    s=atoi(fechayhora);
 	 	usleep(1000000);
 	 	
    printf ("\r\t->Hoy es:  %d  :  %d\r", m,s);
    



 	}

}
