#include "pch.h"
#include "LoginSSO.h"
#include <Weteoes/Application/CEF/AppCookieVisitor.h>

void LoginSSOClass::Loginin(CefRefPtr<CefBrowser> browser) {
	// ��ȡCookie
	LogDll::Info("LoginSSOClass::Loginin LoginSSO Loginin");
	CefRefPtr<CefCookieVisitor> visitor(new AppCookieVisitor());
	CefRefPtr<CefCookieManager> cefCookieManager = CefCookieManager::GetGlobalManager(nullptr);
	if (cefCookieManager) {
		cefCookieManager->VisitAllCookies(visitor);
	}
}

void LoginSSOClass::Cookie(std::string key, std::string value) {
	if (key == "w") {
		LogDll::Info("LoginSSOClass::Cookie LoginSSO Loginin Session Found");
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
	LogDll::Info("LoginSSOClass::PdLogin Detect Session");

	char* result = new char('\0');
	int len = ConfigDll::Config_ServerGetw(result);
	if (len == 0) { return false; }
	std::string wStr(result, len);
	if (wStr.empty()) { return false; }
	SetLoginSession(wStr);
	if (!ConfigDll::Server_PdLogin()) {
		// ��¼̬ʧЧ���������
		// ConfigDll::Config_ServerSetw("");
		LogDll::Info("LoginSSOClass::PdLogin Session Error");
		return false;
	}

	LogDll::Info("LoginSSOClass::PdLogin Session Success");
	// ���±������ã������£�ͨ��js����GetServerConfig���£�
	// GetServerConfig();
	// ���
	VariableClass::isSSOLogin = true;
	SRWDll::Set_Variable("isSSOLogin", "1");
	return true;
}

bool LoginSSOClass::GetServerConfig() {
	return ConfigDll::Server_GetConfig();
}

bool LoginSSOClass::SumbitServerConfig() {
	return ConfigDll::Server_SumbitConfig();
}

bool LoginSSOClass::SetLoginSession(std::string w) {
	return ConfigDll::Server_Set_Variable("w", (char*)w.c_str());
}
