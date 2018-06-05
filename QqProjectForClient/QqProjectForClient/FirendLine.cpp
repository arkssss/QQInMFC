// FirendLine.cpp : 实现文件
//

#include "stdafx.h"
#include "QqProjectForClient.h"
#include "FirendLine.h"
#include "afxdialogex.h"
#include "QqProjectForClientDlg.h"
#include "Msg.h"
#include "Function.h"
#include "ChettingBox.h"
// CFirendLine 对话框
//全局关联数组
//此时要将建立关联数组，判断是否有对话框打开
map <string,CChettingBox*> dict;



IMPLEMENT_DYNAMIC(CFirendLine, CDialogEx)

CFirendLine::CFirendLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFirendLine::IDD, pParent)
{
	
}

CFirendLine::~CFirendLine()
{
	

}

void CFirendLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Friend, m_List);
}


BEGIN_MESSAGE_MAP(CFirendLine, CDialogEx)


	ON_NOTIFY(NM_DBLCLK, IDC_LIST_Friend, &CFirendLine::OnNMDblclkListFriend)
END_MESSAGE_MAP()


// CFirendLine 消息处理程序


BOOL CFirendLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化好友列表
	DWORD dwStyle = m_List.GetExtendedStyle();     
        dwStyle |= LVS_EX_FULLROWSELECT;
        dwStyle |= LVS_EX_GRIDLINES;
    m_List.SetExtendedStyle(dwStyle);
	
	CFont m_font;
	m_font.CreatePointFont(200,_T("Consolas"));
	m_List.SetFont(&m_font);
	m_List.InsertColumn(0,_T("好友"),0,150);
	m_List.InsertColumn(1,_T("状态"),0,150);

	//此处获得该用户的好友信息
	CMsg::SendMsg["BuisType"]="GetFriendList";
	CMsg::SendMsg["UserName"]=ConvertCStringToString(CQqProjectForClientDlg::PresonalInfo.UserName);

	if(CQqProjectForClientDlg::ThClient.SendMap(CMsg::SendMsg)<0) {MessageBox(_T("网络不稳定!!!"));};
	if(CQqProjectForClientDlg::ThClient.RecvForMap(CMsg::ReceMsg)<0){MessageBox(_T("网络不稳定!!!"));};

	if(CMsg::ReceMsg["FriendType"]=="1"){
		//有好友
		int index=0;
		map<string, string>::iterator it=CMsg::ReceMsg.begin();
		while(it!=CMsg::ReceMsg.end()){
			if(it->first!="FriendType"){
				m_List.InsertItem(index,ConvertStringToCString(it->first));
				string status= it->second=="1"? "Online" : "Offline";
				m_List.SetItemText(index,1,ConvertStringToCString(status));
			}
			it++;
		}


	}else{
		//无好友
		
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}




void CFirendLine::OnNMDblclkListFriend(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	 NMLISTVIEW* pp= (NMLISTVIEW*)pNMHDR;
	 CString UserName=m_List.GetItemText(pp->iItem,0);
	 //获得到某一列的username
	 if(UserName!=""){
		//打开对话框
		//CChettingBox ChettingBox;
	   // ChettingBox.m_Caption=UserName;
		//ChettingBox.DoModal();	
		 if(dict.end()==dict.find(ConvertCStringToString(UserName))){
			 //说明不存在
			 CChettingBox * ChettingBox=NULL; 
			 ChettingBox = new CChettingBox();
			 ChettingBox->m_Caption=UserName;
			 ChettingBox->Create(IDD_DIALOG_MsgBox,this);			
			 ChettingBox->ShowWindow(SW_SHOW);
			 dict[ConvertCStringToString(UserName)]=ChettingBox;
		 }else{
			//存在
			 dict[ConvertCStringToString(UserName)]->ShowWindow(SW_SHOW);
		 }	
	 }

	 *pResult = 0;
}
