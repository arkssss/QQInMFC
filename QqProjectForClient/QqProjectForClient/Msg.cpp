#include "StdAfx.h"
#include "Msg.h"


CMsg::CMsg(void)
{
}


CMsg::~CMsg(void)
{
}

	//������̬����
	map<string,string> CMsg::SendMsg;
	map<string,string> CMsg::ReceMsg;


	//�����Ϣ��
	void CMsg::ClearMsg(map<string,string> &SendMsg){
		SendMsg.clear();
		return ;
	}
