#include "stdafx.h"
#include "MyEdit.h"


CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
}


BOOL CMyEdit::PreTranslateMessage(MSG *pMsg)
{
    if (pMsg->message == WM_KEYDOWN) {
        if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) {
            AfxGetMainWnd()->PostMessage(WM_HIDEEDITOR, NULL, NULL);
            return true;
        }
    }


    return CEdit::PreTranslateMessage(pMsg);
}
