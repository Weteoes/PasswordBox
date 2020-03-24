
// PasswordBoxDlg.cpp: 实现文件
//

#include <pch.h>
#include <framework.h>
#include <PasswordBox.h>
#include "PasswordBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <Weteoes\Application\CEF\AppCef.h>
#include <Weteoes\More\CEF\Config.h>
#include <Weteoes\More\CEF\Application\simple_app.h>


// CPasswordBoxDlg 对话框



CPasswordBoxDlg::CPasswordBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PASSWORDBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPasswordBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPasswordBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CPasswordBoxDlg 消息处理程序

BOOL CPasswordBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Ready();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPasswordBoxDlg::OnPaint()
{
	if (IsIconic())
	{
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
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 初始化
void CPasswordBoxDlg::Ready() {
	Ready_Dlg();
	Ready_CEF();
}

// 初始化窗口
void CPasswordBoxDlg::Ready_Dlg() {
	/* 设置窗口标题(用于Dll获取主窗口句柄) Title */
	//AfxGetMainWnd()->SetWindowText(AppConfigClass::SoftwareName.c_str());

	//设置窗口大小
	int width = 400, height = 300;
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);
	GetDlgItem(IDC_CEF)->SetWindowPos(0, 0, 0, width, height, NULL);

	//阴影
	SetClassLong(this->m_hWnd, GCL_STYLE, GetClassLong(this->m_hWnd, GCL_STYLE) | CS_DROPSHADOW);

	//圆角
	CRgn m_rgn; RECT rc;
	//GetWindowRect(&rc); //有边框对话框
	GetClientRect(&rc);//无边框对话框 
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 5, 5); //矩形圆角
	SetWindowRgn(m_rgn, TRUE);
}

// 初始化CEF
void CPasswordBoxDlg::Ready_CEF()
{
	AppCefClass::Url = AppCefClass().GetUrl(Url_Login);
	CefMainArgs mainArgs(AfxGetInstanceHandle());
	CefRefPtr<SimpleApp> app(new SimpleApp);
	CefExecuteProcess(mainArgs, app.get(), NULL);

	CefSettings settings = AppCefClass().GetSetting();
	GetDlgItem(IDC_CEF)->GetClientRect(&SimpleApp::CEF_CRect);
	SimpleApp::CEF_HWND = GetSafeHwnd();
	CefInitialize(mainArgs, settings, app.get(), NULL);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPasswordBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

