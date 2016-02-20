
// StudentRatingSystemDlg.cpp : ʵ���ļ�
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
	//  DDX_Control(pDX, IDC_SORT, m_sort);
	DDX_Control(pDX, IDC_SORT, m_sortBox);
}

BEGIN_MESSAGE_MAP(CStudentRatingSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DELETE, &CStudentRatingSystemDlg::OnBnClickedDelete)
	ON_WM_CREATE()
	//	ON_NOTIFY(NM_DBLCLK, IDC_STUINFLIST, &CStudentRatingSystemDlg::OnNMDblclkStuinflist)
	ON_BN_CLICKED(IDC_IMPORT, &CStudentRatingSystemDlg::OnBnClickedImport)
	ON_BN_CLICKED(IDC_EXPORT, &CStudentRatingSystemDlg::OnBnClickedExport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_STUINFLIST, &CStudentRatingSystemDlg::OnLvnItemchangedStuinflist)
	ON_NOTIFY(LVN_DELETEITEM, IDC_STUINFLIST, &CStudentRatingSystemDlg::OnLvnDeleteitemStuinflist)
	ON_NOTIFY(LVN_INSERTITEM, IDC_STUINFLIST, &CStudentRatingSystemDlg::OnLvnInsertitemStuinflist)
	ON_BN_CLICKED(IDC_evaluateAward1, &CStudentRatingSystemDlg::OnBnClickedevaluateaward1)
	ON_BN_CLICKED(IDC_evaluateAward2, &CStudentRatingSystemDlg::OnBnClickedevaluateaward2)
	ON_BN_CLICKED(IDC_DELETEALL, &CStudentRatingSystemDlg::OnBnClickedDeleteall)
	ON_CBN_SELCHANGE(IDC_SORT, &CStudentRatingSystemDlg::OnCbnSelchangeSort)
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

	PrepareList(); // List ��ʼ��

	// ��ʼ������
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
	m_studentInfList.InsertColumn(7, _T("�Ƿ�ѧϰ���"), LVCFMT_CENTER, 90);
	m_studentInfList.InsertColumn(8, _T("�Ƿ�����ѧ��"), LVCFMT_CENTER, 90);

	CRect Rect(CPoint(0, 0), CSize(100, 500));
	m_Edit.Create(WS_CHILD | WS_TABSTOP | WS_BORDER, Rect, this, IDC_EDIT);
	m_studentInfList.SetDefaultEditor(&m_Edit);
	m_Edit.SetFont(m_studentInfList.GetFont());

	InitializeList();
}

void CStudentRatingSystemDlg::InitializeList() { // ��ʼ���б���ִ�ж�Σ�
	m_studentInfList.DeleteAllItems();

	int averageIndex = m_studentInfList.InsertItem(m_studentInfList.GetItemCount(), _T("ƽ��ֵ"));
	for (int i = 0; i < 4; i++)
		m_studentInfList.SetItemText(averageIndex, i + 3, _T("N/A"));

	m_studentInfList.InsertItem(m_studentInfList.GetItemCount() - 1, _T("          +"));
}

void CStudentRatingSystemDlg::AddNewLine(StudentInf &inf) {
	int newline_index = m_studentInfList.GetItemCount() - 2; // ���һ����ʾƽ��ֵ�������ڶ���ΪԤ��

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
	m_studentInfList.SetItemText(newline_index, 7, _T("N/A"));
	m_studentInfList.SetItemText(newline_index, 8, _T("N/A"));

	RefreshAverage();
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
	std::list<StudentInf>::iterator StudentsListIterator;

	for (StudentsListIterator = StudentInf_list.begin();
	StudentsListIterator != StudentInf_list.end();
		++StudentsListIterator)
	{
		// �ۼ�����
		average[0] += StudentsListIterator->mark_subject1;
		average[1] += StudentsListIterator->mark_subject2;
		average[2] += StudentsListIterator->mark_subject3;
	}
	//average[3] = average[0] + average[1] + average[2];

	int studentNumber = m_studentInfList.GetItemCount() - 2;
	for (int i = 0; i < 3; i++)
		average[i] /= studentNumber; // ����ѧ����
	average[3] = average[0] + average[1] + average[2]; // ͵����

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
		_T("���ŷָ����ļ�(*.csv)|*.csv|�ı��ļ�(*.txt)|*.txt||"), NULL, 0, TRUE);
	if (filedlg.DoModal() != IDOK) // ȡ����
		return;
	int reply = MessageBox(_T("��������ļ��Ƿ���ڱ��⣿\n\n������ָ�������ļ���һ�в��Ǿ������Ϣ���������������ݵ����֡�"),
		_T("�Ƿ���ڱ���"), MB_ICONQUESTION | MB_YESNOCANCEL);

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
	if (handler.err != 0) { // ������
		CString errmsg;
		errmsg.Format(_T("���ļ�ʧ�ܣ�\n���صĴ�����룺%d��������\"errno %d\"�Ի�ȡ����ϸ����Ϣ��"),
			handler.err, handler.err);
		MessageBox(errmsg, _T("���ִ���"), MB_ICONERROR);
		return; // ����������
	}
	if (handler.parseFile(haveHeader, &StudentInf_list))
	{
		std::list<StudentInf>::iterator StudentsListIterator;

		for (StudentsListIterator = StudentInf_list.begin();
		StudentsListIterator != StudentInf_list.end();
			++StudentsListIterator)
		{
			AddNewLine(*StudentsListIterator);
		}

		MessageBox(_T("����ɹ���"), _T("�ɹ���"), MB_ICONINFORMATION);
	}
}


