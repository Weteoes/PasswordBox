#include <pch.h>
#include "V8Handler.h"
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>

bool V8Handler_Class::Execute(
	const CefString& name,                        //JavaScript���õ�C++��������
	CefRefPtr<CefV8Value> object,                 //JavaScript�����߶���
	const CefV8ValueList& arguments,              //JavaScript���ݵĲ���
	CefRefPtr<CefV8Value>& retval,                //��Ҫ���ظ�JavaScript��ֵ���ø��������
	CefString& exception)                         //֪ͨ�쳣��Ϣ��JavaScript	
{
	//if (name == "SystemMenu_Exit") { //�˳���ť
	//	DlgClass().Dlg_Close();
	//	return true;
	//}
	return false;
}