#include "pch.h"
#include "AppDlgCallBack.h"

void AppDlgCallBackClass::OnCancel(std::string browserKey) {
	if (browserKey == VariableClass::createDlgClass.login_sso_BrowserKey) {
		// ͳһ�����֤��¼
		VariableClass::CefBrowserMapClass cefBrowserMapClass = VariableClass::getCefBrowserMap(VariableClass::createDlgClass.init_BrowserKey);
		if (!cefBrowserMapClass.dlgHwnd) { 
			return; 
		}
		// ��������ڳ�ʼ�����ڣ���ȡ����ɹ���
		std::string js = VariableClass::appCefBasicClass.GetJavaScriptNamebyCallBack() + ".init.nextStepActive(false)";
		VariableClass::appCefBasicClass.ExecJavaScript(cefBrowserMapClass.cefBrowser, js);
	}
}
