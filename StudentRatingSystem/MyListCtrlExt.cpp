#include "stdafx.h"
#include "MyListCtrlExt.h"

#include <vector>
#include <map>
#include <algorithm>
#include "StuFileHandler.h"
#include "resource.h"


bool cmp_total(StudentInf first, StudentInf second)
{
    if (first.mark_total <= second.mark_total)
        return false;
    else
        return true;
}

bool cmp_class(StudentInf first, StudentInf second)
{
    if (wcscmp(first.studentClass, second.studentClass))
        return true;
    else
        return false;
}

CMyListCtrlExt::CMyListCtrlExt()
{
    //m_Edit = new CEdit();
}


CMyListCtrlExt::~CMyListCtrlExt()
{
    //delete m_Edit;
}

BOOL CMyListCtrlExt::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
    if (pNMListView) {
        int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

        if (nItem == GetItemCount() - 2) {
            // 双击了添加的一行
            InsertItem(GetItemCount() - 2, _T("")); // 在+行之上新建空行
        }
    }

    return CListCtrlExt::OnNMDblclk(pNMHDR, pResult);
}

BEGIN_MESSAGE_MAP(CMyListCtrlExt, CListCtrlExt)
    ON_WM_LBUTTONDOWN()
    ON_NOTIFY_REFLECT(LVN_INSERTITEM, &CMyListCtrlExt::OnLvnInsertitem)
    ON_NOTIFY_REFLECT(LVN_DELETEITEM, &CMyListCtrlExt::OnLvnDeleteitem)
END_MESSAGE_MAP()


void CMyListCtrlExt::OnLButtonDown(UINT nFlags, CPoint point)
{
    HideEditor(); // 隐藏编辑器

    CListCtrlExt::OnLButtonDown(nFlags, point);
}

void CMyListCtrlExt::AddNewLine(StudentInf &inf)
{
    int newline_index = GetItemCount() - 2; // 最后一行显示平均值，倒数第二行为预留

    CString ID, mark[4];
    ID.Format(_T("%.0f"), inf.studentID);
    mark[0].Format(_T("%.1f"), inf.mark_subject1);
    mark[1].Format(_T("%.1f"), inf.mark_subject2);
    mark[2].Format(_T("%.1f"), inf.mark_subject3);
    mark[3].Format(_T("%.1f"), inf.mark_total);

    InsertItem(newline_index, ID);
    SetItemText(newline_index, 1, inf.name);
    SetItemText(newline_index, 2, inf.studentClass);
    for (int i = 0; i < 4; i++) {
        if (mark[i] == _T("-1.0")) {
            SetItemText(newline_index, i + 3, _T("错误"));
            SetCellColors(newline_index, i + 3, COLOR_ERR, -1);
        } else {
            SetItemText(newline_index, i + 3, mark[i]);
        }
    }

    if (inf.hasAward == -1) {
        SetItemText(newline_index, 7, _T("N/A"));
        SetItemText(newline_index, 8, _T("N/A"));
    } else {
        if (inf.hasAward == 1) {
            SetItemText(newline_index, 7, _T("是"));
            SetCellColors(newline_index, 7, COLOR_YES, -1);
        } else {
            SetItemText(newline_index, 7, _T("否"));
            SetCellColors(newline_index, 7, COLOR_NO, -1);
        }

        if (inf.hasAward == 2) {
            SetItemText(newline_index, 8, _T("是"));
            SetCellColors(newline_index, 8, COLOR_YES, -1);
        } else {
            SetItemText(newline_index, 8, _T("否"));
            SetCellColors(newline_index, 8, COLOR_NO, -1);
        }
    }

    // 将添加的单元计入总计中
    total[0] += inf.mark_subject1;
    total[1] += inf.mark_subject2;
    total[2] += inf.mark_subject3;

}

bool CMyListCtrlExt::isDataCorrect()
{
    isCorrect = true;
    for (int i = 0; i < GetItemCount() - 2; i++) {
        for (int j = 3; j <= 6; j++)
            if (!(isCorrect = isDataCorrect(i, j)))
                return false;
    }
    return isCorrect;
}

bool CMyListCtrlExt::isDataCorrect(int row, int column)
{
    if (GetItemText(row, column) == _T("") || GetItemText(row, column) == _T("错误"))
        return false;

    return true;
}

