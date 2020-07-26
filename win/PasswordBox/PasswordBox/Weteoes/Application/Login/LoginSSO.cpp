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
		ServerDll::Set_Variable("w", (char*)value.c_str());
	}
}
