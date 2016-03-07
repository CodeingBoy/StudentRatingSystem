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
	afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnNMDblclk(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CEdit m_Edit;
	bool isCorrect = true;
	double total[4] = { 0.0 };
public:
	CMyListCtrlExt();
	~CMyListCtrlExt();

	void AddNewLine(StudentInf & inf);
	bool isDataCorrect();
	bool isDataCorrect(int row, int column);
	bool isDataCorrect(std::list<StudentInf>* plist);
	bool MarkIncorrectCell();
	void RefreshAverage();
	void CalculateAverage(double average[]);
	void EvaluateAward1(std::list<StudentInf>* plist);
	void EvaluateAward2(std::list<StudentInf>* plist);
	void GetLinkList(std::list<StudentInf>* plist);
	StudentInf GetData(int row);
	void SyncToList(std::list<StudentInf>* plist);
	void PrepareList();
	void InitializeList();
	BOOL DisplayEditor(int nItem, int nSubItem);
	int modifingItem = 0, modifingSubItem = 0;
	void HideEditor(BOOL bUpdate = TRUE);
};

