#pragma once
#include <map>
#include <string>

using namespace std;

class CMsg
{
public:
	CMsg(void);
	~CMsg(void);
	static map<string,string> SendMsg;
	static map<string,string> ReceMsg;
	static void ClearMsg(map<string,string> &SendMsg) ;
};

