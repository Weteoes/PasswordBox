#include "pch.h"
#include "LoginSSO.h"
#include <Weteoes/Application/CEF/AppCookieVisitor.h>

void LoginSSOClass::Loginin(CefRefPtr<CefBrowser> browser) {
	// 获取Cookie
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
		// 只保存数据，判断由js调起
		ConfigDll::Config_ServerSetw(value.c_str());
		SetLoginSession(value);
		// 隐藏登录窗口
		VariableClass::CefBrowserMapClass cefBrowserMapClass = VariableClass::getCefBrowserMap(VariableClass::createDlgClass.login_sso_BrowserKey);
		if (cefBrowserMapClass.dlgHwnd) {
			// 隐藏（会发送关闭消息）
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
		// 登录态失效，清空配置
		// ConfigDll::Config_ServerSetw("");
		LogDll::Info("LoginSSOClass::PdLogin Session Error");
		return false;
	}

	LogDll::Info("LoginSSOClass::PdLogin Session Success");
	// 更新本地配置（不更新，通过js调用GetServerConfig更新）
	// GetServerConfig();
	// 标记
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
