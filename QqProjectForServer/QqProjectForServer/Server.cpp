#include "StdAfx.h"
#include "Server.h"
#include <iostream>
#include <windows.h>
#include <string>
#define PORT 5000
#pragma comment(lib,"wsock32.lib")
using namespace std;
Server::Server(void)
{
}


Server::~Server(void)
{
}

int Server::Init(){

	//socket
	WORD wVR;
	WSADATA wsaData;
	wVR=MAKEWORD(1,1);
	int res =WSAStartup(wVR,(LPWSADATA)&wsaData);
	if(res < 0){
		printf("socket file error");
		return -1;
	}

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	//第一个参数选择协议
	//第二个参数选择类型 数据流还是数据报
	//SOCK_STREAM for tcp  && SOCK_DGRAM for udp
	//第三个参数一般为0
	//返回值为整型，若小于零则出错
	if(sockfd<0){
		//失败
		printf("error");
		return -1;
	}else{
		//成功
		printf("successful\n");
		
	
	}
	struct sockaddr_in addrServer;
	//初始化结构体
	memset(&addrServer,0,sizeof(addrServer));
	addrServer.sin_family = AF_INET; //ipv4协议 
	addrServer.sin_port = htons(PORT);//转化端口号整型的cpu读取方式
	
	//INADDR_ANY 让系统指定ip
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //server的地址

		//绑定函数
    res = bind(sockfd,(struct sockaddr *)&addrServer,sizeof(addrServer));
	if(res < 0){
		printf("bind error");
		return -1;
	}else{
		printf("bind successful\n");
	}	
	//监听
	res = listen(sockfd,1);

	if(res<0){
		printf("listen error");
			return -1;
	
	}else{
		printf("listen successful\n");	
	}

	return 1;

}
int Server::Accept(int SerSock){

	struct sockaddr_in ServerAddr;
	int szServerAddr=sizeof(ServerAddr);
	newSockFd = accept(sockfd,(struct sockaddr *)&ServerAddr,&szServerAddr);
	//newSockfd 中保存客户端的信息

	if(newSockFd<0){
		return -1;
	}

	return 1;
}
int Server::Recv(int ClientSocket,char * Buf){
	//Buf存储接受数据
	int	res = recv(ClientSocket,Buf,100,0);
	if(res < 0){
		//printf("recv error!");
		return -1;
	}
	//printf ("recv data=[%s]\n",Buf);
	return 1;

}
int Server::SendMsg(int ClientSocket,const char *Msg){
	//scanf("%s",sendbuf);
	//发送函数 返回值大于表示发送成功 且为发送成功数据的字节数
	int res =send(ClientSocket,Msg,strlen(Msg),0);
	if(res<0){
		printf("send error");
		return -1;
	}
	printf("send success =[%s]\n",Msg);

	return 1;

}
void Server::CloseClient(int ClientSocket){

	//关闭连接
	closesocket(ClientSocket);
	//关闭socket
	//closesocket(sockfd);

}
int Server::RecvForMap(map<string,string> &Buf){
		//将接受的字符串转化为map
	char CharBuf[1024]={0};
	if(Recv(newSockFd,CharBuf)<0) {return -1 ;};
	//此时已经得到字符串 将字符串 Charbuf读取且转为 map
	char * times=CharBuf;
	char Key[100];
	char value[100];
	//循环解析键值对
	while(*times!='\0'){
		sscanf(times,"%[^=]=%[^;]",Key,value);  
		times=strstr(times,";")+1;
		//存储
		string SKey=Key;
		string SValue=value;
		Buf[SKey]=SValue;
	}
	return 1;

}
int Server::SendMap(int ClientSocket,map<string,string> Msg){

		string Sbuf="";
		map<string, string>::iterator it=Msg.begin();
		while(it!=Msg.end()){
			char Buf[100];
			const char *key=(it->first).c_str();
			const char *value=(it->second).c_str();
			sprintf(Buf,"%s=%s;",key,value);
			Sbuf+=Buf;
			it++;
		}
		const char *SendChar=Sbuf.c_str();
		if(SendMsg(ClientSocket,SendChar)<0) {return -1;};
		return 1;	
	
}