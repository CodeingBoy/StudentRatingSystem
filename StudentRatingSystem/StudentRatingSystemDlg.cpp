
// StudentRatingSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentRatingSystem.h"
#include "StudentRatingSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentRatingSystemDlg �Ի���



CStudentRatingSystemDlg::CStudentRatingSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDENTRATINGSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentRatingSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STUINFLIST, m_studentInfList);
	DDX_Control(pDX, IDC_TAB_CLASS, m_classTab);
}

BEGIN_MESSAGE_MAP(CStudentRatingSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CStudentRatingSystemDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CStudentRatingSystemDlg::OnBnClickedDelete)
END_MESSAGE_MAP()


// CStudentRatingSystemDlg ��Ϣ�������

BOOL CStudentRatingSystemDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// Tab ��ʼ��
	m_classTab.InsertItem(0, _T("ȫ��"));
	m_classTab.InsertItem(1, _T("2015���������4��"));

	// List ��ʼ��
	m_studentInfList.InsertColumn(0, _T("ѧ��"), LVCFMT_CENTER, 100);
	m_studentInfList.InsertColumn(1, _T("����"), LVCFMT_CENTER, 60);
	m_studentInfList.InsertColumn(2, _T("�༶"), LVCFMT_CENTER, 60);
	m_studentInfList.InsertColumn(3, _T("��Ŀ1�ɼ�"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(4, _T("��Ŀ2�ɼ�"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(5, _T("��Ŀ3�ɼ�"), LVCFMT_CENTER, 80);

	m_studentInfList.InsertItem(0, _T("201510098016"));
	m_studentInfList.SetItemText(0, 1, _T("�Ʒɺ�"));

	LONG lStyle;
	lStyle = GetWindowLong(m_studentInfList.GetSafeHwnd(), GWL_STYLE);//��ȡ��ǰ����style  
	lStyle |= LVS_EDITLABELS; //����style  
	SetWindowLong(m_studentInfList.GetSafeHwnd(), GWL_STYLE, lStyle);//����style  

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CStudentRatingSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStudentRatingSystemDlg::OnPaint()
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
HCURSOR CStudentRatingSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//void CStudentRatingSystemDlg::showEditInList(int Row,int Column, CString &str){
//}

void CStudentRatingSystemDlg::OnBnClickedAdd()
{
	m_studentInfList.InsertItem(m_studentInfList.GetItemCount(), _T("Hi~"));
}


void CStudentRatingSystemDlg::OnBnClickedDelete()
{
	m_studentInfList.SetFocus();
	m_studentInfList.EditLabel(TRUE);
}
