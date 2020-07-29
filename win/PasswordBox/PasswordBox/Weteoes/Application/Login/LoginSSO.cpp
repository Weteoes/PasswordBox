#include "pch.h"
#include "LoginSSO.h"
#include <Weteoes/Application/CEF/AppCookieVisitor.h>

void LoginSSOClass::Loginin(CefRefPtr<CefBrowser> browser) {
	// ��ȡCookie
	CefRefPtr<CefCookieVisitor> visitor(new AppCookieVisitor());
	CefRefPtr<CefCookieManager> cefCookieManager = CefCookieManager::GetGlobalManager(nullptr);
	if (cefCookieManager) {
		cefCookieManager->VisitAllCookies(visitor);
	}
}

void LoginSSOClass::Cookie(std::string key, std::string value) {
	if (key == "JSESSIONID") {
		// ֻ�������ݣ��ж���js����
		ConfigDll::Config_ServerSetw(value.c_str());
		SetLoginSession(value);
		// ���ص�¼����
		VariableClass::CefBrowserMapClass cefBrowserMapClass = VariableClass::getCefBrowserMap(VariableClass::createDlgClass.login_sso_BrowserKey);
		if (cefBrowserMapClass.dlgHwnd) {
			// ���أ��ᷢ�͹ر���Ϣ��
			VariableClass::appDlgClass.Minimize(cefBrowserMapClass.dlgHwnd, true);
		}
	}
}

bool LoginSSOClass::PdLogin() {
	char* result = new char('\0');
	int len = ConfigDll::Config_ServerGetw(result);
	if (len == 0) { return false; }
	std::string wStr(result, len);
	if (wStr.empty()) { return false; }
	SetLoginSession(wStr);
	if (!ServerDll::PdLogin()) {
		// ��¼̬ʧЧ���������
		ConfigDll::Config_ServerSetw("");
		return false;
	}
	// ���±������ã������£�ͨ��js����GetServerConfig���£�
	// GetServerConfig();
	// ���
	VariableClass::isSSOLogin = true;
	SRWDll::Set_Variable("isSSOLogin", "1");
	return true;
}

bool LoginSSOClass::GetServerConfig() {
	return ServerDll::GetConfig();
}

bool LoginSSOClass::SetLoginSession(std::string w) {
	return ServerDll::Set_Variable("w", (char*)w.c_str());
}