#pragma once

#include "StudentInf.h"
#include "StudentRatingSystemDlg.h"
#include "FileHandler.h"

#include <vector>
#include <algorithm>

class CMyListCtrlExt;

class CStuFileHandler:
    public CFileHandler
{
    public:
        CStuFileHandler(const wchar_t *filename, bool bRead = true);
        ~CStuFileHandler();
        bool SaveFile(bool haveHeader, std::vector<StudentInf> *plist);
        bool SaveFile(bool haveHeader, CMyListCtrlExt *plist);
        bool ComposeLine(StudentInf &inf, CString &str);
};

