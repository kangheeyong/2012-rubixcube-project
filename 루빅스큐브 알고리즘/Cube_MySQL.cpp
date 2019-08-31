#include "Cube_MySQL.h"
#include <string.h>


Cube_MySQL :: Cube_MySQL()
{
	server = "localhost";
	user = "root";
	password = "tiger";
	database = "cube";
	port = 3306;
	mysql = mysql_init(NULL);
}
void Cube_MySQL ::MySQL_Connect() // Connect to SQL
{
	if(!mysql_real_connect(mysql, server, user, password, database, port, NULL, 0))
	{
		fprintf(stderr, "%s", mysql_error(mysql));
		exit(1);
	}
}
void Cube_MySQL ::MySQL_Close()
{
	mysql_close(mysql);
}
void Cube_MySQL ::MySQL_Query(char * p) 
{
	mysql_query(mysql, p);
}
char* Cube_MySQL :: MySQL_Data()
{
	res = mysql_use_result(mysql);

	if(res == NULL ) return NULL; // 검색햇는데 없는경우 res값이 널로 나온다
		
	row = mysql_fetch_row(res);	
	
	if(row == NULL) return NULL; // 빼도 되나??

	return row[0];
}
void Cube_MySQL :: MySQL_free()
{
	while(mysql_fetch_row(res) != NULL);
	mysql_free_result(res);
}