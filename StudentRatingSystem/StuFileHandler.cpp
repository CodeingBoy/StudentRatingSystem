#include "stdafx.h"
#include "StuFileHandler.h"
#include <string.h>

CStuFileHandler::CStuFileHandler(const wchar_t *filename, bool bRead) :
    CFileHandler(filename, bRead)
{

}


CStuFileHandler::~CStuFileHandler()
{
    CFileHandler::~CFileHandler();
}

bool CStuFileHandler::SaveFile(bool haveHeader, std::vector<StudentInf> *plist)
{
    if (haveHeader)
        WriteLine(_T("学号,姓名,班级,英语成绩,数学成绩,C++成绩,总成绩,获奖情况"));

    for (std::vector<StudentInf>::iterator StudentsListIterator = plist->begin();
            StudentsListIterator != plist->end();
            ++StudentsListIterator) {
        CString line;
        ComposeLine(*StudentsListIterator, line);
        WriteLine(line.GetBuffer());
    }

    return true;
}

bool CStuFileHandler::SaveFile(bool haveHeader, CMyListCtrlExt *plist)
{
    if (haveHeader)
        WriteLine(_T("学号,姓名,班级,英语成绩,数学成绩,C++成绩,总成绩,获奖情况"));

    for (int i = 0; i < plist->GetItemCount() - 2; i++) {
        CString line;
        ComposeLine(plist->GetData(i) , line);
        WriteLine(line.GetBuffer());
    }

    return true;
}

bool CStuFileHandler::ComposeLine(StudentInf &inf, CString &str)
{
    CString award;
    switch (inf.hasAward) {
        case 1:
            award = _T("学习标兵");
            break;
        case 2:
            award = _T("三好学生");
            break;
        default:
            award = _T("未获奖");
            break;
    }

    str.Format(_T("%.0f,%s,%s,%.1f,%.1f,%.1f,%.1f,%s"),
               inf.studentID, inf.name, inf.studentClass, inf.mark_subject1, inf.mark_subject2,
               inf.mark_subject3, inf.mark_total, award);
    return true;
}
