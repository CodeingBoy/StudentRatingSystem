#include "stdafx.h"
#include "MyListCtrlExt.h"

bool cmp_total(StudentInf first, StudentInf second) {
	if (first.mark_total <= second.mark_total)
		return false;
	else
		return true;
}

CMyListCtrlExt::CMyListCtrlExt()
{
}


CMyListCtrlExt::~CMyListCtrlExt()
{
	
}

BOOL CMyListCtrlExt::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView)
	{
		int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

		if (nItem == GetItemCount() - 2) {
			// ˫������ӵ�һ��
			InsertItem(GetItemCount() - 2, _T("")); // ��+��֮���½�����

		}
	}

	return CListCtrlExt::OnNMDblclk(pNMHDR, pResult);
}

BEGIN_MESSAGE_MAP(CMyListCtrlExt, CListCtrlExt)
ON_WM_LBUTTONDOWN()
ON_NOTIFY_REFLECT(LVN_INSERTITEM, &CMyListCtrlExt::OnLvnInsertitem)
ON_NOTIFY_REFLECT(LVN_DELETEITEM, &CMyListCtrlExt::OnLvnDeleteitem)
ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CMyListCtrlExt::OnLvnItemchanged)
END_MESSAGE_MAP()


void CMyListCtrlExt::OnLButtonDown(UINT nFlags, CPoint point)
{
	HideEditor(); // ���ر༭��

	CListCtrlExt::OnLButtonDown(nFlags, point);
}

void CMyListCtrlExt::AddNewLine(StudentInf &inf, bool hasAwardInf) {
	int newline_index = GetItemCount() - 2; // ���һ����ʾƽ��ֵ�������ڶ���ΪԤ��

	CString ID, mark[4];
	ID.Format(_T("%.0f"), inf.studentID);
	mark[0].Format(_T("%.1f"), inf.mark_subject1);
	mark[1].Format(_T("%.1f"), inf.mark_subject2);
	mark[2].Format(_T("%.1f"), inf.mark_subject3);
	mark[3].Format(_T("%.1f"), inf.mark_total);

	InsertItem(newline_index, ID);
	SetItemText(newline_index, 1, inf.name);
	SetItemText(newline_index, 2, inf.studentClass);
	for (int i = 0; i < 4; i++)
	{
		if (mark[i] == _T("-1.0"))
		{
			SetItemText(newline_index, i + 3, _T("����"));
			SetCellColors(newline_index, i + 3, COLOR_ERR, -1);
		}
		else {
			SetItemText(newline_index, i + 3, mark[i]);
		}
	}

	if (hasAwardInf) {

		if (inf.hasAward == 1){
			SetItemText(newline_index, 7, _T("��"));
			SetCellColors(newline_index, 7, COLOR_YES, -1);
		}else {
			SetItemText(newline_index, 7, _T("��"));
			SetCellColors(newline_index, 7, COLOR_NO, -1);
		}

		if (inf.hasAward == 2){
			SetItemText(newline_index, 8, _T("��"));
			SetCellColors(newline_index, 8, COLOR_YES, -1);
		}else {
			SetItemText(newline_index, 8, _T("��"));
			SetCellColors(newline_index, 8, COLOR_NO, -1);
		}

	}else {
		SetItemText(newline_index, 7, _T("N/A"));
		SetItemText(newline_index, 8, _T("N/A"));
	}

}

bool CMyListCtrlExt::isDataCorrect() {
	bool isCorrect = true;
	for (int i = 0; i < GetItemCount() - 2; i++) {
		for (int j = 3; j <= 6; j++)
		{
			isCorrect = isDataCorrect(i, j);
		}
	}

	return isCorrect;
}

bool CMyListCtrlExt::isDataCorrect(int row, int column) {
	if (GetItemText(row, column) == _T("") || GetItemText(row, column) == _T("����"))
		return false;

// 	if (GetItemText(i, 6) == _T("") ||
// 		GetItemText(i, 6) == _T("����")) {
// 		CString str;
// 		str.Format(_T("%.1f"), _wtof(GetItemText(i, 3)) +
// 			_wtof(GetItemText(i, 4)) + _wtof(GetItemText(i, 5)));
// 		SetItemText(i, 6, str);
// 	}

	return true;
}

