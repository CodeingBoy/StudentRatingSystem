
// StudentRatingSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentRatingSystem.h"
#include "StudentRatingSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_EDIT 1007

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
}

BEGIN_MESSAGE_MAP(CStudentRatingSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CStudentRatingSystemDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CStudentRatingSystemDlg::OnBnClickedDelete)
	ON_WM_CREATE()
//	ON_NOTIFY(NM_DBLCLK, IDC_STUINFLIST, &CStudentRatingSystemDlg::OnNMDblclkStuinflist)
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

	// List 初始化
	PrepareList();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStudentRatingSystemDlg::PrepareList() // 初始化列表（仅执行一次）
{
	m_studentInfList.SetGridBehaviour();
	m_studentInfList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_INFOTIP);

	m_studentInfList.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 100);
	m_studentInfList.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 60);
	m_studentInfList.InsertColumn(2, _T("班级"), LVCFMT_CENTER, 150);
	m_studentInfList.InsertColumn(3, _T("英语成绩"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(4, _T("数学成绩"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(5, _T("C++成绩"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(6, _T("总成绩"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(7, _T("是否学习标兵"), LVCFMT_CENTER, 100);
	m_studentInfList.InsertColumn(8, _T("是否三好学生"), LVCFMT_CENTER, 100);

	CRect Rect(CPoint(0, 0), CSize(100, 500));
	m_Edit.Create(WS_CHILD | WS_TABSTOP | WS_BORDER, Rect, this, IDC_EDIT);
	m_studentInfList.SetDefaultEditor(&m_Edit);
	m_Edit.SetFont(m_studentInfList.GetFont());

	InitializeList();
}

void CStudentRatingSystemDlg::InitializeList() { // 初始化列表（可执行多次）
	m_studentInfList.DeleteAllItems();

	m_studentInfList.InsertItem(m_studentInfList.GetItemCount(), _T("平均值"));

	m_studentInfList.InsertItem(m_studentInfList.GetItemCount()-1, _T("          +"));
}

void CStudentRatingSystemDlg::AddNewLine(StudentInf &inf) {
	int newline_index = m_studentInfList.GetItemCount() - 2; // 最后一行显示平均值，倒数第二行为预留

	CString ID, mark[3];
	ID.Format(_T("%f"), inf.studentID);
	mark[0].Format(_T("%.2f"), inf.mark_subject1);
	mark[1].Format(_T("%.2f"), inf.mark_subject2);
	mark[2].Format(_T("%.2f"), inf.mark_subject3);

	m_studentInfList.InsertItem(newline_index, ID);
	m_studentInfList.SetItemText(newline_index, 1, inf.name);
	m_studentInfList.SetItemText(newline_index, 2, inf.studentClass);
	m_studentInfList.SetItemText(newline_index, 3, mark[0]);
	m_studentInfList.SetItemText(newline_index, 4, mark[1]);
	m_studentInfList.SetItemText(newline_index, 5, mark[2]);
	m_studentInfList.SetItemText(newline_index, 6, _T("N/A"));
	m_studentInfList.SetItemText(newline_index, 7, _T("N/A"));
}

void CStudentRatingSystemDlg::RefreshAverage() {
	CalculateAverage();
}

void CStudentRatingSystemDlg::CalculateAverage() {

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


int CStudentRatingSystemDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | CS_DBLCLKS | LVS_REPORT;

	//BOOL bResult = m_List.Create(dwStyle, CRect(0, 0, 0, 0), this, IDC_LIST);
	
	return 0;
}

