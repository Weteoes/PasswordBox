#include "pch.h"
#include "AppDlgCallBack.h"

void AppDlgCallBackClass::OnCancel(std::string browserKey) {
	if (browserKey == VariableClass::createDlgClass.login_sso_BrowserKey) {
		// 统一身份认证登录
		VariableClass::CefBrowserMapClass cefBrowserMapClass = VariableClass::getCefBrowserMap(VariableClass::createDlgClass.init_BrowserKey);
		if (!cefBrowserMapClass.dlgHwnd) { 
			return; 
		}
		// 如果是正在初始化窗口（获取句柄成功）
		std::string js = VariableClass::appCefBasicClass.GetJavaScriptNamebyCallBack() + ".init.nextStepActive(false)";
		VariableClass::appCefBasicClass.ExecJavaScript(cefBrowserMapClass.cefBrowser, js);
	}
}
