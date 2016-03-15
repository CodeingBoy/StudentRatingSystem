
// StudentRatingSystemDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "MyListCtrlExt.h"
#include "StudentInf.h"

#include "afxwin.h"



// CStudentRatingSystemDlg �Ի���
class CStudentRatingSystemDlg : public CDialogEx
{
// ����
    public:
        CStudentRatingSystemDlg(CWnd* pParent = NULL);  // ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_STUDENTRATING_MAINDIALOG };
#endif

    protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


// ʵ��
    protected:
        HICON m_hIcon;

        // ���ɵ���Ϣӳ�亯��
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


