#pragma once
#include <map>
#include <string>
#include <iostream>
#include "C_MysqlOpForServer.h"
using namespace std;
//专门的消息处理类
class CMsgHandle
{
public:
	CMsgHandle(void);
	~CMsgHandle(void);
	
	//打印消息map
	static void PrintfMsg(map<string,string> ReceMsg);
	//根据业务内容指定服务函数
	static bool HandleMsg(map<string,string> ReceMsg);
	static bool HandleForLogIn(string username,string pwd);
	static bool handleForGetList(string username);
	static bool HandleForSendMsg(string FromUser,string ToUser,string Text);


};

