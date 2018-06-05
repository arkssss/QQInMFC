// QqProjectForServer.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "Function.h"
#include "Server.h"
#include "MsgHandle.h"
#include "ConnectMap.h"
#include "Msg.h"
//ȫ�ֱ�������
Server ThServer;


//�̴߳������������Ա�֤���Ӷ���ͻ���
DWORD WINAPI ReceThread(LPVOID lpParam){
	int * ClientSocket = (int *) lpParam;
	//���ܴ�ʱ�������׽���
	while(1){ 
		int CurrentToSocket=*ClientSocket;
		//ѭ��Ϊ�����ӽ�����Ϣ
		if(ThServer.RecvForMap(CMsg::ReceMsg)<0) {
			printf("Connect Close ,Has Exited Thread!\n");
			ThServer.CloseClient(*ClientSocket);
			break;}


		//��ʱ���ܵ��ͻ��˵���Ϣ
		CMsgHandle::PrintfMsg(CMsg::ReceMsg);
		if(!CMsgHandle::HandleMsg(CMsg::ReceMsg)) {printf("Handle Msg error!\n");}	


			
		//��socket������ת���߼�
		if(CConnectMap::DictForConnected[CMsg::LogicMsg["UserName"]]==-1) {
			CConnectMap::DictForConnected[CMsg::ReceMsg["UserName"]]=*ClientSocket;
		}

		//����ת���߼�
		if( CConnectMap::DictForConnected.find(CMsg::ReceMsg["ToUser"])!=CConnectMap::DictForConnected.end() && CMsg::ReceMsg["BuisType"]=="SendMsg"){
			//��ToUser������Ϊת���߼���ʱ�� ��ִ������ת��
			CMsg::SendMsg["Text"]=CMsg::ReceMsg["Text"];
			CMsg::SendMsg["FromUser"]=CMsg::ReceMsg["FromUser"];
			CurrentToSocket=CConnectMap::DictForConnected[CMsg::ReceMsg["ToUser"]];
		}


		//���۲��ҽ����ζ�������Ϣ
		if(ThServer.SendMap(CurrentToSocket,CMsg::SendMsg)<0) {printf("SendMsg error;");}



		//�����Ϣ�ҵȴ���һ�ν���
		CMsg::LogicMsg.clear();
		CMsg::ReceMsg.clear();
		CMsg::SendMsg.clear();
		

	}

	return 1;

}


int _tmain(int argc, _TCHAR* argv[])
{

	//��ʼ�����ݿ�ͷ������׽���
	if(ThServer.Init()<0) {printf("server init error!\n");exit(1);};

	while(1){
		//ѭ������
		ThServer.Accept(ThServer.sockfd);
	    CreateThread(NULL,0,ReceThread,&ThServer.newSockFd,0,0);

	}
	getchar();
	return 0;
}

