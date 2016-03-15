
// StudentRatingSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentRatingSystem.h"
#include "StudentRatingSystemDlg.h"
#include "afxdialogex.h"
#include "StuFileHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_EDIT 1007

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
    public:
        CAboutDlg();

        // �Ի�������
#ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_ABOUTBOX };
#endif

    protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
    protected:
        DECLARE_MESSAGE_MAP()
    public:
//  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//  ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CStudentRatingSystemDlg �Ի���



CStudentRatingSystemDlg::CStudentRatingSystemDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_STUDENTRATINGSYSTEM_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentRatingSystemDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STUINFLIST, m_studentInfList);
}

BEGIN_MESSAGE_MAP(CStudentRatingSystemDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_DELETE, &CStudentRatingSystemDlg::OnBnClickedDelete)
    ON_WM_CREATE()
    ON_BN_CLICKED(IDC_IMPORT, &CStudentRatingSystemDlg::OnBnClickedImport)
    ON_BN_CLICKED(IDC_EXPORT, &CStudentRatingSystemDlg::OnBnClickedExport)
    ON_BN_CLICKED(IDC_evaluateAward1, &CStudentRatingSystemDlg::OnBnClickedevaluateaward1)
    ON_BN_CLICKED(IDC_evaluateAward2, &CStudentRatingSystemDlg::OnBnClickedevaluateaward2)
    ON_BN_CLICKED(IDC_DELETEALL, &CStudentRatingSystemDlg::OnBnClickedDeleteall)
    ON_BN_CLICKED(IDC_CHECK, &CStudentRatingSystemDlg::OnBnClickedCheck)
    ON_BN_CLICKED(IDC_EXPORT_AWARD, &CStudentRatingSystemDlg::OnBnClickedExportAward)
END_MESSAGE_MAP()


// CStudentRatingSystemDlg ��Ϣ�������

BOOL CStudentRatingSystemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // ��������...���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL) {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);         // ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);        // ����Сͼ��

    m_studentInfList.PrepareList(); // List ��ʼ��

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CStudentRatingSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStudentRatingSystemDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    } else {
        CDialogEx::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CStudentRatingSystemDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CStudentRatingSystemDlg::OnBnClickedDelete()
{
    int deletingIndex = m_studentInfList.GetSelectionMark();
    if (deletingIndex <= m_studentInfList.GetItemCount() - 3) {

        m_studentInfList.DeleteSelectedItems();
    }

}


int CStudentRatingSystemDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialogEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}



void CStudentRatingSystemDlg::OnBnClickedImport()
{
    CFileDialog filedlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT,
                        _T("���ŷָ����ļ�(*.csv)|*.csv|�ı��ļ�(*.txt)|*.txt||"), NULL, 0, TRUE);
    if (filedlg.DoModal() != IDOK) // ȡ����
        return;
    int reply = MessageBox(_T("��������ļ��Ƿ���ڱ��⣿\n\n������ָ�������ļ���һ�в��Ǿ������Ϣ���������������ݵ����֡�"),
                           _T("�Ƿ���ڱ���"), MB_ICONQUESTION | MB_YESNOCANCEL);

    bool haveHeader;
    switch (reply)  {
    case IDYES:
        haveHeader = true;
        break;
    case IDNO:
        haveHeader = false;
        break;
    default:
        return;
    }

    CStuFileHandler handler(filedlg.GetPathName());
    int err;
    if ((err = handler.GetError()) != 0) { // ������
        CString errmsg;
        errmsg.Format(_T("���ļ�ʧ�ܣ�\n���صĴ�����룺%d��������\"errno %d\"�Ի�ȡ����ϸ����Ϣ��"),
                      err, err);
        MessageBox(errmsg, _T("���ִ���"), MB_ICONERROR);
        return; // ����������
    }

    if (handler.ParseFile(haveHeader, &m_studentInfList)) {
        if (handler.HasDataError())
            MessageBox(_T("�����������ļ���ȱ����һ������Ϣ����Щ��Ϣ����ʹ�ó���ͳ�ƹ����޷��������У����������촦��\n"
                          "���������������Ա�֤���ݵ���ȷ�ԡ�"), _T("�ļ�ȱ����Ϣ"), MB_ICONERROR);

        if (handler.HasExtraInf())
            MessageBox(_T("�����������ļ��к��ж������Ϣ����Щ��Ϣ�����ѹ��ڣ����������������\n"
                          "���������������Ա�֤���ݵ���ȷ�ԡ�"), _T("�ļ����ж������Ϣ"), MB_ICONINFORMATION);

        int parsedLine;
        if ((parsedLine = handler.GetParsedLine()) == 0) {
            MessageBox(_T("���������ļ�Ϊ�գ����δ�����κ�����"), _T("����ʧ��"), MB_ICONERROR);
        } else {
            CString str;
            str.Format(_T("�ѵ��� %d ������"), handler.GetParsedLine());
            MessageBox(str, _T("����ɹ�"), MB_ICONINFORMATION);
            m_studentInfList.RefreshAverage();
        }
    }

}


