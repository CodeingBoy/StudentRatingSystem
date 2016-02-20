
// StudentRatingSystemDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "MyListCtrlExt.h"
#include "StudentInf.h"

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

	void AddNewLine(StudentInf & inf);

	void RefreshAverage();

	void CalculateAverage();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CEdit m_Edit;
public:
	CMyListCtrlExt m_studentInfList;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
private:
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnNMDblclkStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
};
