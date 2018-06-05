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
	addrServer.sin_addr.S_un.S_addr = inet_addr(ch); //回环地址  inet_addr函数可以将十进制点分法的ip地址 转化为32为的二进制
													 //还可以检测无效的ip地址			
	

	 res = connect(sockfd,(struct sockaddr *)&addrServer,sizeof(addrServer));
	if(res < 0){
		printf("connect error");
		return -1;
	}else{
	
	    printf("connect successful\n");
	}
	//write()函数

}
int Client::SendMsg (const char * ch){
	//scanf("%s",sendbuf);
	//发送函数 返回值大于表示发送成功 且为发送成功数据的字节数
	int res =send(sockfd,ch,strlen(ch),0);
	if(res<0){
		printf("send error");
		return -1;
	}
//	printf("send success =[%s]\n",ch);
	return 1;
}
int Client::Recv(char * Buf){
	//Buf存储接受数据
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
	//将msg发送
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
			//将接受的字符串转化为map
		char CharBuf[1024]={0};
		if(Recv(CharBuf)<0) {return -1 ;};
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