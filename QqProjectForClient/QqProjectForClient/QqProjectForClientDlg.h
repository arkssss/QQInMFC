
// QqProjectForClientDlg.h : ͷ�ļ�
//

#pragma once
#include "Client.h"
#include "Msg.h"
#include "MsgHandle.h"
#include "PresonalInfo.h"

// CQqProjectForClientDlg �Ի���
class CQqProjectForClientDlg : public CDialogEx
{
// ����
public:
	CQqProjectForClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQPROJECTFORCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
