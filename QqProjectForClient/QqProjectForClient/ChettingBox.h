#pragma once


// CChettingBox �Ի���

class CChettingBox : public CDialogEx
{
	DECLARE_DYNAMIC(CChettingBox)

public:
	CChettingBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChettingBox();

// �Ի�������
	enum { IDD = IDD_DIALOG_MsgBox };
	//�Ի��˵�UserName
	CString m_Caption;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString m_SendMsg;
	CString m_ReceMsg;
};
