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
        WriteLine(_T("ѧ��,����,�༶,Ӣ��ɼ�,��ѧ�ɼ�,C++�ɼ�,�ܳɼ�,�����"));

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
        WriteLine(_T("ѧ��,����,�༶,Ӣ��ɼ�,��ѧ�ɼ�,C++�ɼ�,�ܳɼ�,�����"));

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
            award = _T("ѧϰ���");
            break;
        case 2:
            award = _T("����ѧ��");
            break;
        default:
            award = _T("δ��");
            break;
    }

    str.Format(_T("%.0f,%s,%s,%.1f,%.1f,%.1f,%.1f,%s"),
               inf.studentID, inf.name, inf.studentClass, inf.mark_subject1, inf.mark_subject2,
               inf.mark_subject3, inf.mark_total, award);
    return true;
}
