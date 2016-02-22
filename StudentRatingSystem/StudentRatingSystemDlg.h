
// StudentRatingSystemDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "MyListCtrlExt.h"
#include "StudentInf.h"

#include <list>
#include <algorithm>
#include "afxwin.h"

// CStudentRatingSystemDlg 对话框
class CStudentRatingSystemDlg : public CDialogEx
{
// 构造
public:
	CStudentRatingSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTRATING_MAINDIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void PrepareList();
	void InitializeList();
	void AddNewLine(StudentInf & inf, bool hasAwardInf = false);
	void RefreshAverage();
	void CalculateAverage(float average[]);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CEdit m_Edit;
public:
	CMyListCtrlExt m_studentInfList;
	afx_msg void OnBnClickedDelete();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedImport();
	afx_msg void OnBnClickedExport();
	std::list<StudentInf> StudentInf_list;
	afx_msg void OnLvnItemchangedStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitemStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnInsertitemStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedevaluateaward1();
	void evaluateAward1(std::list<StudentInf>* plist);
	void evaluateAward2(std::list<StudentInf>* plist);
	afx_msg void OnBnClickedevaluateaward2();
	afx_msg void OnBnClickedDeleteall();
	void syncToLinkList();
	void syncToList();
	bool isDataCorrect(std::list<StudentInf>* plist);
	bool isDataCorrect();
	void OnBnClickedCheck();
private:
	bool calcAverage = true;
};

bool cmp_total(StudentInf first, StudentInf second);