bool CMyListCtrlExt::isDataCorrect(std::list<StudentInf> *plist) {
	for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
	StudentsListIterator != plist->end();
		++StudentsListIterator)
	{
		if (StudentsListIterator->mark_subject1 < 0 ||
			StudentsListIterator->mark_subject2 < 0 ||
			StudentsListIterator->mark_subject3 < 0)
			return false;

		if (StudentsListIterator->mark_total < 0)
			StudentsListIterator->mark_total = StudentsListIterator->mark_subject1 +
			StudentsListIterator->mark_subject2 + StudentsListIterator->mark_subject3;
	}

	return true;
}

bool CMyListCtrlExt::markIncorrectCell() {
	bool isCorrect = true;
	for (int i = 0; i < GetItemCount() - 2; i++) {
		for (int j = 3; j <= 6; j++)
		{
			if (!isDataCorrect(i, j))
			{
				isCorrect = false;
				SetItemText(i, j, _T("����"));
				SetCellColors(i, j, COLOR_ERR, -1);
			}
		}
	}
	return isCorrect;
}

void CMyListCtrlExt::RefreshAverage() {

	if (!calcAverage) return;
	float average[4] = { 0,0,0,0 };
	CalculateAverage(average);

	int lastLineIndex = GetItemCount() - 1;
	CString average_str[4];
	for (int i = 0; i < 4; i++)
	{
		average_str[i].Format(_T("%.1f"), average[i]);
		SetItemText(lastLineIndex, i + 3, average_str[i]);
	}

}

void CMyListCtrlExt::CalculateAverage(float average[]) {

	
	for (int i = 0; i < GetItemCount() - 2; i++)
	{
		// �ۼ�����
		average[0] += _wtof(GetItemText(i, 3));
		average[1] += _wtof(GetItemText(i, 4));
		average[2] += _wtof(GetItemText(i, 5));
	}

	int studentNumber = GetItemCount() - 2;
	for (int i = 0; i < 3; i++)
		average[i] /= studentNumber; // ����ѧ����
	average[3] = average[0] + average[1] + average[2]; // ͵����

}

void CMyListCtrlExt::evaluateAward1(std::list<StudentInf> *plist) {
	plist->sort(cmp_total); // �ȴӴ�С����

	for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
	StudentsListIterator != plist->end();
		++StudentsListIterator)
	{
		if (StudentsListIterator->mark_subject1 >= 75 &&
			StudentsListIterator->mark_subject2 >= 75 &&
			StudentsListIterator->mark_subject3 >= 75)
		{
			StudentsListIterator->hasAward = 1;
			return; // ������ֻ��һ�ˣ���������
		}

	}
}

void CMyListCtrlExt::evaluateAward2(std::list<StudentInf> *plist) {
	plist->sort(cmp_total); // �ȴӴ�С����

	int num = 1;
	const int totalNum = GetItemCount() - 2;

	for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
	StudentsListIterator != plist->end();
		++StudentsListIterator)
	{
		if (num <= (int)(totalNum * 0.05 + 0.5) && StudentsListIterator->hasAward != 1) // �����ϲ�����
		{

			if (StudentsListIterator->mark_subject1 >= 75 &&
				StudentsListIterator->mark_subject2 >= 75 &&
				StudentsListIterator->mark_subject3 >= 75)
				StudentsListIterator->hasAward = 2;
			num++;
		}

	}
}

void CMyListCtrlExt::syncToLinkList(std::list<StudentInf> *plist) {
	plist->clear();
	for (int i = 0; i < GetItemCount() - 2; i++)
	{
		plist->push_back(getData(i));
	}
}

StudentInf CMyListCtrlExt::getData(int row)
{
	StudentInf inf;

	inf.studentID = _wtof(GetItemText(row, 0));
	wcscpy_s(inf.name, GetItemText(row, 1));
	wcscpy_s(inf.studentClass, GetItemText(row, 2));
	inf.mark_subject1 = _wtof(GetItemText(row, 3));
	inf.mark_subject2 = _wtof(GetItemText(row, 4));
	inf.mark_subject3 = _wtof(GetItemText(row, 5));
	inf.mark_total = _wtof(GetItemText(row, 6));
	inf.hasAward = 0;
	if (GetItemText(row, 7) == _T("��"))
		inf.hasAward = 1;
	else if (GetItemText(row, 8) == _T("��"))
		inf.hasAward = 2;

	return inf;
}

void CMyListCtrlExt::syncToList(std::list<StudentInf>* plist) {
	calcAverage = false;

	InitializeList();

	calcAverage = false;

	for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
	StudentsListIterator != plist->end();
		++StudentsListIterator)
	{
		AddNewLine(*StudentsListIterator, true);
	}

	calcAverage = true;
}

