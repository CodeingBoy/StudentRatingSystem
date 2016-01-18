
// StudentRatingSystemDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ListCtrlExt.h"

// CStudentRatingSystemDlg �Ի���
class CStudentRatingSystemDlg : public CDialogEx
{
// ����
public:
	CStudentRatingSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTRATING_MAINDIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
