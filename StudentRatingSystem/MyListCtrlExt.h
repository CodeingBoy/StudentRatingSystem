#pragma once
#include "ListCtrlExt.h"
#include "StudentInf.h"
#include "MyEdit.h"

#include <vector>
#include <map>
#include <algorithm>

#define IDC_EDIT 1007

#define COLOR_ERR			RGB(255, 0, 0)
#define COLOR_YES			RGB(128, 255, 0)
#define COLOR_NO			RGB(255, 128, 128)
#define COLOR_NOT_ENOUGH	RGB(255, 128, 0)

typedef std::multimap<CString, StudentInf *> ClassMap;

class CStuFileHandler;

class CMyListCtrlExt :
    public CListCtrlExt
{
    protected:
        DECLARE_MESSAGE_MAP()
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
        afx_msg BOOL OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
        afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);
    private:
        CMyEdit m_Edit;
        bool isCorrect = true;
        double total[4] = { 0.0 };
        int modifingItem = -1, modifingSubItem = -1;
    public:
        CMyListCtrlExt();
        ~CMyListCtrlExt();

        void AddNewLine(StudentInf &inf);
        bool isDataCorrect();
        bool isDataCorrect(int row, int column);
        bool isDataCorrect(std::vector<StudentInf> *plist);
        bool MarkIncorrectCell();
        void RefreshAverage();
        void CalculateAverage(double average[]);
        void MarkNotEnoughCell(bool isMark);
        void MarkNotEnoughCell(int nRow, int nCol);
        std::vector<StudentInf> EvaluateAward(std::vector<StudentInf> *plist, bool isAwardOne);
        void EvaluateAward1(std::vector<StudentInf> *plist);
        void EvaluateAward2(std::vector<StudentInf> *plist);
        void GetVector(std::vector<StudentInf> *plist);
        StudentInf GetData(int row);
        void SyncToList(std::vector<StudentInf> *plist);
        void PrepareList();
        void InitializeList();
        BOOL DisplayEditor(int nItem, int nSubItem);
        void HideEditor(BOOL bUpdate = TRUE);
        bool SaveAwardList(CStuFileHandler &handler);
        ClassMap *getClassMap(std::vector<StudentInf> &container);
        bool HasData();
};

