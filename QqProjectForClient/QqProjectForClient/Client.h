#pragma once
#include <string>
#include <map>
#include "Function.h"
using namespace std;
class Client
{
public:
	Client(void);
	~Client(void);
	int sockfd;
	int Init(char * ch);
	//返回-1说明错误
	int SendMsg (const char * ch);
	int SendMap(map<string,string> Msg);

	//发送函数
	int Recv(char * Buf);
	int RecvForMap(map<string,string> &Buf);



	void CloseClient();


	
	//int SendMsgForStruct(CStudent Student);
	//void StructToChar(char * buf,CStudent Student);


	
};

