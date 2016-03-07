#include "stdafx.h"
#include "StuFileHandler.h"
#include <string.h>

CStuFileHandler::CStuFileHandler(const wchar_t *filename, bool bRead)
{
	if (bRead) {
		if (err = _wfopen_s(&fp, filename, _T("r,ccs=UTF-8")))   // err
			return;
	}else {
		if (err = _wfopen_s(&fp, filename, _T("w,ccs=UTF-8")))  // err
			return;
	}
}


CStuFileHandler::~CStuFileHandler()
{
	if (fp)
		fclose(fp);
}

bool CStuFileHandler::saveFile(bool haveHeader, std::list<StudentInf> *plist) {
	if (haveHeader)
		writeLine(_T("ѧ��,����,�༶,Ӣ��ɼ�,��ѧ�ɼ�,C++�ɼ�,�ܳɼ�,�����"));

	for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
	StudentsListIterator != plist->end();
		++StudentsListIterator)
	{
		CString line;
		composeLine(*StudentsListIterator, line);
		writeLine(line.GetBuffer());
	}

	return true;
}

bool CStuFileHandler::saveFile(bool haveHeader, CMyListCtrlExt *plist) {
	if (haveHeader)
		writeLine(_T("ѧ��,����,�༶,Ӣ��ɼ�,��ѧ�ɼ�,C++�ɼ�,�ܳɼ�,�����"));

	for (int i = 0; i < plist->GetItemCount() - 2; i++) {
		CString line;
		composeLine(plist->GetData(i) , line);
		writeLine(line.GetBuffer());
	}

	return true;
}

bool CStuFileHandler::parseFile(bool haveHeader, std::list<StudentInf> *plist) {
	if (haveHeader) {
		wchar_t temp[1024];
		readLine(temp); // ������һ��
	}

	StudentInf inf;
	while (!feof(fp)) {
		if (parseLine(inf))
			plist->push_back(inf);
	}

	return true;
}

bool CStuFileHandler::parseFile(bool haveHeader, CMyListCtrlExt *plist) {
	if (haveHeader)	{
		wchar_t temp[1024];
		readLine(temp); // ������һ��
	}

	StudentInf inf;
	while (!feof(fp)) {
		if (parseLine(inf))
			plist->AddNewLine(inf);
	}

	plist->RefreshAverage();

	return true;
}

bool CStuFileHandler::parseLine(wchar_t *line, StudentInf &inf)
{
	// �ָ��ַ���
	wchar_t *pStr, *pContext;
	int times = 0;
	pStr = wcstok_s(line, _T(","), &pContext);

	bool hasLineError = false;
	while (pStr)
	{
		times++;
		switch (times)
		{
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
	

	return true;
}

bool CStuFileHandler::parseLine(StudentInf &inf)
{
	wchar_t line[1024];
	memset(line, NULL, 1024); // ����Ϊ��
	if (!readLine(line) || !wcscmp(line, _T("")))
		return false;

	return parseLine(line, inf);
}

bool CStuFileHandler::composeLine(StudentInf &inf, CString &str)
{
	CString award;
	switch (inf.hasAward)
	{
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

bool CStuFileHandler::saveAwardList(std::list<StudentInf> *plist) {
	writeLine(_T("ѧϰ�����"));
	for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
	StudentsListIterator != plist->end();
		++StudentsListIterator)
	{
		if (StudentsListIterator->hasAward == 1)
		{
			writeLine(StudentsListIterator->name);
		}

	}

	writeLine(_T("")); // ����
	writeLine(_T("����ѧ����"));
	for (std::list<StudentInf>::iterator StudentsListIterator = plist->begin();
	StudentsListIterator != plist->end();
		++StudentsListIterator) {
		if (StudentsListIterator->hasAward == 2) {
			writeLine(StudentsListIterator->name);
		}

	}

	return true;
}

bool CStuFileHandler::readLine(wchar_t *output) {
	if (!fp || feof(fp))return false;
	fgetws(output, 1024, fp);  //��ȡһ��
	return true;
}

bool CStuFileHandler::writeLine(wchar_t *content) {
	if (!fp || feof(fp))return false;
	fputws(content, fp);
	fputws(_T("\n"), fp);
	return true;
}