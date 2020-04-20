#include "pch.h"
#include "CreateDlg.h"
#include <Weteoes/Dlg/BrowserDlg.h>
#include <resource.h>

void CreateDlgClass::browser(string url, bool minimize) {
	BrowserDlg a;
	a.configCEFUrl = url;
	if (minimize) {
		// Òþ±ÎÆô¶¯
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
	string url = VariableClass::appCefClass.GetUrl("/passwordBox/ui/1/init");
	browser(url);
}

void CreateDlgClass::login() {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl("/passwordBox/ui/1/login");
	browser(url);
}

void CreateDlgClass::changePassword() {
	string url = VariableClass::appCefClass.GetUrl("/passwordBox/ui/1/changePassword");
	browser(url);
}

void CreateDlgClass::main(bool minimize) {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl("/passwordBox/ui/2/main");
	browser(url, minimize);
}