void CStudentRatingSystemDlg::OnBnClickedExport()
{
	CFileDialog filedlg(FALSE, NULL, NULL, OFN_CREATEPROMPT | OFN_PATHMUSTEXIST,
		_T("���ŷָ����ļ�(*.csv)|*.csv|�ı��ļ�(*.txt)|*.txt||"), NULL, 0, TRUE);
	if (filedlg.DoModal() != IDOK) // ȡ����
		return;
	int reply = MessageBox(_T("��ϣ�����������\n\n������ָ�������ļ���һ�в��Ǿ������Ϣ���������������ݵ����֡�"),
		_T("�Ƿ񱣴����"), MB_ICONQUESTION | MB_YESNOCANCEL);

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
	if (handler.err != 0) { // ������
		CString errmsg;
		errmsg.Format(_T("���ļ�ʧ�ܣ�\n���صĴ�����룺%d��������\"errno %d\"�Ի�ȡ����ϸ����Ϣ��"),
			handler.err, handler.err);
		MessageBox(errmsg, _T("���ִ���"), MB_ICONERROR);
		return; // ����������
	}
	if (handler.saveFile(haveHeader, &StudentInf_list))
	{
		MessageBox(_T("����ɹ���"), _T("�ɹ���"), MB_ICONINFORMATION);
	}
}


void CStudentRatingSystemDlg::OnLvnItemchangedStuinflist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView)
	{
		int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

		if (m_studentInfList.GetItemCount() > 2 && nItem == m_studentInfList.GetItemCount() - 1)
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
				if (StudentsListIterator->studentID == _wtof(deletingItem_ID)) { // ѧ��һ��
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

	if (m_studentInfList.GetItemCount() > 2)
		RefreshAverage();

	*pResult = 0;
}


void CStudentRatingSystemDlg::OnBnClickedevaluateaward1()
{
	evaluateAward1(&StudentInf_list);
}

void CStudentRatingSystemDlg::evaluateAward1(std::list<StudentInf> *plist) {
	StudentInf_list.sort(cmp_total); // �ȴӴ�С����

	for (std::list<StudentInf>::iterator StudentsListIterator = StudentInf_list.begin();
	StudentsListIterator != StudentInf_list.end();
		++StudentsListIterator)
	{
		if (StudentsListIterator->mark_subject1 >= 75 &&
			StudentsListIterator->mark_subject2 >= 75 &&
			StudentsListIterator->mark_subject3 >= 75)
		{
			for (int i = 0; i < m_studentInfList.GetItemCount() - 2; i++)
			{
				if (_wtof(m_studentInfList.GetItemText(i, 0)) == StudentsListIterator->studentID)
				{
					m_studentInfList.SetItemText(i, 7, _T("��"));
					m_studentInfList.SetCellColors(i, 7, RGB(134, 71, 63), -1);
					StudentsListIterator->haveAward = 1;
				}
				else {
					m_studentInfList.SetItemText(i, 7, _T("��"));
					m_studentInfList.SetCellColors(i, 7, RGB(100, 106, 88), -1);
				}
			}
			return; // ������ֻ��һ�ˣ���������
		}

	}
}

void CStudentRatingSystemDlg::evaluateAward2(std::list<StudentInf> *plist) {
	StudentInf_list.sort(cmp_total); // �ȴӴ�С����

	int num = 1;
	const int totalNum = m_studentInfList.GetItemCount() - 2;

	for (std::list<StudentInf>::iterator StudentsListIterator = StudentInf_list.begin();
	StudentsListIterator != StudentInf_list.end();
		++StudentsListIterator)
	{
		if (num <= (int)(totalNum * 0.05 + 0.5) && StudentsListIterator->haveAward != 1) // �����ϲ�����
		{

			if (StudentsListIterator->mark_subject1 >= 75 &&
				StudentsListIterator->mark_subject2 >= 75 &&
				StudentsListIterator->mark_subject3 >= 75)
			{
				// ���Ҳ���д
				for (int i = 0; i < m_studentInfList.GetItemCount() - 2; i++)
				{
					if (_wtof(m_studentInfList.GetItemText(i, 0)) == StudentsListIterator->studentID)
					{
						m_studentInfList.SetItemText(i, 8, _T("��"));
						m_studentInfList.SetCellColors(i, 8, RGB(134, 71, 63), -1);
						StudentsListIterator->haveAward = 2;
						break; // �Ѳ��ҵ�������ѭ��
					}
				}
			}
			num++;
		}

	}

	// û�񽱵���д��
	for (int i = 0; i < m_studentInfList.GetItemCount() - 2; i++)
	{
		if (m_studentInfList.GetItemText(i, 8) != _T("��"))
		{
			m_studentInfList.SetItemText(i, 8, _T("��"));
			m_studentInfList.SetCellColors(i, 8, RGB(100, 106, 88), -1);
		}
		// ��п����ᣬ������ο����û�� :(
		// ��ӵ���֧������û��ҵ����û�н��� :(
	}


}

void CStudentRatingSystemDlg::OnBnClickedevaluateaward2()
{
	evaluateAward2(&StudentInf_list);
}


void CStudentRatingSystemDlg::OnBnClickedDeleteall()
{
	if (MessageBox(_T("��ȷ��Ҫ����б���"), _T("ȷ����"), MB_ICONQUESTION | MB_YESNO)
		== IDYES) {
		InitializeList();
		StudentInf_list.clear();
	}

}

bool cmp_total(StudentInf first, StudentInf second) {
	if (first.mark_total <= second.mark_total)
		return false;
	else
		return true;
}

void CStudentRatingSystemDlg::OnCbnSelchangeSort()
{
	switch (m_sortBox.GetCurSel())
	{

		break;
	}

}
