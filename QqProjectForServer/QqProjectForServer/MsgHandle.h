#pragma once
#include <map>
#include <string>
#include <iostream>
#include "C_MysqlOpForServer.h"
using namespace std;
//ר�ŵ���Ϣ������
class CMsgHandle
{
public:
	CMsgHandle(void);
	~CMsgHandle(void);
	
	//��ӡ��Ϣmap
	static void PrintfMsg(map<string,string> ReceMsg);
	//����ҵ������ָ��������
	static bool HandleMsg(map<string,string> ReceMsg);
	static bool HandleForLogIn(string username,string pwd);
	static bool handleForGetList(string username);
	static bool HandleForSendMsg(string FromUser,string ToUser,string Text);


};

