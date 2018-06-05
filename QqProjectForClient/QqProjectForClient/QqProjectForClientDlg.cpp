
// QqProjectForClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QqProjectForClient.h"
#include "QqProjectForClientDlg.h"
#include "afxdialogex.h"
#include "FirendLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//静态成员变量声明
Client CQqProjectForClientDlg::ThClient;
CPresonalInfo CQqProjectForClientDlg::PresonalInfo;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQqProjectForClientDlg 对话框




CQqProjectForClientDlg::CQqProjectForClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQqProjectForClientDlg::IDD, pParent)
	, m_Username(_T(""))
	, m_Password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQqProjectForClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Username);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
}

BEGIN_MESSAGE_MAP(CQqProjectForClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CQqProjectForClientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CQqProjectForClientDlg 消息处理程序

BOOL CQqProjectForClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//此步骤添加初始化链接函数
	//初始化服务器连接
	if(ThClient.Init("127.0.0.1")<0) {MessageBox(_T("服务器连接失败!"));exit(1);}	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQqProjectForClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQqProjectForClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQqProjectForClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQqProjectForClientDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//给服务器发送信息
	UpdateData(true);
	CMsg::SendMsg["UserName"]=ConvertCStringToString(m_Username);
	CMsg::SendMsg["PassWord"]=ConvertCStringToString(m_Password);
	CMsg::SendMsg["BuisType"]="LogIn";
	//封装消息
	if(ThClient.SendMap(CMsg::SendMsg)<0) {MessageBox(_T("服务器忙!发送失败"));};


	//此时接受服务器发送的验证消息
	if(ThClient.RecvForMap(CMsg::ReceMsg) < 0) {MessageBox(_T("接受服务器的消息失败!"));};
	if(CMsg::ReceMsg["BusiStatus"]=="1") {
			//登陆成功
			MessageBox(_T("登陆成功"));

			//保存个人信息
			PresonalInfo.UserName=ConvertStringToCString(CMsg::ReceMsg["UserName"]);
			PresonalInfo.Age=ConvertStringToCString(CMsg::ReceMsg["Age"]);
			PresonalInfo.PassWord=ConvertStringToCString(CMsg::ReceMsg["PassWord"]);
			PresonalInfo.Sex=ConvertStringToCString(CMsg::ReceMsg["Sex"]);
			PresonalInfo.RegTime=ConvertStringToCString(CMsg::ReceMsg["RegTime"]);

			//清空消息
			CMsg::ReceMsg.clear();
			CMsg::SendMsg.clear();

			CFirendLine FirendLine;
			CDialogEx::OnOK();
			FirendLine.DoModal();
		}else{
			//登陆失败
			MessageBox(_T("登陆失败"));
		}
	
}
