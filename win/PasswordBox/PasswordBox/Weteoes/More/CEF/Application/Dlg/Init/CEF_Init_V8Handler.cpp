#include <pch.h>
#include "CEF_Init_V8Handler.h"

bool CEF_Init_V8Handler::Execute(
	const CefString& name,                        //JavaScript���õ�C++��������
	CefRefPtr<CefDictionaryValue> arguments,              //JavaScript���ݵĲ���
	CefRefPtr<CefV8Value>& retval,                //��Ҫ���ظ�JavaScript��ֵ���ø��������
	CefString& exception)                         //֪ͨ�쳣��Ϣ��JavaScript	
{
	if (name == "Init") { //�˳���ť
		string token = arguments->GetString("b");
		string token1 = arguments->GetString("b1");
		int id = arguments->GetInt("a");
		int id1 = arguments->GetInt("a1");
		retval = CefV8Value::CreateString("123123123");
		return true;
	}
	return false;
}