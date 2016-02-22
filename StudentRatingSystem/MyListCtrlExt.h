#pragma once
#include "ListCtrlExt.h"
#include "StudentInf.h"

#include <list>
#include <algorithm>

#define IDC_EDIT 1007

#define COLOR_ERR RGB(255, 0, 0)
#define COLOR_YES RGB(134, 71, 63)
#define COLOR_NO RGB(100, 106, 88)

class CMyListCtrlExt :
	public CListCtrlExt
{
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnNMDblclk(NMHDR * pNMHDR, LRESULT * pResult);
private:
	CEdit m_Edit;
public:
	CMyListCtrlExt();
	~CMyListCtrlExt();
	void AddNewLine(StudentInf & inf, bool hasAwardInf = false);
	bool isDataCorrect();
	bool isDataCorrect(int row, int column);
	bool isDataCorrect(std::list<StudentInf>* plist);
	bool markIncorrectCell();
	void RefreshAverage();
	void CalculateAverage(float average[]);
	void evaluateAward1(std::list<StudentInf>* plist);
	void evaluateAward2(std::list<StudentInf>* plist);
	void syncToLinkList(std::list<StudentInf>* plist);
	StudentInf getData(int row);
	void syncToList(std::list<StudentInf>* plist);
	void PrepareList();
	void InitializeList();
	bool calcAverage = true;
	afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