bool CMyListCtrlExt::isDataCorrect(std::vector<StudentInf> *plist)
{
    for (std::vector<StudentInf>::iterator ListIterator = plist->begin();
            ListIterator != plist->end();
            ++ListIterator) {
        if (ListIterator->mark_subject1 < 0 ||
                ListIterator->mark_subject2 < 0 ||
                ListIterator->mark_subject3 < 0)
            return false;

        if (ListIterator->mark_total < 0)
            ListIterator->mark_total = ListIterator->mark_subject1 +
                                       ListIterator->mark_subject2 +
                                       ListIterator->mark_subject3;
    }

    return true;
}

bool CMyListCtrlExt::MarkIncorrectCell()
{
    bool isCorrect = true;
    for (int i = 0; i < GetItemCount() - 2; i++) {
        for (int j = 3; j <= 6; j++) {
            if (!isDataCorrect(i, j)) {
                isCorrect = false;
                SetItemText(i, j, _T("错误"));
                SetCellColors(i, j, COLOR_ERR, -1);
            }
        }
    }
    return isCorrect;
}

void CMyListCtrlExt::RefreshAverage()
{
    int lastLineIndex = GetItemCount() - 1;
    if (!isCorrect) {
        for (int i = 0; i < 4; i++)
            SetItemText(lastLineIndex, i + 3, _T("错误"));
        return;
    }

    double average[4] = { 0, 0, 0, 0 };
    CalculateAverage(average);

    CString average_str[4];
    for (int i = 0; i < 4; i++) {
        average_str[i].Format(_T("%.1f"), average[i]);
        SetItemText(lastLineIndex, i + 3, average_str[i]);
    }

}

void CMyListCtrlExt::CalculateAverage(double average[])
{
    // 从总和中提取数据
    average[0] = total[0];
    average[1] = total[1];
    average[2] = total[2];
    average[3] = total[0] + total[1] + total[2];

    int studentNumber = GetItemCount() - 2;
    for (int i = 0; i < 4; i++)
        average[i] /= studentNumber; // 除以学生数
}

void CMyListCtrlExt::MarkNotEnoughCell(bool isMark)
{
    for (int i = 0; i < GetItemCount() - 2; i++) {
        for (int j = 3; j <= 5; j++) {
            CString itemText = GetItemText(i, j);
            if (!wcscmp(itemText, _T("错误")))
                continue;
            if (_wtof(itemText) < 75 && isMark)
                SetCellColors(i, j, COLOR_NOT_ENOUGH, -1);
            else
                SetCellColors(i, j, -1, -1);
        }
    }
}

void CMyListCtrlExt::MarkNotEnoughCell(int nRow, int nCol)
{
    if (_wtof(GetItemText(nRow, nCol)) < 75)
        SetCellColors(nRow, nCol, COLOR_NOT_ENOUGH, -1);
    else
        SetCellColors(nRow, nCol, -1, -1);
}

std::vector<StudentInf> CMyListCtrlExt::EvaluateAward(std::vector<StudentInf> *plist, bool isAwardOne)
{
    ClassMap *pclassMap = getClassMap(*plist);   // 按班级排列

    std::vector<StudentInf> rtnList;

    // 遍历
    for (ClassMap::iterator iter = pclassMap->begin(); iter != pclassMap->end(); iter = pclassMap->upper_bound(iter->first)) {
        std::vector<StudentInf> classList;

        std::pair<ClassMap::iterator, ClassMap::iterator> res = pclassMap->equal_range(iter->first);
        for (ClassMap::iterator i = res.first; i != res.second; ++i) {
            classList.push_back(*i->second);
        }

        if (isAwardOne)
            EvaluateAward1(&classList);
        else
            EvaluateAward2(&classList);

        for (std::vector<StudentInf>::iterator rtnIterator = classList.begin();
                rtnIterator != classList.end(); rtnIterator++) {
            rtnList.push_back(*rtnIterator);
        }
    }

    delete pclassMap;

    return rtnList;
}

void CMyListCtrlExt::EvaluateAward1(std::vector<StudentInf> *plist)
{
    sort(plist->begin(), plist->end(), cmp_total);  // 按总分排序

    for (std::vector<StudentInf>::iterator StudentsListIterator = plist->begin();
            StudentsListIterator != plist->end();
            ++StudentsListIterator) {
        if (StudentsListIterator->mark_subject1 >= 75 &&
                StudentsListIterator->mark_subject2 >= 75 &&
                StudentsListIterator->mark_subject3 >= 75) {
            StudentsListIterator->hasAward = 1;
            return; // 获奖名额只有一人，评定结束
        }
    }
}

