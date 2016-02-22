
// StudentRatingSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentRatingSystem.h"
#include "StudentRatingSystemDlg.h"
#include "afxdialogex.h"
#include "StuFileHandler.h"

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
public:
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_LBUTTONDBLCLK()
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
	ON_BN_CLICKED(IDC_DELETE, &CStudentRatingSystemDlg::OnBnClickedDelete)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_IMPORT, &CStudentRatingSystemDlg::OnBnClickedImport)
	ON_BN_CLICKED(IDC_EXPORT, &CStudentRatingSystemDlg::OnBnClickedExport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_STUINFLIST, &CStudentRatingSystemDlg::OnLvnItemchangedStuinflist)
	ON_NOTIFY(LVN_DELETEITEM, IDC_STUINFLIST, &CStudentRatingSystemDlg::OnLvnDeleteitemStuinflist)
	ON_NOTIFY(LVN_INSERTITEM, IDC_STUINFLIST, &CStudentRatingSystemDlg::OnLvnInsertitemStuinflist)
	ON_BN_CLICKED(IDC_evaluateAward1, &CStudentRatingSystemDlg::OnBnClickedevaluateaward1)
	ON_BN_CLICKED(IDC_evaluateAward2, &CStudentRatingSystemDlg::OnBnClickedevaluateaward2)
	ON_BN_CLICKED(IDC_DELETEALL, &CStudentRatingSystemDlg::OnBnClickedDeleteall)
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

	PrepareList(); // List 初始化

	// 初始化排序
	m_studentInfList.SetColumnSorting(0, CListCtrlExt::Auto, CListCtrlExt::StringNumberNoCase);
	m_studentInfList.SetColumnSorting(1, CListCtrlExt::Auto, CListCtrlExt::StringNoCase);
	m_studentInfList.SetColumnSorting(2, CListCtrlExt::Auto, CListCtrlExt::StringNoCase);
	m_studentInfList.SetColumnSorting(3, CListCtrlExt::Auto, CListCtrlExt::Int);
	m_studentInfList.SetColumnSorting(4, CListCtrlExt::Auto, CListCtrlExt::Int);
	m_studentInfList.SetColumnSorting(5, CListCtrlExt::Auto, CListCtrlExt::Int);
	m_studentInfList.SetColumnSorting(6, CListCtrlExt::Auto, CListCtrlExt::Int);
	m_studentInfList.SetColumnSorting(7, CListCtrlExt::Auto, CListCtrlExt::StringNoCase);
	m_studentInfList.SetColumnSorting(8, CListCtrlExt::Auto, CListCtrlExt::StringNoCase);

	m_studentInfList.GetHeaderCtrl()->SetRemovable(0, FALSE);

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
	m_studentInfList.InsertColumn(7, _T("是否学习标兵"), LVCFMT_CENTER, 90);
	m_studentInfList.InsertColumn(8, _T("是否三好学生"), LVCFMT_CENTER, 90);

	CRect Rect(CPoint(0, 0), CSize(100, 500));
	m_Edit.Create(WS_CHILD | WS_TABSTOP | WS_BORDER, Rect, this, IDC_EDIT);
	m_studentInfList.SetDefaultEditor(&m_Edit);
	m_Edit.SetFont(m_studentInfList.GetFont());

	InitializeList();
}

void CStudentRatingSystemDlg::InitializeList() { // 初始化列表（可执行多次）
	m_studentInfList.DeleteAllItems();

	int averageIndex = m_studentInfList.InsertItem(m_studentInfList.GetItemCount(), _T("平均值"));
	for (int i = 0; i < 4; i++)
		m_studentInfList.SetItemText(averageIndex, i + 3, _T("N/A"));
	m_studentInfList.SetRowColors(averageIndex, RGB(28, 28, 28), -1);
	m_studentInfList.SetRowReadOnly(averageIndex);

	m_studentInfList.InsertItem(m_studentInfList.GetItemCount() - 1, _T("          +"));
	m_studentInfList.SetRowReadOnly(m_studentInfList.GetItemCount() - 1);

}

