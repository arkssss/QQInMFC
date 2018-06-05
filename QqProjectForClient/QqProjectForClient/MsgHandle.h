#pragma once
#include <map>
#include <string>
#include <iostream>
using namespace std;
class CMsgHandle
{
public:
	CMsgHandle(void);
	~CMsgHandle(void);

	static void PrintfMsg(map<string,string> ReceMsg);

};

