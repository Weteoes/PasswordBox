#include <pch.h>

#ifndef CEF_Main_V8Handler_CPP
#define CEF_Main_V8Handler_CPP

#include "CEF_Main_V8Handler.h"
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>

bool CEF_Main_V8Handler::Execute(
	const CefString& name,                        //JavaScript���õ�C++��������
	CefRefPtr<CefV8Value> object,                 //JavaScript�����߶���
	const CefV8ValueList& arguments,              //JavaScript���ݵĲ���
	CefRefPtr<CefV8Value>& retval,                //��Ҫ���ظ�JavaScript��ֵ���ø��������
	CefString& exception)                         //֪ͨ�쳣��Ϣ��JavaScript	
{
	return false;
}
#endif