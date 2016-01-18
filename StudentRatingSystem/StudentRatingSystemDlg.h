
// StudentRatingSystemDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ListCtrlExt.h"

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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CEdit m_Edit;
	CComboBox m_Combo;
	CDateTimeCtrl m_DT;
	CListCtrlExt m_List;
public:
	CListCtrl m_studentInfList;
	CListCtrlExt m_studentInfList1;
	CTabCtrl m_classTab;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	CEdit m_listEditor;
//	afx_msg void OnNMDblclkStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
};