void CStudentRatingSystemDlg::OnBnClickedExport()
{
    CFileDialog filedlg(FALSE, _T("csv"), NULL, OFN_CREATEPROMPT | OFN_PATHMUSTEXIST,
                        _T("���ŷָ����ļ�(*.csv)|*.csv|�ı��ļ�(*.txt)|*.txt||"), NULL, 0, TRUE);
    if (filedlg.DoModal() != IDOK) // ȡ����
        return;
    int reply = MessageBox(_T("��ϣ�����������\n\n������ָ�������ļ���һ�в��Ǿ������Ϣ���������������ݵ����֡�"),
                           _T("�Ƿ񱣴����"), MB_ICONQUESTION | MB_YESNOCANCEL);

    bool haveHeader;
    switch (reply) {
    case IDYES:
        haveHeader = true;
        break;
    case IDNO:
        haveHeader = false;
        break;
    default:
        return;
    }

    CStuFileHandler handler(filedlg.GetPathName(), false);
    int err;
    if ((err = handler.GetError()) != 0) { // ������
        CString errmsg;
        errmsg.Format(_T("���ļ�ʧ�ܣ�\n���صĴ�����룺%d��������\"errno %d\"�Ի�ȡ����ϸ����Ϣ��"),
                      err, err);
        MessageBox(errmsg, _T("���ִ���"), MB_ICONERROR);
        return; // ����������
    }
    if (handler.SaveFile(haveHeader, &m_studentInfList)) {
        MessageBox(_T("����ɹ���"), _T("�ɹ���"), MB_ICONINFORMATION);
    } else {
        MessageBox(_T("����ʧ�ܣ�"), _T("ʧ�ܣ�"), MB_ICONERROR);
    }
}

void CStudentRatingSystemDlg::OnBnClickedevaluateaward1()
{
    if (!m_studentInfList.isDataCorrect())  {
        MessageBox(_T("�������ݲ��������޷�����������"), _T("���ݲ�����"), MB_ICONERROR);
        return;
    }

    std::vector<StudentInf> StudentInf_list, rtnlist;
    m_studentInfList.GetVector(&StudentInf_list);
    rtnlist = m_studentInfList.EvaluateAward(&StudentInf_list, true);
    m_studentInfList.SyncToList(&rtnlist);
}

void CStudentRatingSystemDlg::OnBnClickedevaluateaward2()
{
    if (!m_studentInfList.isDataCorrect()) {
        MessageBox(_T("�������ݲ��������޷�����������"), _T("���ݲ�����"), MB_ICONERROR);
        return;
    }

    std::vector<StudentInf> StudentInf_list, rtnlist;
    m_studentInfList.GetVector(&StudentInf_list);
    rtnlist = m_studentInfList.EvaluateAward(&StudentInf_list, false);
    m_studentInfList.SyncToList(&rtnlist);
}


void CStudentRatingSystemDlg::OnBnClickedDeleteall()
{
    if (MessageBox(_T("��ȷ��Ҫ����б���"), _T("ȷ����"), MB_ICONQUESTION | MB_YESNO)
            == IDYES) {
        m_studentInfList.InitializeList();
        //StudentInf_list.clear();
    }

}

void CStudentRatingSystemDlg::OnBnClickedCheck()
{
    if (m_studentInfList.MarkIncorrectCell()) {
        MessageBox(_T("��ϲ����������������"), _T("��������"), MB_ICONINFORMATION);
    } else {
        MessageBox(_T("�������ݲ�������"), _T("���ݲ�����"), MB_ICONERROR);
    }
}

void CStudentRatingSystemDlg::OnBnClickedExportAward()
{

    CFileDialog filedlg(FALSE, _T("txt"), NULL, OFN_CREATEPROMPT | OFN_PATHMUSTEXIST ,
                        _T("�ı��ļ�(*.txt)|*.txt||"), NULL, 0, TRUE);
    if (filedlg.DoModal() != IDOK) // ȡ����
        return;

    CStuFileHandler handler(filedlg.GetPathName(), false);
    int err;
    if ((err = handler.GetError()) != 0) { // ������
        CString errmsg;
        errmsg.Format(_T("���ļ�ʧ�ܣ�\n���صĴ�����룺%d��������\"errno %d\"�Ի�ȡ����ϸ����Ϣ��"), err, err);
        MessageBox(errmsg, _T("���ִ���"), MB_ICONERROR);
        return; // ����������

    }

    if (m_studentInfList.SaveAwardList(handler)) {
        MessageBox(_T("����ɹ���"), _T("�ɹ���"), MB_ICONINFORMATION);
    } else {
        MessageBox(_T("����ʧ��"), _T("ʧ��"), MB_ICONERROR);
    }

}