void CMyListCtrlExt::PrepareList() // ��ʼ���б���ִ��һ�Σ�
{
	SetGridBehaviour();
	SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_INFOTIP);

	InsertColumn(0, _T("ѧ��"), LVCFMT_CENTER, 100);
	InsertColumn(1, _T("����"), LVCFMT_CENTER, 60);
	InsertColumn(2, _T("�༶"), LVCFMT_CENTER, 150);
	InsertColumn(3, _T("Ӣ��ɼ�"), LVCFMT_CENTER, 80);
	InsertColumn(4, _T("��ѧ�ɼ�"), LVCFMT_CENTER, 80);
	InsertColumn(5, _T("C++�ɼ�"), LVCFMT_CENTER, 80);
	InsertColumn(6, _T("�ܳɼ�"), LVCFMT_CENTER, 80);
	InsertColumn(7, _T("�Ƿ�ѧϰ���"), LVCFMT_CENTER, 90);
	InsertColumn(8, _T("�Ƿ�����ѧ��"), LVCFMT_CENTER, 90);

	CRect Rect(CPoint(0, 0), CSize(100, 500));
	m_Edit.Create(WS_CHILD | WS_TABSTOP | WS_BORDER, Rect, this, IDC_EDIT);
	SetDefaultEditor(&m_Edit);
	m_Edit.SetFont(GetFont());

	// ��ʼ������
	SetColumnSorting(0, CListCtrlExt::Auto, CListCtrlExt::StringNumberNoCase);
	SetColumnSorting(1, CListCtrlExt::Auto, CListCtrlExt::StringNoCase);
	SetColumnSorting(2, CListCtrlExt::Auto, CListCtrlExt::StringNoCase);
	SetColumnSorting(3, CListCtrlExt::Auto, CListCtrlExt::Int);
	SetColumnSorting(4, CListCtrlExt::Auto, CListCtrlExt::Int);
	SetColumnSorting(5, CListCtrlExt::Auto, CListCtrlExt::Int);
	SetColumnSorting(6, CListCtrlExt::Auto, CListCtrlExt::Int);
	SetColumnSorting(7, CListCtrlExt::Auto, CListCtrlExt::StringNoCase);
	SetColumnSorting(8, CListCtrlExt::Auto, CListCtrlExt::StringNoCase);

	GetHeaderCtrl()->SetRemovable(0, FALSE);

	InitializeList();
}

void CMyListCtrlExt::InitializeList() { // ��ʼ���б���ִ�ж�Σ�
	calcAverage = false;
	DeleteAllItems();

	int averageIndex = InsertItem(GetItemCount(), _T("ƽ��ֵ"));
	for (int i = 0; i < 4; i++)
		SetItemText(averageIndex, i + 3, _T("N/A"));
	SetRowColors(averageIndex, RGB(28, 28, 28), -1);
	SetRowReadOnly(averageIndex);

	InsertItem(GetItemCount() - 1, _T("          +"));
	SetRowReadOnly(GetItemCount() - 1);

	calcAverage = true;
}

void CMyListCtrlExt::OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	if (GetItemCount() > 2 && calcAverage)
		RefreshAverage();

	*pResult = 0;
}


void CMyListCtrlExt::OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView)
	{
		int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

		// 		int deletingIndex = GetSelectionMark();
		// 		if (GetItemCount() > 2 && nItem <= GetItemCount() - 3) {
		// 			CString deletingItem_ID = GetItemText(deletingIndex, 0);
		// 			for (std::list<StudentInf>::iterator StudentsListIterator = StudentInf_list.begin();
		// 			StudentsListIterator != StudentInf_list.end();
		// 				++StudentsListIterator)
		// 			{
		// 				if (StudentsListIterator->studentID == _wtof(deletingItem_ID)) { // ѧ��һ��
		// 					StudentInf_list.erase(StudentsListIterator);
		// 					break;
		// 				}
		// 			}
		
		//}

	}

	if (GetItemCount() > 2 && calcAverage)
		RefreshAverage();

	*pResult = 0;
}


void CMyListCtrlExt::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView)
	{
		int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

		if (GetItemCount() > 2 && nItem != GetItemCount() - 1 &&
			calcAverage)
			RefreshAverage();
	}

	*pResult = 0;
}
