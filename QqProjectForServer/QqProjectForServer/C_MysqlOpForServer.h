#pragma once
#include <string>
#include "Mysql_Op.h"

using namespace std;

class C_MysqlOpForServer
{
public:
	C_MysqlOpForServer(void);
	~C_MysqlOpForServer(void);
	static Mysql_Op thMysql_Op;
	static bool OperatorForLogIn(string Username,string Pwd);
	static bool OperatorForGetList(string UserName);
};