void CMyListCtrlExt::EvaluateAward2(std::vector<StudentInf> *plist)
{
    sort(plist->begin(), plist->end(), cmp_total);  // 按总分排序

    int num = 1;
    const int totalNum = GetItemCount() - 2;

    for (std::vector<StudentInf>::iterator StudentsListIterator = plist->begin();
            StudentsListIterator != plist->end();
            ++StudentsListIterator) {
        if (num <= (int)(totalNum * 0.05 + 0.5) && StudentsListIterator->hasAward != 1) { // 不符合不评比

            if (StudentsListIterator->mark_subject1 >= 75 &&
                    StudentsListIterator->mark_subject2 >= 75 &&
                    StudentsListIterator->mark_subject3 >= 75)
                StudentsListIterator->hasAward = 2;
            num++;
        }

    }
}

void CMyListCtrlExt::GetVector(std::vector<StudentInf> *plist)
{
    plist->clear();
    for (int i = 0; i < GetItemCount() - 2; i++) {
        StudentInf inf = GetData(i);
        plist->push_back(inf);

    }
}

StudentInf CMyListCtrlExt::GetData(int row)
{
    StudentInf inf;

    inf.studentID = _wtof(GetItemText(row, 0));
    wcscpy(inf.name, GetItemText(row, 1));
    wcscpy(inf.studentClass, GetItemText(row, 2));
    inf.mark_subject1 = _wtof(GetItemText(row, 3));
    inf.mark_subject2 = _wtof(GetItemText(row, 4));
    inf.mark_subject3 = _wtof(GetItemText(row, 5));
    inf.mark_total = _wtof(GetItemText(row, 6));
    inf.hasAward = 0;
    if (GetItemText(row, 7) == _T("是"))
        inf.hasAward = 1;
    else if (GetItemText(row, 8) == _T("是"))
        inf.hasAward = 2;

    return inf;
}

void CMyListCtrlExt::SyncToList(std::vector<StudentInf> *plist)
{

    InitializeList();

    for (std::vector<StudentInf>::iterator StudentsListIterator = plist->begin();
            StudentsListIterator != plist->end();
            ++StudentsListIterator)
        AddNewLine(*StudentsListIterator);


}

void CMyListCtrlExt::PrepareList() // 初始化列表（仅执行一次）
{
    SetGridBehaviour();
    SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_INFOTIP);

    InsertColumn(0, _T("学号"), LVCFMT_CENTER, 100);
    InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 60);
    InsertColumn(2, _T("班级"), LVCFMT_CENTER, 150);
    InsertColumn(3, _T("英语成绩"), LVCFMT_CENTER, 80);
    InsertColumn(4, _T("数学成绩"), LVCFMT_CENTER, 80);
    InsertColumn(5, _T("C++成绩"), LVCFMT_CENTER, 80);
    InsertColumn(6, _T("总成绩"), LVCFMT_CENTER, 80);
    InsertColumn(7, _T("是否学习标兵"), LVCFMT_CENTER, 90);
    InsertColumn(8, _T("是否三好学生"), LVCFMT_CENTER, 90);

    CRect Rect(CPoint(0, 0), CSize(100, 500));
    m_Edit.Create(WS_CHILD | WS_TABSTOP | WS_BORDER, Rect, this, IDC_EDIT);
    m_Edit.SetFont(GetFont());
    SetDefaultEditor(&m_Edit);

    // 初始化排序
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

void CMyListCtrlExt::InitializeList()   // 初始化列表（可执行多次）
{
    DeleteAllItems();

    total[0] = total[1] = total[2] = total[3] = 0;

    int averageIndex = InsertItem(GetItemCount(), _T("平均值"));
    for (int i = 0; i < 4; i++)
        SetItemText(averageIndex, i + 3, _T("N/A"));
    SetRowColors(averageIndex, RGB(227, 227, 227), -1);
    SetRowReadOnly(averageIndex);

    InsertItem(GetItemCount() - 1, _T("          +"));
    SetRowReadOnly(GetItemCount() - 1);

}

