#include "StdAfx.h"
#include "Msg.h"


CMsg::CMsg(void)
{
}


CMsg::~CMsg(void)
{
}

	//声明静态变量
	map<string,string> CMsg::SendMsg;
	map<string,string> CMsg::ReceMsg;


	//清空消息类
	void CMsg::ClearMsg(map<string,string> &SendMsg){
		SendMsg.clear();
		return ;
	}
