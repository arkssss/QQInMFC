
// QqProjectForClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQqProjectForClientApp:
// �йش����ʵ�֣������ QqProjectForClient.cpp
//

class CQqProjectForClientApp : public CWinApp
{
public:
	CQqProjectForClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQqProjectForClientApp theApp;