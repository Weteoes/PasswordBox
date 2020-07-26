
// PasswordBoxDlg.cpp: 实现文件
//

#include <pch.h>
#include <framework.h>
#include <PasswordBox.h>
#include "BrowserDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <Weteoes/Variable.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/More/CEF/Config.h>
#include <Weteoes/More/CEF/Application/CEF_Handler.h>


// BrowserDlg 对话框

BrowserDlg::BrowserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Browser, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void BrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(BrowserDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// BrowserDlg 消息处理程序

BOOL BrowserDlg::OnInitDialog()
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

void BrowserDlg::OnPaint()
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
void BrowserDlg::Ready() {
	ReadyDlg();
	ReadyVariable();
	ReadyCEF();
}

void BrowserDlg::ReadyVariable() {
	VariableClass::dlg_CEF = dlg_CEF;
	VariableClass::dlg_HWND = dlg_HWND;
}

// 初始化窗口
void BrowserDlg::ReadyDlg() {
	// 初始化变量
	dlg_CEF = IDC_Browser_CEF;
	dlg_HWND = this->m_hWnd;

	// 设置窗口标题(用于Dll获取主窗口句柄) Title
	SetWindowText(dlgTitle.c_str());

	//设置窗口大小
	//int width = 600, height = 400;
	SetWindowPos(NULL, 0, 0, dlgWidth, dlgHeight, SWP_NOMOVE);
	GetDlgItem(dlg_CEF)->SetWindowPos(0, 0, 0, dlgWidth, dlgHeight, NULL);

	if (dlgBorderStyle != BorderStyle_None) SetBorder(dlgBorderStyle);
	// 阴影
	//SetClassLong(dlg_HWND, GCL_STYLE, GetClassLong(dlg_HWND, GCL_STYLE) | CS_DROPSHADOW);
	
}

// 初始化CEF
void BrowserDlg::ReadyCEF() {
	CefRefPtr<CEF_Handler> CEF_handler = CEF_Handler::GetInstance();
	if (CEF_handler == NULL) {
		CEF_handler = new CEF_Handler(false);
	}
	browserListIndex = CEF_handler->GetBrowserListIndex();
	CRect CEF_CRect;
	GetDlgItem(dlg_CEF)->GetClientRect(&CEF_CRect);
	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;
	window_info.SetAsChild(GetSafeHwnd(), CEF_CRect);
	CefBrowserHost::CreateBrowser(window_info, CEF_handler, configCEFUrl, browser_settings, NULL, NULL);
	thread a(&BrowserDlg::ReadyCEFVariable, this); a.detach();
}

void BrowserDlg::ReadyCEFVariable() {
	CefRefPtr<CEF_Handler> CEF_handler = CEF_Handler::GetInstance();
	CefRefPtr<CefBrowser> browser = CEF_handler->GetBrowserbyIndex(browserListIndex);
	if (browser) {
		this->browser = browser;
		VariableClass::setCefBrowserMap(browserKey, this->dlg_HWND, this->browser);
	}
	else {
		Sleep(100);
		ReadyCEFVariable();
	}
}

void BrowserDlg::SetBorder(UINT nBorder) {
	if (BorderStyle_Dialog_Frame == nBorder)
	{
		ModifyStyle(WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS | DS_MODALFRAME,
			WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS | DS_MODALFRAME, NULL);
		ModifyStyleEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, NULL);
	}
	else if (BorderStyle_Thin == nBorder)
	{
		ModifyStyle(WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS | DS_MODALFRAME,
			WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS | DS_MODALFRAME, NULL);
		ModifyStyleEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, NULL);
	}
	else if (BorderStyle_None == nBorder)
	{
		ModifyStyle(WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS | DS_MODALFRAME,
			WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS, NULL);
		ModifyStyleEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, NULL, NULL);
	}
	else if (BorderStyle_Resizing == nBorder)
	{
		ModifyStyle(WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS | DS_MODALFRAME,
			WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_CLIPSIBLINGS | DS_MODALFRAME | WS_THICKFRAME, NULL);
		ModifyStyleEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, NULL);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR BrowserDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

void BrowserDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
	if (nState != 0) {
		ReadyVariable();
	}
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


void BrowserDlg::OnSize(UINT nType, int cx, int cy) {
	CDialogEx::OnSize(nType, cx, cy);
	if (browser) {
		CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
		//因为浏览器对于对话框是子窗口，所以浏览器的左上角坐标是相于父窗口的客户区的左上角而言的
		::MoveWindow(hwnd, 0, 0, cx, cy, TRUE);
	}
}

// Alt + F4
void BrowserDlg::OnCancel() {
	CString a;
	GetWindowText(a);
	if (a == "Close") {
		CDialogEx::OnCancel();
	}
	else {
		// 如果不等于close就不关闭
		VariableClass::appDlgClass.Minimize();
	}
}

BOOL BrowserDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
	return 0;
}