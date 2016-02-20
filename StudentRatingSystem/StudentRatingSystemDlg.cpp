
// StudentRatingSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentRatingSystem.h"
#include "StudentRatingSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_EDIT 1007

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

	// List ��ʼ��
	PrepareList();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CStudentRatingSystemDlg::PrepareList() // ��ʼ���б���ִ��һ�Σ�
{
	m_studentInfList.SetGridBehaviour();
	m_studentInfList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_INFOTIP);

	m_studentInfList.InsertColumn(0, _T("ѧ��"), LVCFMT_CENTER, 100);
	m_studentInfList.InsertColumn(1, _T("����"), LVCFMT_CENTER, 60);
	m_studentInfList.InsertColumn(2, _T("�༶"), LVCFMT_CENTER, 150);
	m_studentInfList.InsertColumn(3, _T("Ӣ��ɼ�"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(4, _T("��ѧ�ɼ�"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(5, _T("C++�ɼ�"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(6, _T("�ܳɼ�"), LVCFMT_CENTER, 80);
	m_studentInfList.InsertColumn(7, _T("�Ƿ�ѧϰ���"), LVCFMT_CENTER, 100);
	m_studentInfList.InsertColumn(8, _T("�Ƿ�����ѧ��"), LVCFMT_CENTER, 100);

	CRect Rect(CPoint(0, 0), CSize(100, 500));
	m_Edit.Create(WS_CHILD | WS_TABSTOP | WS_BORDER, Rect, this, IDC_EDIT);
	m_studentInfList.SetDefaultEditor(&m_Edit);
	m_Edit.SetFont(m_studentInfList.GetFont());

	InitializeList();
}

void CStudentRatingSystemDlg::InitializeList() { // ��ʼ���б���ִ�ж�Σ�
	m_studentInfList.DeleteAllItems();

	m_studentInfList.InsertItem(m_studentInfList.GetItemCount(), _T("ƽ��ֵ"));

	m_studentInfList.InsertItem(m_studentInfList.GetItemCount()-1, _T("          +"));
}

void CStudentRatingSystemDlg::AddNewLine(StudentInf &inf) {
	int newline_index = m_studentInfList.GetItemCount() - 2; // ���һ����ʾƽ��ֵ�������ڶ���ΪԤ��

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


int CStudentRatingSystemDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | CS_DBLCLKS | LVS_REPORT;

	//BOOL bResult = m_List.Create(dwStyle, CRect(0, 0, 0, 0), this, IDC_LIST);
	
	return 0;
}

