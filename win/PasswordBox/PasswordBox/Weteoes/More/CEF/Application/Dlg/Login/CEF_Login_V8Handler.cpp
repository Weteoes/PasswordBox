#include <pch.h>
#include "CEF_Login_V8Handler.h"

bool CEF_Login_V8Handler::Execute(
	const CefString& name, 
	CefRefPtr<CefDictionaryValue> arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception
	) {
	if (name == "LoginPass") {
		return VariableClass::cef_Init_V8Handler.Execute("AesInit", arguments, retval, exception);
	}
	if (name == "ShowMainDlg") {
		return VariableClass::cef_Init_V8Handler.Execute("ShowMainDlg", arguments, retval, exception);
	}
	return false;
}
