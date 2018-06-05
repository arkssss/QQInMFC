// ChettingBox.cpp : 实现文件
//

#include "stdafx.h"
#include "QqProjectForClient.h"
#include "ChettingBox.h"
#include "afxdialogex.h"
#include "QqProjectForClientDlg.h"
#include "Msg.h"
#include "Function.h"
// CChettingBox 对话框

IMPLEMENT_DYNAMIC(CChettingBox, CDialogEx)


//进程的接受函数
DWORD WINAPI ReceiveMsg(LPVOID lpParam){

	CChettingBox *dlg = (CChettingBox *)lpParam;
	
	while(1){
			//接受
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


// CChettingBox 消息处理程序


BOOL CChettingBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	this->SetWindowTextW(m_Caption);

	//创建接受线程
	CreateThread(NULL,0,ReceiveMsg,this,0,0);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CChettingBox::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//发送消息 接收人 m_Caption  ； 发送人 取自Personnalinfo  ；发送内容 :
	 
	UpdateData(true);

	CMsg::SendMsg["ToUser"]= ConvertCStringToString(m_Caption);
	CMsg::SendMsg["FromUser"]=ConvertCStringToString(CQqProjectForClientDlg::PresonalInfo.UserName);
	CMsg::SendMsg["Text"]=ConvertCStringToString(m_SendMsg);
	CMsg::SendMsg["BuisType"]="SendMsg";


	if(CQqProjectForClientDlg::ThClient.SendMap(CMsg::SendMsg)<0){
		MessageBox(_T("服务器忙!"))
			;}




	//CDialogEx::OnOK();
}


