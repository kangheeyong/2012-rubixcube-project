#pragma comment(lib, "libmySQL.lib")
#pragma comment(lib, "ws2_32.lib")


#include <my_global.h>
#include <mysql.h>

class Cube_MySQL
{
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server;
	char *user;
	char *password; 
	char *database;
	int port;	
public:
	Cube_MySQL();
	void MySQL_Connect();
	void MySQL_Close();
	void MySQL_Query(char * p);
	char* MySQL_Data();
	void MySQL_free();
};

