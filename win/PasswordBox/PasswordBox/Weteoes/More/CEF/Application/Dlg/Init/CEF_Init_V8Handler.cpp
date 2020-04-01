#include <pch.h>
#include "CEF_Init_V8Handler.h"

bool CEF_Init_V8Handler::Execute(
	const CefString& name,                        //JavaScript调用的C++方法名字
	CefRefPtr<CefDictionaryValue> arguments,              //JavaScript传递的参数
	CefRefPtr<CefV8Value>& retval,                //需要返回给JavaScript的值设置给这个对象
	CefString& exception)                         //通知异常信息给JavaScript	
{
	if (name == "Init") { //退出按钮
		string token = arguments->GetString("b");
		string token1 = arguments->GetString("b1");
		int id = arguments->GetInt("a");
		int id1 = arguments->GetInt("a1");
		retval = CefV8Value::CreateString("123123123");
		return true;
	}
	return false;
}