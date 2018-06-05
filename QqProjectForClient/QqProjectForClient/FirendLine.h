#pragma once
#include "afxcmn.h"


// CFirendLine 对话框

class CFirendLine : public CDialogEx
{
	DECLARE_DYNAMIC(CFirendLine)

public:
	CFirendLine(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFirendLine();

// 对话框数据
	enum { IDD = IDD_DIALOG_FriendLine };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	afx_msg void OnNMDblclkListFriend(NMHDR *pNMHDR, LRESULT *pResult);


};