void CStudentRatingSystemDlg::AddNewLine(StudentInf &inf, bool hasAwardInf) {
	int newline_index = m_studentInfList.GetItemCount() - 2; // 最后一行显示平均值，倒数第二行为预留

	CString ID, mark[4];
	ID.Format(_T("%.0f"), inf.studentID);
	mark[0].Format(_T("%.1f"), inf.mark_subject1);
	mark[1].Format(_T("%.1f"), inf.mark_subject2);
	mark[2].Format(_T("%.1f"), inf.mark_subject3);
	mark[3].Format(_T("%.1f"), inf.mark_total);

	m_studentInfList.InsertItem(newline_index, ID);
	m_studentInfList.SetItemText(newline_index, 1, inf.name);
	m_studentInfList.SetItemText(newline_index, 2, inf.studentClass);
	m_studentInfList.SetItemText(newline_index, 3, mark[0]);
	m_studentInfList.SetItemText(newline_index, 4, mark[1]);
	m_studentInfList.SetItemText(newline_index, 5, mark[2]);
	m_studentInfList.SetItemText(newline_index, 6, mark[3]);

	if (hasAwardInf){
		m_studentInfList.SetItemText(newline_index, 7, _T("否"));
		m_studentInfList.SetItemText(newline_index, 8, _T("否"));
		m_studentInfList.SetCellColors(newline_index, 7, RGB(100, 106, 88), -1);
		m_studentInfList.SetCellColors(newline_index, 8, RGB(100, 106, 88), -1);
		switch (inf.haveAward)
		{
		case 1:
			m_studentInfList.SetItemText(newline_index, 7, _T("是"));
			m_studentInfList.SetCellColors(newline_index, 7, RGB(134, 71, 63), -1);
			break;
		case 2:
			m_studentInfList.SetItemText(newline_index, 8, _T("是"));
			m_studentInfList.SetCellColors(newline_index, 8, RGB(134, 71, 63), -1);
			break;
		}
	}else {
		m_studentInfList.SetItemText(newline_index, 7, _T("N/A"));
		m_studentInfList.SetItemText(newline_index, 8, _T("N/A"));
	}

}

void CStudentRatingSystemDlg::RefreshAverage() {

	float average[4] = { 0,0,0,0 };
	CalculateAverage(average);

	int lastLineIndex = m_studentInfList.GetItemCount() - 1;
	CString average_str[4];
	for (int i = 0; i < 4; i++)
	{
		average_str[i].Format(_T("%.1f"), average[i]);
		m_studentInfList.SetItemText(lastLineIndex, i + 3, average_str[i]);
	}

}

void CStudentRatingSystemDlg::CalculateAverage(float average[]) {

	for (int i = 0; i < m_studentInfList.GetItemCount() - 2; i++)
	{
		// 累加起来
		average[0] += _wtof(m_studentInfList.GetItemText(i, 3));
		average[1] += _wtof(m_studentInfList.GetItemText(i, 4));
		average[2] += _wtof(m_studentInfList.GetItemText(i, 5));
	}

	int studentNumber = m_studentInfList.GetItemCount() - 2;
	for (int i = 0; i < 3; i++)
		average[i] /= studentNumber; // 除以学生数
	average[3] = average[0] + average[1] + average[2]; // 偷个懒

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

void CStudentRatingSystemDlg::OnBnClickedDelete()
{
	int deletingIndex = m_studentInfList.GetSelectionMark();
	if (deletingIndex <= m_studentInfList.GetItemCount() - 3)
	{

		m_studentInfList.DeleteSelectedItems();
	}

}


int CStudentRatingSystemDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}



