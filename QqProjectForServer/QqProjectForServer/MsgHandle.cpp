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
	//消息处理函数
	string BsType=ReceMsg["BuisType"];
	//获得业务类型

	//登陆类型
	if(BsType=="LogIn") { 
		if(HandleForLogIn(ReceMsg["UserName"],ReceMsg["PassWord"])){
			//此处登陆成功,可以绑定sockte
			//先赋值为-1，再在主线程中赋值为socket
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


//登陆业务
bool CMsgHandle::HandleForLogIn(string username,string pwd){
		//登陆业务
	if(C_MysqlOpForServer::OperatorForLogIn(username,pwd)) return true;
		return false;

}


bool CMsgHandle::handleForGetList(string username){
	//返回好友列表
	if(C_MysqlOpForServer::OperatorForGetList(username)) return true;
		return false;

}


bool CMsgHandle::HandleForSendMsg(string FromUser,string ToUser,string Text){
	//处理消息发送逻辑
	//总提来说 如果对方在线 则直接转发，且存入数据库
	//如对方不在线，且只存数据库	
	//此步骤只管存数据库


	return true;

}