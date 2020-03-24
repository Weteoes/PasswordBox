#include <pch.h>
#include "V8Handler.h"
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>

bool V8Handler_Class::Execute(
	const CefString& name,                        //JavaScript调用的C++方法名字
	CefRefPtr<CefV8Value> object,                 //JavaScript调用者对象
	const CefV8ValueList& arguments,              //JavaScript传递的参数
	CefRefPtr<CefV8Value>& retval,                //需要返回给JavaScript的值设置给这个对象
	CefString& exception)                         //通知异常信息给JavaScript	
{
	//if (name == "SystemMenu_Exit") { //退出按钮
	//	DlgClass().Dlg_Close();
	//	return true;
	//}
	return false;
}