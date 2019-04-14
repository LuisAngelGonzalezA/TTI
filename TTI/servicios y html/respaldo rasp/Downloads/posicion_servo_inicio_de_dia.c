/* librerías que usaremos */

/* gcc posicion_servo_inicio_de_dia.c -o posicion_servo_inicio_de_dia `mysql_config --cflags` `mysql_config --libs`
*/
#include <mysql.h> /* libreria que nos permite hacer el uso de las conexiones y consultas con MySQL */
#include <stdio.h> /* Para poder usar printf, etc. */
#include <stdlib.h>
#include <string.h>


int main()
{
	char coordenada_x[100],coordenada_y[100];
	MYSQL *conn; /* variable de conexión para MySQL */
	MYSQL_RES *res; /* variable que contendra el resultado de la consuta */
	MYSQL_ROW row; /* variable que contendra los campos por cada registro consultado */
	char *server = "localhost"; /*direccion del servidor 127.0.0.1, localhost o direccion ip */
	char *user = "root"; /*usuario para consultar la base de datos */
	char *password = "root"; /* contraseña para el usuario en cuestion */
	char *database = "tt1Pruebas"; /*nombre de la base de datos a consultar */
	conn = mysql_init(NULL); /*inicializacion a nula la conexión */

	/* conectar a la base de datos */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{ /* definir los parámetros de la conexión antes establecidos */
		fprintf(stderr, "%s\n", mysql_error(conn)); /* si hay un error definir cual fue dicho error */
		exit(1);
	}

	/* enviar consulta SQL */
	if (mysql_query(conn, "select*from posicion_servo where date(now()) between fecha_inicio and fecha_fin "))
	{ /* definicion de la consulta y el origen de la conexion */
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);
	printf("Posicion x\t\tPosicion y\tMes\tEstacion\t\tFecha inicio\t\tEstacion fin\t\t\n\n");
	while ((row = mysql_fetch_row(res)) != NULL) /* recorrer la variable res con todos los registros obtenidos para su uso */
	{
		//printf("%9s\t%9s\t%9s\t\t%9s\t\t%9s\t\t%9s\n", row[0],row[1],row[2],row[3],row[4],row[5]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
		strcat(coordenada_x,row[0]);
		strcat(coordenada_x,"\n");
		strcat(coordenada_y,row[1]);
		strcat(coordenada_y,"\n");
	}

	/* se libera la variable res y se cierra la conexión */
	mysql_free_result(res);
	mysql_close(conn);




	FILE *fichero;
	
	char lectura[100];
	
	fichero=fopen("/home/luis/Escritorio/archivo.txt","wt"); //Abrimos el fichero para solo lectura
	fputs(coordenada_x,fichero);
	fputs(coordenada_y,fichero);
	fclose(fichero);








}
