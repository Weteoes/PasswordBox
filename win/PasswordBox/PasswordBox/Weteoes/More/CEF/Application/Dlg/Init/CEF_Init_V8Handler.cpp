#include <pch.h>
#include "CEF_Init_V8Handler.h"

bool CEF_Init_V8Handler::Execute(
	const CefString& name,                        // JavaScript���õ�C++��������
	CefRefPtr<CefDictionaryValue> arguments,      // JavaScript���ݵĲ���
	CefRefPtr<CefV8Value>& retval,                // ��Ҫ���ظ�JavaScript��ֵ���ø��������
	CefString& exception)                         // ֪ͨ�쳣��Ϣ��JavaScript	
{
	if (name == "AesInit") {
		// �ж�����ͳ�ʼ������
		string pass = arguments->GetString("pass");
		bool result = ConfigDll::Config_SetAESPassword((char*)pass.c_str());
		if (result) {
			// ������ȷ
			SRWDll::Set_Variable("LoginIn", "1");
		}
		retval = CefV8Value::CreateBool(result);
		return true;
	}
	else if (name == "ShowMainDlg") {
		std::thread a(&CEF_Init_V8Handler::ShowMainDlg, this); a.detach();		// Create Thread
		return true;
	}
	else if (name == "ShowLoginDlg") {
		std::thread a(&CEF_Init_V8Handler::ShowLoginDlg, this); a.detach();		// Create Thread
		return true;
	}
	else if (name == "ShowLogin_SSODlg") {
		std::thread a(&CEF_Init_V8Handler::ShowLogin_SSODlg, this); a.detach(); // Create Thread
		return true;
	}
	// �ж��Ƿ�ͳһ�����֤��¼
	else if (name == "PdSSOLogin") {
		bool result = VariableClass::loginSSOClass.PdLogin();
		retval = CefV8Value::CreateBool(result);
		return true;
	}	
	// �ж�ͳһ�����֤�����������Ƿ��ȡ�ɹ�
	else if (name == "SSOGetServerConfig") {
		bool result = VariableClass::loginSSOClass.GetServerConfig();
		retval = CefV8Value::CreateBool(result);
		return true;
	}
	// ͳһ�����֤�����������ύ
	else if (name == "SSOSumbitServerConfig") {
		bool result = VariableClass::loginSSOClass.SumbitServerConfig();
		retval = CefV8Value::CreateBool(result);
		return true;
	}
	return false;
}

void CEF_Init_V8Handler::ShowMainDlg() {
	VariableClass::createDlgClass.main();
}

void CEF_Init_V8Handler::ShowLoginDlg() {
	// �ж��Ƿ��д���(��ʼ������)
	VariableClass::CefBrowserMapClass cefBrowserMapClass = VariableClass::getCefBrowserMap("init");
	if (cefBrowserMapClass.dlgHwnd) {
		// ���ص�����ֹ�������������ڵ��¸ô���ûʶ�𵽣�
		VariableClass::appDlgClass.Minimize(cefBrowserMapClass.dlgHwnd);
	}
	VariableClass::createDlgClass.login();
}

void CEF_Init_V8Handler::ShowLogin_SSODlg() {
	VariableClass::createDlgClass.login_sso();
}