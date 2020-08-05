#include "pch.h"
#include "ApplicationExports.h"

ApplicationExports::CEF_ExecJavaScript_ ApplicationExports::CEF_ExecJavaScript;
ApplicationExports::SSO_Login_ ApplicationExports::SSO_Login;

bool ApplicationExports::Loading() {
	CEF_ExecJavaScript =	(CEF_ExecJavaScript_)			GetProcAddress(GetModuleHandle(NULL), "CEF_ExecJavaScript");
	SSO_Login =				(SSO_Login_)					GetProcAddress(GetModuleHandle(NULL), "SSO_Login");
    return true;
}
