#include "stdafx.h"
#include "StuFileHandler.h"
#include <string.h>

CStuFileHandler::CStuFileHandler(const wchar_t *filename, bool bRead)
{
    if (bRead) {
        if (err = _wfopen_s(&fp, filename, _T("r,ccs=UTF-8")))   // err
            return;
    } else {
        if (err = _wfopen_s(&fp, filename, _T("w,ccs=UTF-8")))  // err
            return;
    }
}


CStuFileHandler::~CStuFileHandler()
{
    if (fp)
        fclose(fp);
}

bool CStuFileHandler::SaveFile(bool haveHeader, std::list<StudentInf> *plist)
{
    if (haveHeader)
        WriteLine(_T("学号,姓名,班级,英语成绩,数学成绩,C++成绩,总成绩,获奖情况"));

    for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
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

bool CStuFileHandler::ParseFile(bool haveHeader, std::list<StudentInf> *plist)
{
    if (haveHeader) {
        wchar_t temp[1024];
        ReadLine(temp); // 丢弃第一行
    }

    StudentInf inf;
    while (!feof(fp)) {
        if (ParseLine(inf))
            plist->push_back(inf);
    }

    return true;
}

bool CStuFileHandler::ParseFile(bool haveHeader, CMyListCtrlExt *plist)
{
    if (haveHeader) {
        wchar_t temp[1024];
        ReadLine(temp); // 丢弃第一行
    }

    StudentInf inf;
    while (!feof(fp)) {
        if (ParseLine(inf))
            plist->AddNewLine(inf);
    }

    return true;
}

bool CStuFileHandler::ParseLine(wchar_t *line, StudentInf &inf)
{
    // 分割字符串
    wchar_t *pStr, *pContext;
    int times = 0;
    pStr = wcstok_s(line, _T(","), &pContext);

    bool hasLineError = false;
    while (pStr) {
        times++;
        switch (times) {
        case 1:
            inf.studentID = _wtof(pStr);
            break;
        case 2:
            wcscpy_s(inf.name, pStr);
            break;
        case 3:
            wcscpy_s(inf.studentClass, pStr);
            break;
        case 4:
            inf.mark_subject1 = _wtof(pStr);
            break;
        case 5:
            inf.mark_subject2 = _wtof(pStr);
            break;
        case 6:
            inf.mark_subject3 = _wtof(pStr);

            if (!hasLineError)
                inf.mark_total = inf.mark_subject1 + inf.mark_subject2 + inf.mark_subject3;
            break;
        default:
            hasExtraInf = true;
            break;
        }
        pStr = wcstok_s(pContext, _T(","), &pContext);


        if (times < 6 && (pStr == NULL || !wcscmp(pStr,_T("\n")))) {
            hasDataError = true;
            hasLineError = true;
            inf.mark_total = -1;
            pStr = _T("-1");
        }
    }

    parsedLine++;

    return true;
}

bool CStuFileHandler::ParseLine(StudentInf &inf)
{
    wchar_t line[1024];
    memset(line, NULL, 1024); // 设置为空
    if (!ReadLine(line) || !wcscmp(line, _T("")))
        return false;

    return ParseLine(line, inf);
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

bool CStuFileHandler::SaveAwardList(std::list<StudentInf> *plist)
{
    WriteLine(_T("学习标兵："));
    for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
            StudentsListIterator != plist->end();
            ++StudentsListIterator) {
        if (StudentsListIterator->hasAward == 1) {
            WriteLine(StudentsListIterator->name);
        }

    }

    WriteLine(_T("")); // 换行
    WriteLine(_T("三好学生："));
    for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
            StudentsListIterator != plist->end();
            ++StudentsListIterator) {
        if (StudentsListIterator->hasAward == 2) {
            WriteLine(StudentsListIterator->name);
        }

    }

    return true;
}

bool CStuFileHandler::ReadLine(wchar_t *output)
{
    if (!fp || feof(fp))return false;
    fgetws(output, 1024, fp);  //读取一行
    return true;
}

bool CStuFileHandler::WriteLine(wchar_t *content)
{
    if (!fp || feof(fp))return false;
    fputws(content, fp);
    fputws(_T("\n"), fp);
    return true;
}

bool CStuFileHandler::HasExtraInf()
{
    return hasExtraInf;
}

bool CStuFileHandler::HasDataError()
{
    return hasDataError;
}

int CStuFileHandler::GetError()
{
    return err;
}

unsigned int CStuFileHandler::GetParsedLine()
{
    return parsedLine;
}