
// QqProjectForClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QqProjectForClient.h"
#include "QqProjectForClientDlg.h"
#include "afxdialogex.h"
#include "FirendLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��̬��Ա��������
Client CQqProjectForClientDlg::ThClient;
CPresonalInfo CQqProjectForClientDlg::PresonalInfo;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CQqProjectForClientDlg �Ի���




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


// CQqProjectForClientDlg ��Ϣ�������

BOOL CQqProjectForClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//�˲�����ӳ�ʼ�����Ӻ���
	//��ʼ������������
	if(ThClient.Init("127.0.0.1")<0) {MessageBox(_T("����������ʧ��!"));exit(1);}	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQqProjectForClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQqProjectForClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQqProjectForClientDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��������������Ϣ
	UpdateData(true);
	CMsg::SendMsg["UserName"]=ConvertCStringToString(m_Username);
	CMsg::SendMsg["PassWord"]=ConvertCStringToString(m_Password);
	CMsg::SendMsg["BuisType"]="LogIn";
	//��װ��Ϣ
	if(ThClient.SendMap(CMsg::SendMsg)<0) {MessageBox(_T("������æ!����ʧ��"));};


	//��ʱ���ܷ��������͵���֤��Ϣ
	if(ThClient.RecvForMap(CMsg::ReceMsg) < 0) {MessageBox(_T("���ܷ���������Ϣʧ��!"));};
	if(CMsg::ReceMsg["BusiStatus"]=="1") {
			//��½�ɹ�
			MessageBox(_T("��½�ɹ�"));

			//���������Ϣ
			PresonalInfo.UserName=ConvertStringToCString(CMsg::ReceMsg["UserName"]);
			PresonalInfo.Age=ConvertStringToCString(CMsg::ReceMsg["Age"]);
			PresonalInfo.PassWord=ConvertStringToCString(CMsg::ReceMsg["PassWord"]);
			PresonalInfo.Sex=ConvertStringToCString(CMsg::ReceMsg["Sex"]);
			PresonalInfo.RegTime=ConvertStringToCString(CMsg::ReceMsg["RegTime"]);

			//�����Ϣ
			CMsg::ReceMsg.clear();
			CMsg::SendMsg.clear();

			CFirendLine FirendLine;
			CDialogEx::OnOK();
			FirendLine.DoModal();
		}else{
			//��½ʧ��
			MessageBox(_T("��½ʧ��"));
		}
	
}
