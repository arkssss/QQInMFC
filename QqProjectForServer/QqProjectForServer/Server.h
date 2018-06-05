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
	
	//�������ܺ���
	int Recv(int ClientSocket,char * Buf);
	int RecvForMap(map<string,string> &Buf);


	//�������ͺ���
	int SendMsg(int ClientSocket,const char *Msg);
	int SendMap(int ClientSocket,map<string,string> Msg);


	void CloseClient(int ClientSocket);

	




};

