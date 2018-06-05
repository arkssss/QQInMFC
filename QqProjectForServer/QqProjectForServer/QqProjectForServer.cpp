// QqProjectForServer.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Function.h"
#include "Server.h"
#include "MsgHandle.h"
#include "ConnectMap.h"
#include "Msg.h"
//全局变量声明
Server ThServer;


//线程创建函数，可以保证链接多个客户端
DWORD WINAPI ReceThread(LPVOID lpParam){
	int * ClientSocket = (int *) lpParam;
	//接受此时的链接套接字
	while(1){ 
		int CurrentToSocket=*ClientSocket;
		//循环为此链接接受消息
		if(ThServer.RecvForMap(CMsg::ReceMsg)<0) {
			printf("Connect Close ,Has Exited Thread!\n");
			ThServer.CloseClient(*ClientSocket);
			break;}


		//此时接受到客户端的消息
		CMsgHandle::PrintfMsg(CMsg::ReceMsg);
		if(!CMsgHandle::HandleMsg(CMsg::ReceMsg)) {printf("Handle Msg error!\n");}	


			
		//绑定socket和在线转发逻辑
		if(CConnectMap::DictForConnected[CMsg::LogicMsg["UserName"]]==-1) {
			CConnectMap::DictForConnected[CMsg::ReceMsg["UserName"]]=*ClientSocket;
		}

		//在线转发逻辑
		if( CConnectMap::DictForConnected.find(CMsg::ReceMsg["ToUser"])!=CConnectMap::DictForConnected.end() && CMsg::ReceMsg["BuisType"]=="SendMsg"){
			//当ToUser在线且为转发逻辑的时候 变执行在线转发
			CMsg::SendMsg["Text"]=CMsg::ReceMsg["Text"];
			CMsg::SendMsg["FromUser"]=CMsg::ReceMsg["FromUser"];
			CurrentToSocket=CConnectMap::DictForConnected[CMsg::ReceMsg["ToUser"]];
		}


		//无论查找结果如何都传回信息
		if(ThServer.SendMap(CurrentToSocket,CMsg::SendMsg)<0) {printf("SendMsg error;");}



		//清空消息且等待下一次接受
		CMsg::LogicMsg.clear();
		CMsg::ReceMsg.clear();
		CMsg::SendMsg.clear();
		

	}

	return 1;

}


int _tmain(int argc, _TCHAR* argv[])
{

	//初始化数据库和服务器套接字
	if(ThServer.Init()<0) {printf("server init error!\n");exit(1);};

	while(1){
		//循环监听
		ThServer.Accept(ThServer.sockfd);
	    CreateThread(NULL,0,ReceThread,&ThServer.newSockFd,0,0);

	}
	getchar();
	return 0;
}

