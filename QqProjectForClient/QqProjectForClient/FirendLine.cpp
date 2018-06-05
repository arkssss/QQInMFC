// FirendLine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QqProjectForClient.h"
#include "FirendLine.h"
#include "afxdialogex.h"
#include "QqProjectForClientDlg.h"
#include "Msg.h"
#include "Function.h"
#include "ChettingBox.h"
// CFirendLine �Ի���
//ȫ�ֹ�������
//��ʱҪ�������������飬�ж��Ƿ��жԻ����
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


// CFirendLine ��Ϣ�������


BOOL CFirendLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ�������б�
	DWORD dwStyle = m_List.GetExtendedStyle();     
        dwStyle |= LVS_EX_FULLROWSELECT;
        dwStyle |= LVS_EX_GRIDLINES;
    m_List.SetExtendedStyle(dwStyle);
	
	CFont m_font;
	m_font.CreatePointFont(200,_T("Consolas"));
	m_List.SetFont(&m_font);
	m_List.InsertColumn(0,_T("����"),0,150);
	m_List.InsertColumn(1,_T("״̬"),0,150);

	//�˴���ø��û��ĺ�����Ϣ
	CMsg::SendMsg["BuisType"]="GetFriendList";
	CMsg::SendMsg["UserName"]=ConvertCStringToString(CQqProjectForClientDlg::PresonalInfo.UserName);

	if(CQqProjectForClientDlg::ThClient.SendMap(CMsg::SendMsg)<0) {MessageBox(_T("���粻�ȶ�!!!"));};
	if(CQqProjectForClientDlg::ThClient.RecvForMap(CMsg::ReceMsg)<0){MessageBox(_T("���粻�ȶ�!!!"));};

	if(CMsg::ReceMsg["FriendType"]=="1"){
		//�к���
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
		//�޺���
		
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}




void CFirendLine::OnNMDblclkListFriend(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 NMLISTVIEW* pp= (NMLISTVIEW*)pNMHDR;
	 CString UserName=m_List.GetItemText(pp->iItem,0);
	 //��õ�ĳһ�е�username
	 if(UserName!=""){
		//�򿪶Ի���
		//CChettingBox ChettingBox;
	   // ChettingBox.m_Caption=UserName;
		//ChettingBox.DoModal();	
		 if(dict.end()==dict.find(ConvertCStringToString(UserName))){
			 //˵��������
			 CChettingBox * ChettingBox=NULL; 
			 ChettingBox = new CChettingBox();
			 ChettingBox->m_Caption=UserName;
			 ChettingBox->Create(IDD_DIALOG_MsgBox,this);			
			 ChettingBox->ShowWindow(SW_SHOW);
			 dict[ConvertCStringToString(UserName)]=ChettingBox;
		 }else{
			//����
			 dict[ConvertCStringToString(UserName)]->ShowWindow(SW_SHOW);
		 }	
	 }

	 *pResult = 0;
}