void CMyListCtrlExt::OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    if (GetItemCount() > 2)
        RefreshAverage();

    *pResult = 0;
}


void CMyListCtrlExt::OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
    if (pNMListView) {
        int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

        // 将删除的单元从总计中剔除
        total[0] -= _wtof(GetItemText(nItem, 3));
        total[1] -= _wtof(GetItemText(nItem, 4));
        total[2] -= _wtof(GetItemText(nItem, 5));
    }

    if (GetItemCount() > 2)
        RefreshAverage();

    *pResult = 0;
}

BOOL CMyListCtrlExt::DisplayEditor(int nItem, int nSubItem)
{
    if (nItem == GetItemCount() - 2)
        return 0;

    BOOL rtnval = CListCtrlExt::DisplayEditor(nItem, nSubItem);

    if (nSubItem >= 3 && nSubItem <= 5) {
        modifingItem = nItem;
        modifingSubItem = nSubItem;

        // 将删除的单元从总计中剔除
        total[nSubItem - 3] -= _wtof(GetItemText(nItem, nSubItem));
    }

    m_Edit.SetFocus();

    return rtnval;
}

void CMyListCtrlExt::HideEditor(BOOL bUpdate)
{
    CListCtrlExt::HideEditor(bUpdate);

    if (GetItemCount() <= 2)
        return;

    if (modifingItem != -1 && modifingSubItem != -1) {
        // 将改动后的数据重新加入
        double temp = _wtof(GetItemText(modifingItem, modifingSubItem));
        total[modifingSubItem - 3] += _wtof(GetItemText(modifingItem, modifingSubItem));

        // 重新计算总分
        CString totalScore;
        totalScore.Format(_T("%.1f"), _wtof(GetItemText(modifingItem, 3)) + _wtof(GetItemText(modifingItem, 4))
                          + _wtof(GetItemText(modifingItem, 5)));
        SetItemText(modifingItem, 6, totalScore);

        if (((CButton *)AfxGetMainWnd()->GetDlgItem(IDC_MARK_SCORE))->GetCheck() == BST_CHECKED)
            MarkNotEnoughCell(modifingItem, modifingSubItem);

        modifingItem = -1;
        modifingSubItem = -1;

        RefreshAverage();
    }
}

bool CMyListCtrlExt::SaveAwardList(CStuFileHandler &handler)
{
    std::vector<StudentInf> container;
    GetVector(&container);
    ClassMap *pclassMap = getClassMap(container);   // 按班级排列

    std::vector<StudentInf> rtnList;

    // 遍历
    for (ClassMap::iterator iter = pclassMap->begin(); iter != pclassMap->end(); iter = pclassMap->upper_bound(iter->first)) {
        std::vector<StudentInf> classList;

        handler.WriteLine(_T("*********************"));
        handler.Write((*iter->second).studentClass);
        handler.WriteLine(_T("："));

        handler.WriteLine(_T("")); // 换行
        handler.WriteLine(_T("学习标兵："));
        std::pair<ClassMap::iterator, ClassMap::iterator> res = pclassMap->equal_range(iter->first);
        for (ClassMap::iterator i = res.first; i != res.second; ++i) {

            if ((*i->second).hasAward == 1)
                handler.WriteLine((*i->second).name);
        }

        handler.WriteLine(_T("")); // 换行
        handler.WriteLine(_T("三好学生："));
        res = pclassMap->equal_range(iter->first);
        for (ClassMap::iterator i = res.first; i != res.second; ++i) {

            if ((*i->second).hasAward == 2)
                handler.WriteLine((*i->second).name);


        }

        handler.WriteLine(_T("*********************"));
        handler.WriteLine(_T("")); // 换行
    }

    delete pclassMap;

    return true;
}

ClassMap *CMyListCtrlExt::getClassMap(std::vector<StudentInf> &container)
{
    ClassMap *pclassMap = new std::multimap<CString, StudentInf *>;

    for (std::vector<StudentInf>::iterator classListIterator = container.begin();
            classListIterator != container.end(); classListIterator++) {
        pclassMap->insert(std::make_pair(CString(classListIterator->studentClass), classListIterator._Ptr));
    }

    return pclassMap;
}

bool CMyListCtrlExt::HasData()
{
    return GetItemCount() > 2;
}