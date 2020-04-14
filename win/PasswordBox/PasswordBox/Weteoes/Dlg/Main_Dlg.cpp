
// PasswordBoxDlg.cpp: 实现文件
//

#include <pch.h>
#include <framework.h>
#include <PasswordBox.h>
#include "Main_Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <Weteoes/Variable.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/More/CEF/Config.h>
#include <Weteoes/More/CEF/Application/Dlg/Main/CEF_Main_App.h>
#include <Weteoes/More\CEF/Application/CEF_Handler.h>


// Main_Dlg 对话框

HWND Main_Dlg::dlg_HWND;						// 窗口句柄
int Main_Dlg::dlg_CEF;							// CEF句柄ID
int Main_Dlg::browserListIndex;					// 在CEF_Handler中的浏览器ID
CefRefPtr<CefBrowser> Main_Dlg::browser;		// 浏览器句柄

Main_Dlg::Main_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Main, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void Main_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Main_Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// Main_Dlg 消息处理程序

BOOL Main_Dlg::OnInitDialog()
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

void Main_Dlg::OnPaint()
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
void Main_Dlg::Ready() {
	ReadyDlg();
	ReadyVariable();
	ReadyCEF();
}

void Main_Dlg::ReadyVariable() {
	VariableClass::dlg_CEF = dlg_CEF;
	VariableClass::dlg_HWND = dlg_HWND;
}

// 初始化窗口
void Main_Dlg::ReadyDlg() {
	// 初始化变量
	dlg_CEF = IDC_MAIN_CEF;
	dlg_HWND = this->m_hWnd;

	// 设置窗口标题(用于Dll获取主窗口句柄) Title
	SetWindowText("Main");

	//设置窗口大小
	int width = 800, height = 500;
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);
	GetDlgItem(dlg_CEF)->SetWindowPos(0, 0, 0, width, height, NULL);

	//阴影
	SetClassLong(dlg_HWND, GCL_STYLE, GetClassLong(dlg_HWND, GCL_STYLE) | CS_DROPSHADOW);
}

// 初始化CEF
void Main_Dlg::ReadyCEF() {
	string url = AppCefClass().GetUrl("/passwordBox/ui/2/main");
	CefRefPtr<CEF_Handler> CEF_handler = CEF_Handler::GetInstance();
	browserListIndex = CEF_handler->GetBrowserListIndex();
	GetDlgItem(dlg_CEF)->GetClientRect(&CEF_Main_App::CEF_CRect);
	CEF_Main_App::CEF_HWND = GetSafeHwnd();
	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;
	window_info.SetAsChild(CEF_Main_App::CEF_HWND, CEF_Main_App::CEF_CRect);
	CefBrowserHost::CreateBrowser(window_info, CEF_handler, url, browser_settings, NULL, NULL);
	thread a(&Main_Dlg::ReadyCEFVariable, this); a.detach();
}

void Main_Dlg::ReadyCEFVariable() {
	CefRefPtr<CEF_Handler> CEF_handler = CEF_Handler::GetInstance();
	CefRefPtr<CefBrowser> browser = CEF_handler->GetBrowserbyIndex(browserListIndex);
	if (browser) {
		this->browser = browser;
	}
	else {
		Sleep(100);
		ReadyCEFVariable();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Main_Dlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

void Main_Dlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
	ReadyVariable();
	if (browser) {
		string a = VariableClass::appCefBasicClass.GetJavaScriptNamebyDlg("OnActivate");
		int len = (int)a.length() + 1;
		char* b = new char[len];
		sprintf_s(b, len, a.c_str(), nState);
		VariableClass::appCefBasicClass.ExecJavaScript(browser, b);
		delete[] b;
	}
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}


void Main_Dlg::OnSize(UINT nType, int cx, int cy) {
	CDialogEx::OnSize(nType, cx, cy);
	if (browser) {
		CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
		//因为浏览器对于对话框是子窗口，所以浏览器的左上角坐标是相于父窗口的客户区的左上角而言的
		::MoveWindow(hwnd, 0, 0, cx, cy, TRUE);
	}
}

// Alt + F4
void Main_Dlg::OnCancel() {
	VariableClass::appDlgClass.Minimize();
}


BOOL Main_Dlg::OnHelpInfo(HELPINFO* pHelpInfo) {
	return 0;
}
