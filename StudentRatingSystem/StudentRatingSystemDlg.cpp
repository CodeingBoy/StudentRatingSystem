
// StudentRatingSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentRatingSystem.h"
#include "StudentRatingSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CStudentRatingSystemDlg 对话框



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


// CStudentRatingSystemDlg 消息处理程序

BOOL CStudentRatingSystemDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// Tab 初始化
	m_classTab.InsertItem(0, _T("全局"));
	m_classTab.InsertItem(1, _T("2015级软件工程4班"));

	// List 初始化
	m_studentInfList.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 100);
	m_studentInfList.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 60);
	m_studentInfList.InsertColumn(2, _T("班级"), LVCFMT_CENTER, 60);
	m_studentInfList.InsertColumn(3, _T("科目1成绩"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(4, _T("科目2成绩"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(5, _T("科目3成绩"), LVCFMT_CENTER, 80);

	m_studentInfList.InsertItem(0, _T("201510098016"));
	m_studentInfList.SetItemText(0, 1, _T("黄飞豪"));

	LONG lStyle;
	lStyle = GetWindowLong(m_studentInfList.GetSafeHwnd(), GWL_STYLE);//获取当前窗口style  
	lStyle |= LVS_EDITLABELS; //设置style  
	SetWindowLong(m_studentInfList.GetSafeHwnd(), GWL_STYLE, lStyle);//设置style  

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStudentRatingSystemDlg::OnPaint()
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
