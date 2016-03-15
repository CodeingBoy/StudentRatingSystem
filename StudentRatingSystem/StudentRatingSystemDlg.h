
// StudentRatingSystemDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "MyListCtrlExt.h"
#include "StudentInf.h"

#include "afxwin.h"



// CStudentRatingSystemDlg 对话框
class CStudentRatingSystemDlg : public CDialogEx
{
// 构造
    public:
        CStudentRatingSystemDlg(CWnd* pParent = NULL);  // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_STUDENTRATING_MAINDIALOG };
#endif

    protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


// 实现
    protected:
        HICON m_hIcon;

        // 生成的消息映射函数
        virtual BOOL OnInitDialog();
        afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
        afx_msg void OnPaint();
        afx_msg HCURSOR OnQueryDragIcon();
        DECLARE_MESSAGE_MAP()

    public:
        CMyListCtrlExt m_studentInfList;
        afx_msg void OnBnClickedDelete();
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnBnClickedImport();
        afx_msg void OnBnClickedExport();
        afx_msg void OnBnClickedevaluateaward1();
        afx_msg void OnBnClickedevaluateaward2();
        afx_msg void OnBnClickedDeleteall();
        afx_msg void OnBnClickedCheck();
        CString GetAwardList();
        afx_msg void OnBnClickedExportAward();
};


