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
	//��һ������ѡ��Э��
	//�ڶ�������ѡ������ �������������ݱ�
	//SOCK_STREAM for tcp  && SOCK_DGRAM for udp
	//����������һ��Ϊ0
	//����ֵΪ���ͣ���С���������
	if(sockfd<0){
		//ʧ��
		printf("error");
		return -1;
	}else{
		//�ɹ�
		printf("successful\n");
		
	
	}
	struct sockaddr_in addrServer;
	//��ʼ���ṹ��
	memset(&addrServer,0,sizeof(addrServer));
	addrServer.sin_family = AF_INET; //ipv4Э�� 
	addrServer.sin_port = htons(PORT);//ת���˿ں����͵�cpu��ȡ��ʽ
	
	//INADDR_ANY ��ϵͳָ��ip
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //server�ĵ�ַ

		//�󶨺���
    res = bind(sockfd,(struct sockaddr *)&addrServer,sizeof(addrServer));
	if(res < 0){
		printf("bind error");
		return -1;
	}else{
		printf("bind successful\n");
	}	
	//����
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
	//newSockfd �б���ͻ��˵���Ϣ

	if(newSockFd<0){
		return -1;
	}

	return 1;
}
int Server::Recv(int ClientSocket,char * Buf){
	//Buf�洢��������
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
	//���ͺ��� ����ֵ���ڱ�ʾ���ͳɹ� ��Ϊ���ͳɹ����ݵ��ֽ���
	int res =send(ClientSocket,Msg,strlen(Msg),0);
	if(res<0){
		printf("send error");
		return -1;
	}
	printf("send success =[%s]\n",Msg);

	return 1;

}
void Server::CloseClient(int ClientSocket){

	//�ر�����
	closesocket(ClientSocket);
	//�ر�socket
	//closesocket(sockfd);

}
int Server::RecvForMap(map<string,string> &Buf){
		//�����ܵ��ַ���ת��Ϊmap
	char CharBuf[1024]={0};
	if(Recv(newSockFd,CharBuf)<0) {return -1 ;};
	//��ʱ�Ѿ��õ��ַ��� ���ַ��� Charbuf��ȡ��תΪ map
	char * times=CharBuf;
	char Key[100];
	char value[100];
	//ѭ��������ֵ��
	while(*times!='\0'){
		sscanf(times,"%[^=]=%[^;]",Key,value);  
		times=strstr(times,";")+1;
		//�洢
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