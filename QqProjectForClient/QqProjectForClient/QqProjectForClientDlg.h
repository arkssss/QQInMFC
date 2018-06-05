
// QqProjectForClientDlg.h : 头文件
//

#pragma once
#include "Client.h"
#include "Msg.h"
#include "MsgHandle.h"
#include "PresonalInfo.h"

// CQqProjectForClientDlg 对话框
class CQqProjectForClientDlg : public CDialogEx
{
// 构造
public:
	CQqProjectForClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QQPROJECTFORCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_Username;
	CString m_Password;
	static Client ThClient;
	static CPresonalInfo PresonalInfo;
	afx_msg void OnBnClickedOk();
};