void CStudentRatingSystemDlg::OnBnClickedImport()
{
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT,
		_T("逗号分隔符文件(*.csv)|*.csv|文本文件(*.txt)|*.txt||"), NULL, 0, TRUE);
	if (filedlg.DoModal() != IDOK) // 取消了
		return;
	int reply = MessageBox(_T("您导入的文件是否存在标题？\n\n标题是指：您的文件第一行不是具体的信息，而是描述列内容的文字。"),
		_T("是否存在标题"), MB_ICONQUESTION | MB_YESNOCANCEL);

	bool haveHeader;
	switch (reply)
	{
	case IDYES:
		haveHeader = true;
		break;
	case IDNO:
		haveHeader = false;
		break;
	default:
		return;
	}

	CStuFileHandler handler(filedlg.GetPathName());
	if (handler.err != 0) { // 出错处理
		CString errmsg;
		errmsg.Format(_T("打开文件失败！\n返回的错误代码：%d，请搜索\"errno %d\"以获取更详细的信息。"),
			handler.err, handler.err);
		MessageBox(errmsg, _T("出现错误"), MB_ICONERROR);
		return; // 立刻析构掉
	}

	calcAverage = false; // 即将大批量导入 取消每次修改都计算平均

	void (CStudentRatingSystemDlg::* pFunc)(StudentInf&, bool) = &CStudentRatingSystemDlg::AddNewLine;
	if (handler.parseFile(haveHeader, this, pFunc))
	{
		if (handler.hasExtraInf){
			MessageBox(_T("程序发现您的文件中含有额外的信息，这些信息可能已过期，因此已作丢弃处理。\n"
				 "建议您审阅数据以保证数据的正确性。"), _T("文件含有额外的信息"), MB_ICONINFORMATION);
		}

		RefreshAverage();

		MessageBox(_T("导入成功！"), _T("成功！"), MB_ICONINFORMATION);
	}

	calcAverage = true;
}


void CStudentRatingSystemDlg::OnBnClickedExport()
{
	CFileDialog filedlg(FALSE, NULL, NULL, OFN_CREATEPROMPT | OFN_PATHMUSTEXIST,
		_T("逗号分隔符文件(*.csv)|*.csv|文本文件(*.txt)|*.txt||"), NULL, 0, TRUE);
	if (filedlg.DoModal() != IDOK) // 取消了
		return;
	int reply = MessageBox(_T("您希望保存标题吗？\n\n标题是指：您的文件第一行不是具体的信息，而是描述列内容的文字。"),
		_T("是否保存标题"), MB_ICONQUESTION | MB_YESNOCANCEL);

	bool haveHeader;
	switch (reply)
	{
	case IDYES:
		haveHeader = true;
		break;
	case IDNO:
		haveHeader = false;
		break;
	default:
		return;
	}

	CStuFileHandler handler(filedlg.GetPathName(), false);
	if (handler.err != 0) { // 出错处理
		CString errmsg;
		errmsg.Format(_T("打开文件失败！\n返回的错误代码：%d，请搜索\"errno %d\"以获取更详细的信息。"),
			handler.err, handler.err);
		MessageBox(errmsg, _T("出现错误"), MB_ICONERROR);
		return; // 立刻析构掉
	}
	if (handler.saveFile(haveHeader, &StudentInf_list))
	{
		MessageBox(_T("保存成功！"), _T("成功！"), MB_ICONINFORMATION);
	}
}


void CStudentRatingSystemDlg::OnLvnItemchangedStuinflist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView)
	{
		int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

		if (m_studentInfList.GetItemCount() > 2 && nItem != m_studentInfList.GetItemCount() - 1 &&
			calcAverage )
			RefreshAverage();
	}


	*pResult = 0;
}


void CStudentRatingSystemDlg::OnLvnDeleteitemStuinflist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView)
	{
		int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

		int deletingIndex = m_studentInfList.GetSelectionMark();
		if (m_studentInfList.GetItemCount() > 2 && nItem <= m_studentInfList.GetItemCount() - 3) {
			CString deletingItem_ID = m_studentInfList.GetItemText(deletingIndex, 0);
			for (std::list<StudentInf>::iterator StudentsListIterator = StudentInf_list.begin();
			StudentsListIterator != StudentInf_list.end();
				++StudentsListIterator)
			{
				if (StudentsListIterator->studentID == _wtof(deletingItem_ID)) { // 学号一致
					StudentInf_list.erase(StudentsListIterator);
					break;
				}
			}
			RefreshAverage();
		}

	}

	*pResult = 0;
}


