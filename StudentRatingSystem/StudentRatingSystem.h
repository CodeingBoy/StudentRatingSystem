
// StudentRatingSystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CStudentRatingSystemApp:
// �йش����ʵ�֣������ StudentRatingSystem.cpp
//

class CStudentRatingSystemApp : public CWinApp
{
    public:
        CStudentRatingSystemApp();

// ��д
    public:
        virtual BOOL InitInstance();

// ʵ��

        DECLARE_MESSAGE_MAP()
};

extern CStudentRatingSystemApp theApp;