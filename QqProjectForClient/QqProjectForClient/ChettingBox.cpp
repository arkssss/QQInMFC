// ChettingBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QqProjectForClient.h"
#include "ChettingBox.h"
#include "afxdialogex.h"
#include "QqProjectForClientDlg.h"
#include "Msg.h"
#include "Function.h"
// CChettingBox �Ի���

IMPLEMENT_DYNAMIC(CChettingBox, CDialogEx)


//���̵Ľ��ܺ���
DWORD WINAPI ReceiveMsg(LPVOID lpParam){

	CChettingBox *dlg = (CChettingBox *)lpParam;
	
	while(1){
			//����
			CQqProjectForClientDlg::ThClient.RecvForMap(CMsg::ReceMsg);
			CString str;
			(dlg->GetDlgItem(IDC_EDIT1))->GetWindowTextW(str);
			str+=ConvertStringToCString(CMsg::ReceMsg["Text"]);
			str+="\r\n";
			(dlg->GetDlgItem(IDC_EDIT1))->SetWindowTextW(str);
		
	}
	
	return 0;
}



CChettingBox::CChettingBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChettingBox::IDD, pParent)
	, m_SendMsg(_T(""))
	, m_ReceMsg(_T(""))
{

}

CChettingBox::~CChettingBox()
{
	MessageBox(_T("over"));
}

void CChettingBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_SendMsg);
	DDX_Text(pDX, IDC_EDIT1, m_ReceMsg);
}


BEGIN_MESSAGE_MAP(CChettingBox, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChettingBox::OnBnClickedOk)
END_MESSAGE_MAP()


// CChettingBox ��Ϣ�������


BOOL CChettingBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	this->SetWindowTextW(m_Caption);

	//���������߳�
	CreateThread(NULL,0,ReceiveMsg,this,0,0);



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CChettingBox::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//������Ϣ ������ m_Caption  �� ������ ȡ��Personnalinfo  ���������� :
	 
	UpdateData(true);

	CMsg::SendMsg["ToUser"]= ConvertCStringToString(m_Caption);
	CMsg::SendMsg["FromUser"]=ConvertCStringToString(CQqProjectForClientDlg::PresonalInfo.UserName);
	CMsg::SendMsg["Text"]=ConvertCStringToString(m_SendMsg);
	CMsg::SendMsg["BuisType"]="SendMsg";


	if(CQqProjectForClientDlg::ThClient.SendMap(CMsg::SendMsg)<0){
		MessageBox(_T("������æ!"))
			;}




	//CDialogEx::OnOK();
}


