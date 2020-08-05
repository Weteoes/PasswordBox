#pragma once
#include <pch.h>

extern "C" _declspec(dllexport) bool CEF_ExecJavaScript(const char* js) {
	if (VariableClass::dlg_CEF == NULL) { return false; }
	VariableClass::appCefBasicClass.ExecJavaScript(VariableClass::dlg_CEF, js);
	return true;
}

// SSOµÇÂ¼´°¿Ú
extern "C" _declspec(dllexport) bool SSO_Login() {
	VariableClass::cef_Init_V8Handler.Execute("ShowLogin_SSODlg");
	return true;
}