#include "pch.h"
#include "CreateDlg.h"
#include <Weteoes/Dlg/BrowserDlg.h>
#include <resource.h>

void CreateDlgClass::browser(
	std::string url,
	std::string browserKey,
	std::string dlgTitle,
	int dlgWidth, 
	int dlgHeight, 
	bool minimize, 
	int dlgBorderStyle
) {
	// 判断是否有窗口（已经开过一次）
	VariableClass::CefBrowserMapClass cefBrowserMapClass = VariableClass::getCefBrowserMap(browserKey);
	if (cefBrowserMapClass.dlgHwnd) {
		// 如果有就显示，不创建新的窗口
		cefBrowserMapClass.cefBrowser->GetMainFrame()->LoadURL(url);
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

void CreateDlgClass::init() {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl(VariableClass::appConfigClass.DlgInitURL);
	browser(url, "init");
}

void CreateDlgClass::login() {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl(VariableClass::appConfigClass.DlgLoginURL);
	browser(url, "login");
}

void CreateDlgClass::login_sso() {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appConfigClass.ServerLoginSSOLoginURL + VariableClass::appConfigClass.ServerLoginSSOSuccessURL;
	browser(url, "login_sso","统一身份认证", 1000, 400, false, BorderStyle_Thin);
}

void CreateDlgClass::changePassword() {
	string url = VariableClass::appCefClass.GetUrl(VariableClass::appConfigClass.DlgChangePasswordURL);
	browser(url, "changePassword");
}

void CreateDlgClass::main(bool minimize) {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl(VariableClass::appConfigClass.DlgMainURL);
	browser(url, "main", "Main", minimize);
}