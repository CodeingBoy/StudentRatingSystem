
// StudentRatingSystemDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "MyListCtrlExt.h"
#include "StudentInf.h"

#include <list>
#include <algorithm>

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
	void PrepareList();
	void InitializeList();
	void AddNewLine(StudentInf & inf);
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
private:
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedImport();
	afx_msg void OnBnClickedExport();
	std::list<StudentInf> StudentInf_list;
	afx_msg void OnLvnItemchangedStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitemStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnInsertitemStuinflist(NMHDR *pNMHDR, LRESULT *pResult);
};
