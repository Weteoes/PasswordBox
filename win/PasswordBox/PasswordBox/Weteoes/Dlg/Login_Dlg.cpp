
// PasswordBoxDlg.cpp: 实现文件
//

#include <pch.h>
#include <framework.h>
#include <PasswordBox.h>
#include "Login_Dlg.h"
#include "afxdialogex.h"
#include <resource.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <Weteoes/Variable.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/More/CEF/Config.h>
#include <Weteoes/More/CEF/Application/Dlg/Login/CEF_Login_App.h>
#include <Weteoes/More/CEF/Application/Dlg/Login/CEF_Login_V8Handler.h>
#include <Weteoes/More/CEF/Application/CEF_Handler.h>


// Login_Dlg 对话框



Login_Dlg::Login_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Login, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void Login_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// 托盘重启
static UINT OnTaskBarRestart_ID = RegisterWindowMessage(TEXT("TaskbarCreated"));
BEGIN_MESSAGE_MAP(Login_Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	// 托盘事件
	ON_COMMAND(ID_MENU_Exit, &Login_Dlg::IconMenu_Exit)
	ON_MESSAGE(WM_IconMsg, &Login_Dlg::OnNotifyMsg)
	ON_REGISTERED_MESSAGE(OnTaskBarRestart_ID, &Login_Dlg::OnTaskBarRestart)
	ON_BN_CLICKED(IDOK, &Login_Dlg::OnBnClickedOk)
	ON_WM_NCHITTEST()
//	ON_WM_ICONERASEBKGND()
END_MESSAGE_MAP()


// Login_Dlg 消息处理程序

BOOL Login_Dlg::OnInitDialog() {
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

void Login_Dlg::OnPaint() {
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
void Login_Dlg::Ready() {
	Ready_Dlg();
	Ready_Icon();
	VariableClass::app_Dll_SWR.Start(0);
	Ready_CEF();
	SRWDll::Set_Variable("LoginIn", "1");
	ConfigDll::Set_Variable("AES_Password", "123456");
}

// 初始化窗口
void Login_Dlg::Ready_Dlg() {
	/* 设置窗口标题(用于Dll获取主窗口句柄) Title */
	//AfxGetMainWnd()->SetWindowText(AppConfigClass::SoftwareName.c_str());

	//设置窗口大小
	int width = 400, height = 300;
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);
	GetDlgItem(IDC_LOGIN_STATIC_CEF)->SetWindowPos(0, 0, 0, width, height, NULL);

	//阴影
	SetClassLong(this->m_hWnd, GCL_STYLE, GetClassLong(this->m_hWnd, GCL_STYLE) | CS_DROPSHADOW);

	//圆角
	CRgn m_rgn; RECT rc;
	//GetWindowRect(&rc); //有边框对话框
	GetClientRect(&rc);//无边框对话框 
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 5, 5); //矩形圆角
	SetWindowRgn(m_rgn, TRUE);

	// 保存窗口句柄
	VariableClass::dlg_HWND = this->m_hWnd;
}

// 初始化CEF
void Login_Dlg::Ready_CEF() {
	string url = VariableClass::appCefClass.GetUrl("/operating/console/getAll");
	CefRefPtr<CEF_Handler> CEF_handler = CEF_Handler::GetInstance();
	GetDlgItem(IDC_LOGIN_STATIC_CEF)->GetClientRect(&CEF_Login_App::CEF_CRect);
	CEF_Login_App::CEF_HWND = GetSafeHwnd();
	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;
	window_info.SetAsChild(CEF_Login_App::CEF_HWND, CEF_Login_App::CEF_CRect);
	CefBrowserHost::CreateBrowser(window_info, CEF_handler, url, browser_settings, NULL, NULL);
}

// 初始化托盘图标
void Login_Dlg::Ready_Icon() {
	VariableClass::appIconClass.Icon_Add(this->m_hWnd, AfxGetInstanceHandle());
}

// 托盘图标事件
LRESULT Login_Dlg::OnNotifyMsg(WPARAM wparam, LPARAM lparam) {
	if (wparam != IDI_ICON1) { return -1; }
	switch (lparam) {
	case WM_LBUTTONDOWN:
		VariableClass::appDlgClass.Show();
		break;
	case WM_RBUTTONDOWN: 
		// 注意：菜单是弹出式菜单，菜单索引项是弹出式菜单，子菜单不是
		CMenu menu;
		menu.LoadMenu(IDR_MENU1);
		CMenu* pPopup = menu.GetSubMenu(0);  // 获取菜单句柄，参数表示菜单位置，索引值
		if (!pPopup) { MessageBox(_T("Icon 获取句柄失败"), _T(""), MB_OK); return 0; }
		SetForegroundWindow();
		POINT pt;
		GetCursorPos(&pt);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this); // 其中可添加TPM_RETURNCMD  | TPM_RIGHTBUTTON 选项，返回值表示选中的菜单ID项
		pPopup->DestroyMenu(); //销毁菜单
		break;
	}
	return 0;
}

// 托盘图标重启事件
LRESULT Login_Dlg::OnTaskBarRestart(WPARAM wParam, LPARAM lParam) {
	Ready_Icon();
	return 0;
}

// 托盘事件-退出
void Login_Dlg::IconMenu_Exit() {
	VariableClass::appDlgClass.Close();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Login_Dlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}


#include <Weteoes/Dlg/Main_Dlg.h>

void Login_Dlg::OnBnClickedOk() {
	// TODO: 在此添加控件通知处理程序代码
	//exit(0);
	Main_Dlg a;
	a.DoModal();
}


// Alt + F4
void Login_Dlg::OnCancel() {
	VariableClass::appDlgClass.Minimize();
	//CDialogEx::OnCancel();
}
