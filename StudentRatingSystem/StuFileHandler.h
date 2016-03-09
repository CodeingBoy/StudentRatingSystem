#pragma once

#include "StudentInf.h"
#include "StudentRatingSystemDlg.h"
#include "MyListCtrlExt.h"

#include <list>
#include <algorithm>

class CStuFileHandler
{
    public:
        CStuFileHandler(const wchar_t * filename, bool bRead = true);
        ~CStuFileHandler();
        bool SaveFile(bool haveHeader, std::list<StudentInf>* plist);
        bool SaveFile(bool haveHeader, CMyListCtrlExt * plist);
        bool ParseFile(bool haveHeader, std::list<StudentInf>* plist);
        bool ParseFile(bool haveHeader, CMyListCtrlExt * plist);
        bool ParseLine(wchar_t * line, StudentInf & inf);
        bool ParseLine(StudentInf & inf);
        bool ComposeLine(StudentInf & inf, CString & str);
        bool SaveAwardList(std::list<StudentInf> *plist);
        bool ReadLine(wchar_t * output);
        bool WriteLine(wchar_t * content);
        bool HasExtraInf();
        bool HasDataError();
        int GetError();
        unsigned int GetParsedLine();
    private:
        bool bRead = true; // 读取还是保存
        int err;
        int parsedLine = 0;
        bool hasExtraInf = false;
        bool hasDataError = false;
        FILE *fp;
};

