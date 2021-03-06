#include <pch.h>
#include "CEF_Main_V8Handler.h"

bool CEF_Main_V8Handler::Execute(
	const CefString& name, 
	CefRefPtr<CefDictionaryValue> arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception
	) {
	if (name == "Signout") { 
		// �˳���¼
		SRWDll::Set_Variable("LoginIn", "");
		return VariableClass::cef_Init_V8Handler.Execute("ShowLoginDlg", arguments, retval, exception);
		return true;
	}
	else if (name == "ShowChangePasswordDlg") {
		std::thread a(&CEF_Main_V8Handler::ShowChangePasswordDlg, this); a.detach(); //Create Thread
		return true;
	}
	else if (name == "PdSSOLogin") {
		VariableClass::cef_Init_V8Handler.Execute("PdSSOLogin", arguments, retval, exception);
		return true;
	}
	else if (name == "SSOSumbitServerConfig") {
		VariableClass::cef_Init_V8Handler.Execute("SSOSumbitServerConfig", arguments, retval, exception);
		return true;
	}
	return false;
}

void CEF_Main_V8Handler::ShowChangePasswordDlg() {
	VariableClass::createDlgClass.changePassword();
}