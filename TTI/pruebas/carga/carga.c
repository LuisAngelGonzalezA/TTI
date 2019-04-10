#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <mysql/mysql.h>

double corriente_mysql=.01;
double mysql_corriente_bateria()
{
	
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row; 	 	


	char *server="localhost";
	char *user="TT";
	char *pass="TT";
	char *database="tornasol";
	
	con=mysql_init(NULL);
	if(!mysql_real_connect(con,server,user,pass,database,0,NULL,0))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"select b.corriente from historial_bateria_panel hbp,bateria b where hbp.id_bateria=b.id_bateria and hbp.activo=1"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	double dato=0.0;
	//printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		{
			printf("%s\n",row[0]);
			 dato=atof(row[0]);
			
		}
		
	mysql_free_result(res);
	mysql_close(con);
		
	return dato;
}
int etapa_de_bateria()
{

  int estado_bateria=0;
  double corriente_de_bateria_usada=mysql_corriente_bateria();
  corriente_mysql*=1000;
  printf("\n Corriente entrante = %lf \n",corriente_mysql); 
  if(corriente_mysql<=0.0)
  {
    estado_bateria=4;
  }
  else if(corriente_de_bateria_usada<=corriente_mysql || corriente_mysql>=corriente_de_bateria_usada/5 || corriente_mysql>=corriente_de_bateria_usada/4)
  {
   estado_bateria=1;
  }
  else if(corriente_mysql<=corriente_de_bateria_usada/20)
  {
    estado_bateria=3;
  }
  else
  {
    estado_bateria=2;
  }
   
  
  return estado_bateria;

}

int main()
{          
	
	
	printf("Estapa de la bateria es : %d \n",etapa_de_bateria());                                   

	return 0;
}



