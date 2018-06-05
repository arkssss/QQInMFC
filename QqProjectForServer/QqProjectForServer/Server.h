#pragma once
#include <map>
#include <string>
using namespace std;
class Server
{
public:
	Server(void);
	~Server(void);
	int sockfd;
	int newSockFd;
	int Accept(int SerSock);
	int Init();
	map<string,int> sock;
	
	//两个接受函数
	int Recv(int ClientSocket,char * Buf);
	int RecvForMap(map<string,string> &Buf);


	//两个发送函数
	int SendMsg(int ClientSocket,const char *Msg);
	int SendMap(int ClientSocket,map<string,string> Msg);


	void CloseClient(int ClientSocket);

	




};

