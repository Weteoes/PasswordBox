#pragma once
#ifndef ApplicationExports_
#define ApplicationExports_
#include <pch.h>

class ApplicationExports {
private:
	typedef bool(__stdcall* CEF_ExecJavaScript_)(const char* js);				// CEFÖ´ÐÐJS´úÂë
	typedef bool(__stdcall* SSO_Login_)();										// SSOµÇÂ¼

public:
	bool Loading();
	static CEF_ExecJavaScript_ CEF_ExecJavaScript;
	static SSO_Login_ SSO_Login;
};
#endif