/*
Se debe de instalar previamente 
		sudo apt-get install libmysqlclient.dev
		* 
		* 
	gcc mysql.c -o mysql `mysql_config --cflags` `mysql_config --libs`

*/


#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>



int main(int argc, char const *argv[])
{
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;


	char *server="localhost";
	char *user="TT";
	char *pass="TT";
	char *database="tt1Pruebas";
	
	con=mysql_init(NULL);
	if(!mysql_real_connect(con,server,user,pass,database,0,NULL,0))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
	}

	if(mysql_query(con,"show databases"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res=mysql_use_result(con);
	printf("La base de datos son :\n");
	while((row= mysql_fetch_row(res)) !=NULL)
		printf("%s\n",row[0]);


	 if (mysql_query(con, "SELECT * FROM posicion_servo")) 
  {
      mysql_error(con);
  }
  
  res = mysql_store_result(con);
  
  if (res == NULL) 
  {
      mysql_error(con);
  }

  int num_fields = mysql_num_fields(res);
  
  while ((row = mysql_fetch_row(res))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }

	mysql_free_result(res);
	mysql_close(con);



	return 0;
}
