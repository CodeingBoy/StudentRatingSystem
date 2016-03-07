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
	bool saveFile(bool haveHeader, std::list<StudentInf>* plist);
	bool saveFile(bool haveHeader, CMyListCtrlExt * plist);
	bool parseFile(bool haveHeader, std::list<StudentInf>* plist);
	bool parseFile(bool haveHeader, CMyListCtrlExt * plist);
	bool parseLine(wchar_t * line, StudentInf & inf);
	bool parseLine(StudentInf & inf);
	bool composeLine(StudentInf & inf, CString & str);
	bool saveAwardList(std::list<StudentInf> *plist);
	bool readLine(wchar_t * output);
	bool writeLine(wchar_t * content);
	int err;
	bool hasExtraInf = false;
	bool hasDataError = false;
private:
	bool bRead = true; // ��ȡ���Ǳ���
	FILE *fp;
};

