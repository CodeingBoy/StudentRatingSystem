#pragma once

#include "StudentInf.h"

#include <list>
#include <algorithm>

class CStuFileHandler
{
public:
	CStuFileHandler(const wchar_t * filename, bool bRead = true);
	~CStuFileHandler();
	bool parseFile(bool haveHeader, std::list<StudentInf>* plist);
	bool parseLine(wchar_t * line, StudentInf & inf);
	bool parseLine(StudentInf & inf);
	bool readLine(wchar_t * output);
	int err;
private:
	bool bRead = true; // 读取还是保存
	FILE *fp;
};

