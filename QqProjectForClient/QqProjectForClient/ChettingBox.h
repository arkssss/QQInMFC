#pragma once


// CChettingBox 对话框

class CChettingBox : public CDialogEx
{
	DECLARE_DYNAMIC(CChettingBox)

public:
	CChettingBox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChettingBox();

// 对话框数据
	enum { IDD = IDD_DIALOG_MsgBox };
	//对话人的UserName
	CString m_Caption;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString m_SendMsg;
	CString m_ReceMsg;
};
