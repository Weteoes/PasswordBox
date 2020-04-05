#include <pch.h>
#include "CEF_Init_V8Handler.h"
#include <Weteoes\Dlg\Main_Dlg.h>

bool CEF_Init_V8Handler::Execute(
	const CefString& name,                        //JavaScript���õ�C++��������
	CefRefPtr<CefDictionaryValue> arguments,              //JavaScript���ݵĲ���
	CefRefPtr<CefV8Value>& retval,                //��Ҫ���ظ�JavaScript��ֵ���ø��������
	CefString& exception)                         //֪ͨ�쳣��Ϣ��JavaScript	
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
		std::thread a(&CEF_Init_V8Handler::ShowMainDlg, this); a.detach(); //Create Thread
		return true;
	}
	return false;
}

void CEF_Init_V8Handler::ShowMainDlg() {
	VariableClass::createDlgClass.main();
}