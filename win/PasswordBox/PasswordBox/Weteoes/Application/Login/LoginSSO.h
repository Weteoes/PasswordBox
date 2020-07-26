#pragma once
#ifndef LoginSSOClass_
#define LoginSSOClass_
class LoginSSOClass {
public:
	void Loginin(CefRefPtr<CefBrowser> browser);
	void Cookie(std::string key, std::string value);
};
#endif