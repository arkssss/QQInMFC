#include "StdAfx.h"
#include "Client.h"
#include <string>
#include <iostream>
#include <windows.h>
#define PORT 5000
#pragma comment(lib,"wsock32.lib")
using namespace std;

Client::Client(void)
{
}
Client::~Client(void)
{
}
int Client::Init(char * ch){
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
	addrServer.sin_addr.S_un.S_addr = inet_addr(ch); //�ػ���ַ  inet_addr�������Խ�ʮ���Ƶ�ַ���ip��ַ ת��Ϊ32Ϊ�Ķ�����
													 //�����Լ����Ч��ip��ַ			
	

	 res = connect(sockfd,(struct sockaddr *)&addrServer,sizeof(addrServer));
	if(res < 0){
		printf("connect error");
		return -1;
	}else{
	
	    printf("connect successful\n");
	}
	//write()����

}
int Client::SendMsg (const char * ch){
	//scanf("%s",sendbuf);
	//���ͺ��� ����ֵ���ڱ�ʾ���ͳɹ� ��Ϊ���ͳɹ����ݵ��ֽ���
	int res =send(sockfd,ch,strlen(ch),0);
	if(res<0){
		printf("send error");
		return -1;
	}
//	printf("send success =[%s]\n",ch);
	return 1;
}
int Client::Recv(char * Buf){
	//Buf�洢��������
	int	res = recv(sockfd,Buf,100,0);
	if(res < 0){
		printf("recv error!");
		return -1;
	
	}
	printf ("recv data=[%s]\n",Buf);

}
void Client::CloseClient(){

	closesocket(sockfd);
}
/*
void Client::StructToChar(char * buf,CStudent Student){
	Student.Name+='\n';
	Student.ProType+='\n';
	Student.Pwd+='\n';
	char *a=(char *)Student.Name.c_str();
	char *b=(char *)Student.ProType.c_str();
	char *c=(char *)Student.Pwd.c_str();
	sprintf(buf,"%s%s%s",a,b,c);
	return ;
}
*/
/*
int Client::SendMsgForStruct(CStudent Student){
	char buf[1024]={0};
	StructToChar(buf,Student);
	if(SendMsg(buf)<0) {return  -1;}
	return 1;
}
*/

int Client::SendMap(map<string,string> Msg){
	//��msg����
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
		if(SendMsg(SendChar)<0) {return -1;};
		return 1;	
}
int Client::RecvForMap(map<string,string> &Buf){
			//�����ܵ��ַ���ת��Ϊmap
		char CharBuf[1024]={0};
		if(Recv(CharBuf)<0) {return -1 ;};
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