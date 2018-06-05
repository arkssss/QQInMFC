#include "StdAfx.h"
#include "MsgHandle.h"


CMsgHandle::CMsgHandle(void)
{
}


CMsgHandle::~CMsgHandle(void)
{
}


void CMsgHandle::PrintfMsg(map<string,string> ReceMsg){
	//打印收到的消息
	map<string, string>::iterator it=ReceMsg.begin();
	while(it!=ReceMsg.end()){
		string Key = it->first;
		string Value= it->second;
		string msg=Key+Value;
		//MessageBox(NULL,_T(msg),0,0);
		//cout<<it->first<<"="<<it->second<<endl;
		it++;
	}
	return ;

}