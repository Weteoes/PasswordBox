#include <pch.h>
#include "CEF_ChangePassword_V8Handler.h"

bool CEF_ChangePassword_V8Handler::Execute(
	const CefString& name, 
	CefRefPtr<CefDictionaryValue> arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception
	) {
	if (name == "LoginPass") {
		return VariableClass::cef_Init_V8Handler.Execute("AesInit", arguments, retval, exception);
	}
	else if (name == "ResetAESPassword") {
		string oldPass = arguments->GetString("oldPass");
		string newPass = arguments->GetString("newPass");
		bool result = ConfigDll::Config_ResetAESPassword((char*)oldPass.c_str(), (char*)newPass.c_str());
		if (result && VariableClass::isSSOLogin) {
			// �޸ĳɹ�,������ͳһ�����֤��¼
			ConfigDll::Server_SumbitConfig();
		}
		retval = CefV8Value::CreateBool(result);
		return true;
	}
	return false;
}