#include "pch.h"
#include "LoginSSO.h"
#include <Weteoes/Application/CEF/AppCookieVisitor.h>

void LoginSSOClass::Loginin(CefRefPtr<CefBrowser> browser) {
	CefRefPtr<CefCookieVisitor> visitor(new AppCookieVisitor());
	CefRefPtr<CefCookieManager> cefCookieManager = CefCookieManager::GetGlobalManager(nullptr);
	if (cefCookieManager) {
		cefCookieManager->VisitAllCookies(visitor);
	}
}

void LoginSSOClass::Cookie(std::string key, std::string value) {
	if (key == "JSESSIONID") {
		ConfigDll::Config_ServerSetw(value.c_str());
		SetLoginSession(value);
		if (PdLogin()) {
			std::thread(&LoginSSOClass::ShowLoginDlg, this).detach();
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
		// 登录态失效，清空配置
		ConfigDll::Config_ServerSetw("");
		return false;
	}
	// 更新本地配置
	ServerDll::GetConfig();
	// 标记
	VariableClass::isSSOLogin = true;
	SRWDll::Set_Variable("isSSOLogin", "1");
	return true;
}

bool LoginSSOClass::SetLoginSession(std::string w) {
	return ServerDll::Set_Variable("w", (char*)w.c_str());
}

void LoginSSOClass::ShowLoginDlg() {
	VariableClass::createDlgClass.login();
}
