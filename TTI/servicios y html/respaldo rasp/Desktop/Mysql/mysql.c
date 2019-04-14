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
	char *database="tornasol";
	
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


	 if (mysql_query(con, "SELECT * FROM panel_registro")) 
  {
      mysql_error(con);
  }
  
  res = mysql_store_result(con);
  
  if (res == NULL) 
  {
      mysql_error(con);
  }

  int num_fields = mysql_num_fields(res);
  printf("Id \t Voltaje \t Fecha \n");
  while ((row = mysql_fetch_row(res))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%5s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
  
  
  printf("\n\nLa consulta deseada es :\n");
  
  
  if (mysql_query(con, "select*from panel_registro order by fecha desc limit 1")) 
  {
      mysql_error(con);
  }
  
  res = mysql_store_result(con);
  
  if (res == NULL) 
  {
      mysql_error(con);
  }

  num_fields = mysql_num_fields(res);
  
  while ((row = mysql_fetch_row(res))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%10s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
  
  printf("\n\tInsertamos en la base y consultamos nuevo registro\n");
  
  if (mysql_query(con, "insert into panel_registro values(1,0.0,now())")) 
  {
      mysql_error(con);
  }
  if (mysql_query(con, "select*from panel_registro order by fecha desc limit 1")) 
  {
      mysql_error(con);
  }
  
  res = mysql_store_result(con);
  
  if (res == NULL) 
  {
      mysql_error(con);
  }

  num_fields = mysql_num_fields(res);
  
  while ((row = mysql_fetch_row(res))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s\t", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }

	mysql_free_result(res);
	mysql_close(con);



	return 0;
}
