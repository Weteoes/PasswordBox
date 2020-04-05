
// PasswordBoxDlg.cpp: 实现文件
//

#include <pch.h>
#include <framework.h>
#include <PasswordBox.h>
#include "W_ICON_Dlg.h"
#include "afxdialogex.h"
#include <resource.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <Weteoes/Dlg/Init_Dlg.h>


// W_ICON_Dlg 对话框



W_ICON_Dlg::W_ICON_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_W_ICON, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void W_ICON_Dlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

// 托盘重启
static UINT OnTaskBarRestart_ID = RegisterWindowMessage(TEXT("TaskbarCreated"));
BEGIN_MESSAGE_MAP(W_ICON_Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	// 托盘事件
	ON_COMMAND(ID_MENU_Exit, &W_ICON_Dlg::IconMenu_Exit)
	ON_MESSAGE(WM_IconMsg, &W_ICON_Dlg::OnNotifyMsg)
	ON_REGISTERED_MESSAGE(OnTaskBarRestart_ID, &W_ICON_Dlg::OnTaskBarRestart)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// W_ICON_Dlg 消息处理程序

BOOL W_ICON_Dlg::OnInitDialog() {
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

void W_ICON_Dlg::OnPaint() {
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
void W_ICON_Dlg::Ready() {
	Ready_Variable();
	Ready_Icon();
	CreateDlg();
}

bool W_ICON_Dlg::CreateDlg() {
	if (ConfigDll::Config_Exsits()) {
		// 配置文件存在
		VariableClass::createDlgClass.login();
	}
	else {
		VariableClass::createDlgClass.init();
	}
	return true;
}

void W_ICON_Dlg::Ready_Variable() {
	dlg_CEF = IDC_Init_CEF;
	dlg_HWND = this->m_hWnd;
}

// 初始化托盘图标
void W_ICON_Dlg::Ready_Icon() {
	VariableClass::appIconClass.Icon_Add(this->m_hWnd, AfxGetInstanceHandle());
}

// 托盘图标事件
LRESULT W_ICON_Dlg::OnNotifyMsg(WPARAM wparam, LPARAM lparam) {
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
LRESULT W_ICON_Dlg::OnTaskBarRestart(WPARAM wParam, LPARAM lParam) {
	Ready_Icon();
	return 0;
}

// 托盘事件-退出
void W_ICON_Dlg::IconMenu_Exit() {
	VariableClass::appDlgClass.Close();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR W_ICON_Dlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

// Alt + F4
void W_ICON_Dlg::OnCancel() {
	VariableClass::appDlgClass.Minimize();
	//CDialogEx::OnCancel();
}