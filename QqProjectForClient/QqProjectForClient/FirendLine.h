#pragma once
#include "afxcmn.h"


// CFirendLine �Ի���

class CFirendLine : public CDialogEx
{
	DECLARE_DYNAMIC(CFirendLine)

public:
	CFirendLine(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFirendLine();

// �Ի�������
	enum { IDD = IDD_DIALOG_FriendLine };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	afx_msg void OnNMDblclkListFriend(NMHDR *pNMHDR, LRESULT *pResult);


};
