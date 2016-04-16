#pragma once
#include "afxwin.h"

#define WM_HIDEEDITOR WM_USER + 300

class CMyEdit :
    public CEdit
{
    public:
        CMyEdit();
        ~CMyEdit();
        virtual BOOL PreTranslateMessage(MSG *pMsg);
};

