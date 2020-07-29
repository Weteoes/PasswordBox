#include "pch.h"
#include "CreateDlg.h"
#include <Weteoes/Dlg/BrowserDlg.h>
#include <resource.h>

void CreateDlgClass::browser(
	std::string url,
	std::string browserKey,
	bool reloadURL,
	std::string dlgTitle,
	int dlgWidth,
	int dlgHeight, 
	bool minimize, 
	int dlgBorderStyle
) {
	// 判断是否有窗口（已经开过一次）
	VariableClass::CefBrowserMapClass cefBrowserMapClass = VariableClass::getCefBrowserMap(browserKey);
	// 如果有就显示，不创建新的窗口
	if (cefBrowserMapClass.dlgHwnd) {
		// 判断是否需要刷新页面
		if (reloadURL)	cefBrowserMapClass.cefBrowser->GetMainFrame()->LoadURL(url);
		VariableClass::appDlgClass.Show(cefBrowserMapClass.dlgHwnd);
		return;
	}
	// 创建一个新的窗口
	BrowserDlg a;
	a.dlgBorderStyle = dlgBorderStyle;
	a.configCEFUrl = url;
	a.dlgWidth = dlgWidth;
	a.dlgHeight = dlgHeight;
	a.browserKey = browserKey;
	a.dlgTitle = dlgTitle;
	if (minimize) {
		// 隐蔽启动
		a.Create(IDD_DIALOG_Browser);
		a.ShowWindow(SW_HIDE);
		a.RunModalLoop();
	}
	else {
		a.DoModal();
	}
}

void CreateDlgClass::init(bool reloadURL) {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl(VariableClass::appConfigClass.DlgInitURL);
	browser(url, init_BrowserKey, reloadURL, "初始化", 800, 480);
}

void CreateDlgClass::login(bool reloadURL) {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl(VariableClass::appConfigClass.DlgLoginURL);
	browser(url, login_BrowserKey, reloadURL, "登录", 350, 188);
}

void CreateDlgClass::login_sso(bool reloadURL) {
	string url = VariableClass::appConfigClass.ServerLoginSSOLoginURL + VariableClass::appConfigClass.ServerLoginSSOSuccessURL;
	browser(url, login_sso_BrowserKey, reloadURL, "统一身份认证", 1000, 400, false, BorderStyle_Thin);
}

void CreateDlgClass::changePassword(bool reloadURL) {
	string url = VariableClass::appCefClass.GetUrl(VariableClass::appConfigClass.DlgChangePasswordURL);
	browser(url, changePassword_BrowserKey, reloadURL, "修改密码", 350, 273);
}

void CreateDlgClass::main(bool reloadURL, bool minimize) {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl(VariableClass::appConfigClass.DlgMainURL);
	browser(url, main_BrowserKey, reloadURL, "Main", 900, 527, minimize);
}