#include <pch.h>
#include "CEF_Init_V8Handler.h"
#include <Weteoes\Dlg\Main_Dlg.h>

bool CEF_Init_V8Handler::Execute(
	const CefString& name,                        //JavaScript调用的C++方法名字
	CefRefPtr<CefDictionaryValue> arguments,              //JavaScript传递的参数
	CefRefPtr<CefV8Value>& retval,                //需要返回给JavaScript的值设置给这个对象
	CefString& exception)                         //通知异常信息给JavaScript	
{
	if (name == "AesInit") {
		// 判断密码和初始化密码
		string pass = arguments->GetString("pass");
		bool result = ConfigDll::Config_SetAESPassword((char*)pass.c_str());
		if (result) {
			// 密码正确
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