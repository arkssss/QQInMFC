#include "StdAfx.h"
#include "MsgHandle.h"
#include "Msg.h"
#include "ConnectMap.h"

CMsgHandle::CMsgHandle(void)
{
}


CMsgHandle::~CMsgHandle(void)
{
}


void CMsgHandle::PrintfMsg(map<string,string> ReceMsg){

	map<string, string>::iterator it=ReceMsg.begin();
	while(it!=ReceMsg.end()){
		cout<<it->first<<"="<<it->second<<endl;
		it++;
	}
	return ;
}


bool CMsgHandle::HandleMsg(map<string,string> ReceMsg){
	//��Ϣ������
	string BsType=ReceMsg["BuisType"];
	//���ҵ������

	//��½����
	if(BsType=="LogIn") { 
		if(HandleForLogIn(ReceMsg["UserName"],ReceMsg["PassWord"])){
			//�˴���½�ɹ�,���԰�sockte
			//�ȸ�ֵΪ-1���������߳��и�ֵΪsocket
			CConnectMap::DictForConnected[CMsg::LogicMsg["UserName"]]=-1;
			return true;}
			return false;
	}else if(BsType=="GetFriendList") {
		if(handleForGetList(ReceMsg["UserName"])){return true;}
			return false;
	}else if(BsType=="SendMsg"){
		if(HandleForSendMsg(ReceMsg["FromUser"],ReceMsg["ToUser"],ReceMsg["Text"])) {return true;}
			return false;
	}

	return false;

}


//��½ҵ��
bool CMsgHandle::HandleForLogIn(string username,string pwd){
		//��½ҵ��
	if(C_MysqlOpForServer::OperatorForLogIn(username,pwd)) return true;
		return false;

}


bool CMsgHandle::handleForGetList(string username){
	//���غ����б�
	if(C_MysqlOpForServer::OperatorForGetList(username)) return true;
		return false;

}


bool CMsgHandle::HandleForSendMsg(string FromUser,string ToUser,string Text){
	//������Ϣ�����߼�
	//������˵ ����Է����� ��ֱ��ת�����Ҵ������ݿ�
	//��Է������ߣ���ֻ�����ݿ�	
	//�˲���ֻ�ܴ����ݿ�


	return true;

}