void CStudentRatingSystemDlg::OnLvnInsertitemStuinflist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (m_studentInfList.GetItemCount() > 2 && calcAverage)
		RefreshAverage();

	*pResult = 0;
}


void CStudentRatingSystemDlg::OnBnClickedevaluateaward1()
{
	syncToLinkList();
	evaluateAward1(&StudentInf_list);
	syncToList();
}

void CStudentRatingSystemDlg::evaluateAward1(std::list<StudentInf> *plist) {
	StudentInf_list.sort(cmp_total); // 先从大到小排序

	for (std::list<StudentInf>::iterator StudentsListIterator = StudentInf_list.begin();
	StudentsListIterator != StudentInf_list.end();
		++StudentsListIterator)
	{
		if (StudentsListIterator->mark_subject1 >= 75 &&
			StudentsListIterator->mark_subject2 >= 75 &&
			StudentsListIterator->mark_subject3 >= 75)
		{
			StudentsListIterator->haveAward = 1;
			return; // 获奖名额只有一人，评定结束
		}

	}
}

void CStudentRatingSystemDlg::evaluateAward2(std::list<StudentInf> *plist) {
	StudentInf_list.sort(cmp_total); // 先从大到小排序

	int num = 1;
	const int totalNum = m_studentInfList.GetItemCount() - 2;

	for (std::list<StudentInf>::iterator StudentsListIterator = StudentInf_list.begin();
	StudentsListIterator != StudentInf_list.end();
		++StudentsListIterator)
	{
		if (num <= (int)(totalNum * 0.05 + 0.5) && StudentsListIterator->haveAward != 1) // 不符合不评比
		{

			if (StudentsListIterator->mark_subject1 >= 75 &&
				StudentsListIterator->mark_subject2 >= 75 &&
				StudentsListIterator->mark_subject3 >= 75)
					StudentsListIterator->haveAward = 2;
			num++;
		}

	}
}

void CStudentRatingSystemDlg::OnBnClickedevaluateaward2()
{
	syncToLinkList();
	evaluateAward2(&StudentInf_list);
	syncToList();
}


void CStudentRatingSystemDlg::OnBnClickedDeleteall()
{
	if (MessageBox(_T("您确定要清空列表吗？"), _T("确定？"), MB_ICONQUESTION | MB_YESNO)
		== IDYES) {
		InitializeList();
		StudentInf_list.clear();
	}

}

void CStudentRatingSystemDlg::syncToLinkList() {
		StudentInf_list.clear();
		for (int i = 0; i < m_studentInfList.GetItemCount() - 2; i++)
		{
			StudentInf inf;

			inf.studentID = _wtof(m_studentInfList.GetItemText(i,0));
			wcscpy_s(inf.name, m_studentInfList.GetItemText(i, 1));
			wcscpy_s(inf.studentClass, m_studentInfList.GetItemText(i, 2));
			inf.mark_subject1 = _wtof(m_studentInfList.GetItemText(i, 3));
			inf.mark_subject2 = _wtof(m_studentInfList.GetItemText(i, 4));
			inf.mark_subject3 = _wtof(m_studentInfList.GetItemText(i, 5));
			inf.mark_total = _wtof(m_studentInfList.GetItemText(i, 6));
			inf.haveAward = 0;
			if (m_studentInfList.GetItemText(i, 7) == _T("是"))
				inf.haveAward = 1;
			else if (m_studentInfList.GetItemText(i, 8) == _T("是"))
				inf.haveAward = 2;

			StudentInf_list.push_back(inf);
		}
}

void CStudentRatingSystemDlg::syncToList() {
	InitializeList();

	calcAverage = false;

	for (std::list<StudentInf>::iterator StudentsListIterator = StudentInf_list.begin();
	StudentsListIterator != StudentInf_list.end();
		++StudentsListIterator)
	{
		AddNewLine(*StudentsListIterator, true);
	}

	calcAverage = true;
}

bool cmp_total(StudentInf first, StudentInf second) {
	if (first.mark_total <= second.mark_total)
		return false;
	else
		return true;
}

