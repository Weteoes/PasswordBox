#pragma once
#include <pch.h>

class ApplicationExports {
private:
	typedef bool(__stdcall* CEF_ExecJavaScript_)(const char* js);				// CEFִ��JS����
	typedef bool(__stdcall* SSO_Login_)();										// SSO��¼

public:
	static bool Ready();
	static CEF_ExecJavaScript_ CEF_ExecJavaScript;
	static SSO_Login_ SSO_Login;
};