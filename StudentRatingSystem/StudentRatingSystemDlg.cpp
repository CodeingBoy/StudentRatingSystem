
// StudentRatingSystemDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
    public:
        CAboutDlg();

        // 对话框数据
#ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_ABOUTBOX };
#endif

    protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CStudentRatingSystemDlg 对话框



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


// CStudentRatingSystemDlg 消息处理程序

BOOL CStudentRatingSystemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
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

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    m_studentInfList.PrepareList(); // List 初始化

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStudentRatingSystemDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    } else {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
                        _T("逗号分隔符文件(*.csv)|*.csv|文本文件(*.txt)|*.txt||"), NULL, 0, TRUE);
    if (filedlg.DoModal() != IDOK) // 取消了
        return;
    int reply = MessageBox(_T("您导入的文件是否存在标题？\n\n标题是指：您的文件第一行不是具体的信息，而是描述列内容的文字。"),
                           _T("是否存在标题"), MB_ICONQUESTION | MB_YESNOCANCEL);

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
    if ((err = handler.GetError()) != 0) { // 出错处理
        CString errmsg;
        errmsg.Format(_T("打开文件失败！\n返回的错误代码：%d，请搜索\"errno %d\"以获取更详细的信息。"),
                      err, err);
        MessageBox(errmsg, _T("出现错误"), MB_ICONERROR);
        return; // 立刻析构掉
    }

    if (handler.ParseFile(haveHeader, &m_studentInfList)) {
        if (handler.HasDataError())
            MessageBox(_T("程序发现您的文件中缺少了一部分信息，这些信息可能使得程序统计功能无法正常运行，因此已作标红处理。\n"
                          "建议您审阅数据以保证数据的正确性。"), _T("文件缺少信息"), MB_ICONERROR);

        if (handler.HasExtraInf())
            MessageBox(_T("程序发现您的文件中含有额外的信息，这些信息可能已过期，因此已作丢弃处理。\n"
                          "建议您审阅数据以保证数据的正确性。"), _T("文件含有额外的信息"), MB_ICONINFORMATION);

        int parsedLine;
        if ((parsedLine = handler.GetParsedLine()) == 0) {
            MessageBox(_T("您的数据文件为空，因此未导入任何数据"), _T("导入失败"), MB_ICONERROR);
        } else {
            CString str;
            str.Format(_T("已导入 %d 条数据"), handler.GetParsedLine());
            MessageBox(str, _T("导入成功"), MB_ICONINFORMATION);
            m_studentInfList.RefreshAverage();
        }
    }

}


void CStudentRatingSystemDlg::OnBnClickedExport()
{
    CFileDialog filedlg(FALSE, _T("csv"), NULL, OFN_CREATEPROMPT | OFN_PATHMUSTEXIST,
                        _T("逗号分隔符文件(*.csv)|*.csv|文本文件(*.txt)|*.txt||"), NULL, 0, TRUE);
    if (filedlg.DoModal() != IDOK) // 取消了
        return;
    int reply = MessageBox(_T("您希望保存标题吗？\n\n标题是指：您的文件第一行不是具体的信息，而是描述列内容的文字。"),
                           _T("是否保存标题"), MB_ICONQUESTION | MB_YESNOCANCEL);

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
    if ((err = handler.GetError()) != 0) { // 出错处理
        CString errmsg;
        errmsg.Format(_T("打开文件失败！\n返回的错误代码：%d，请搜索\"errno %d\"以获取更详细的信息。"),
                      err, err);
        MessageBox(errmsg, _T("出现错误"), MB_ICONERROR);
        return; // 立刻析构掉
    }
    if (handler.SaveFile(haveHeader, &m_studentInfList)) {
        MessageBox(_T("保存成功！"), _T("成功！"), MB_ICONINFORMATION);
    } else {
        MessageBox(_T("保存失败！"), _T("失败！"), MB_ICONERROR);
    }
}

void CStudentRatingSystemDlg::OnBnClickedevaluateaward1()
{
    if (!m_studentInfList.isDataCorrect())  {
        MessageBox(_T("您的数据不完整，无法进行评定。"), _T("数据不完整"), MB_ICONERROR);
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
        MessageBox(_T("您的数据不完整，无法进行评定。"), _T("数据不完整"), MB_ICONERROR);
        return;
    }

    std::vector<StudentInf> StudentInf_list, rtnlist;
    m_studentInfList.GetVector(&StudentInf_list);
    rtnlist = m_studentInfList.EvaluateAward(&StudentInf_list, false);
    m_studentInfList.SyncToList(&rtnlist);
}


void CStudentRatingSystemDlg::OnBnClickedDeleteall()
{
    if (MessageBox(_T("您确定要清空列表吗？"), _T("确定？"), MB_ICONQUESTION | MB_YESNO)
            == IDYES) {
        m_studentInfList.InitializeList();
        //StudentInf_list.clear();
    }

}

void CStudentRatingSystemDlg::OnBnClickedCheck()
{
    if (m_studentInfList.MarkIncorrectCell()) {
        MessageBox(_T("恭喜，您的数据完整。"), _T("数据完整"), MB_ICONINFORMATION);
    } else {
        MessageBox(_T("您的数据不完整。"), _T("数据不完整"), MB_ICONERROR);
    }
}

void CStudentRatingSystemDlg::OnBnClickedExportAward()
{

    CFileDialog filedlg(FALSE, _T("txt"), NULL, OFN_CREATEPROMPT | OFN_PATHMUSTEXIST ,
                        _T("文本文件(*.txt)|*.txt||"), NULL, 0, TRUE);
    if (filedlg.DoModal() != IDOK) // 取消了
        return;

    CStuFileHandler handler(filedlg.GetPathName(), false);
    int err;
    if ((err = handler.GetError()) != 0) { // 出错处理
        CString errmsg;
        errmsg.Format(_T("打开文件失败！\n返回的错误代码：%d，请搜索\"errno %d\"以获取更详细的信息。"), err, err);
        MessageBox(errmsg, _T("出现错误"), MB_ICONERROR);
        return; // 立刻析构掉

    }

    if (m_studentInfList.SaveAwardList(handler)) {
        MessageBox(_T("保存成功！"), _T("成功！"), MB_ICONINFORMATION);
    } else {
        MessageBox(_T("保存失败"), _T("失败"), MB_ICONERROR);
    }

}
