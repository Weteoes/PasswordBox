#include <pch.h>
#include "CEF_Main_V8Handler.h"

bool CEF_Main_V8Handler::Execute(
	const CefString& name, 
	CefRefPtr<CefDictionaryValue> arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception
	) {
	if (name == "Signout") { 
		// ÍË³öµÇÂ¼
		SRWDll::Set_Variable("LoginIn", "");
		std::thread a(&CEF_Main_V8Handler::ShowLoginDlg, this); a.detach(); //Create Thread
		return true;
	}
	else if (name == "ShowChangePasswordDlg") {
		std::thread a(&CEF_Main_V8Handler::ShowChangePasswordDlg, this); a.detach(); //Create Thread
		return true;
	}
	return false;
}

void CEF_Main_V8Handler::ShowLoginDlg() {
	VariableClass::createDlgClass.login();
}

void CEF_Main_V8Handler::ShowChangePasswordDlg() {
	VariableClass::createDlgClass.changePassword();
}