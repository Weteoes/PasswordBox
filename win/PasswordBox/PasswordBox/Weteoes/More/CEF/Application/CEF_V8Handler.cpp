#include <pch.h>
#ifndef CEF_V8Handler_CPP
#define CEF_V8Handler_CPP

#include "CEF_V8Handler.h"
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes\More\CEF\include\cef_parser.h>

bool CEF_V8Handler::Execute(
	const CefString& name,                        //JavaScript调用的C++方法名字
	CefRefPtr<CefV8Value> object,                 //JavaScript调用者对象
	const CefV8ValueList& arguments,              //JavaScript传递的参数
	CefRefPtr<CefV8Value>& retval,                //需要返回给JavaScript的值设置给这个对象
	CefString& exception)                         //通知异常信息给JavaScript	
{
	if (name == "Dlg_Mouse_Down") { //退出按钮
		int x = arguments[0]->GetIntValue();
		int y = arguments[1]->GetIntValue();
		Dlg_Mouse_Down(x, y);
		return true;
	}
	else if (name == "Dlg_Mouse_Move") {
		int x = arguments[0]->GetIntValue();
		int y = arguments[1]->GetIntValue();
		Dlg_Mouse_Move(x, y);
		return true;
	}
	else if (name == "Dlg_Mouse_Up") {
		Dlg_Mouse_Up();
		return true;
	}
	else if (name == "Dlg_Size") {
		int width = arguments[0]->GetIntValue();
		int height = arguments[1]->GetIntValue();
		VariableClass::appDlgClass.SetSize(width, height);
		return true;
	}
	else if (name == "Dlg_Minimize") {
		VariableClass::appDlgClass.Minimize();
		return true;
	}
	else if (name == "Dlg_Exit") {
		VariableClass::appDlgClass.Exit();
		return true;
	}
	else if (name == "Dlg_Close") {
		VariableClass::appDlgClass.Close();
		return true;
	}
	else if (name == "Dlg_Create") {
		string key = arguments[0]->GetStringValue();
		string url = arguments[1]->GetStringValue();
		if (!url.empty()) {
			thread a(&CEF_V8Handler::Dlg_CreateThread, this, key, url);
			a.detach();
		}
		return true;
	}
	else if (name == "App") {
		return App(name, object, arguments, retval, exception);
	}
	return false;
}

void CEF_V8Handler::Dlg_CreateThread(string key, string url) {
	VariableClass::createDlgClass.browser(key, url, true);
}

void CEF_V8Handler::Dlg_Mouse_Down(int x, int y) {
	Dlg_Mouse_Down_Status = true;
	Dlg_Mouse_Down_X = x;
	Dlg_Mouse_Down_Y = y;
}

void CEF_V8Handler::Dlg_Mouse_Move(int x, int y) {
	if (!Dlg_Mouse_Down_Status) { return; }
	int n_x = x - Dlg_Mouse_Down_X;
	int n_y = y - Dlg_Mouse_Down_Y;
	::SetWindowPos(VariableClass::dlg_HWND, NULL, n_x, n_y, 0, 0, SWP_NOSIZE);
}

void CEF_V8Handler::Dlg_Mouse_Up() {
	Dlg_Mouse_Down_Status = false;
	Dlg_Mouse_Down_X = -1;
	Dlg_Mouse_Down_Y = -1;
}
bool CEF_V8Handler::App(
	const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments, 
	CefRefPtr<CefV8Value>& retval,
	CefString& exception
) {
	string app = arguments[0]->GetStringValue();
	string fun = arguments[1]->GetStringValue();
	wstring args = arguments[2]->GetStringValue();
	CefRefPtr<CefDictionaryValue> argsDict;
	if (!args.empty()) { 
		// 有参数
		CefRefPtr<CefValue> jsonObject = CefParseJSON(args, JSON_PARSER_ALLOW_TRAILING_COMMAS);
		argsDict = jsonObject->GetDictionary();
	}
	if (app.empty() || fun.empty()) { return false; }
	if (app == "Init") { return VariableClass::cef_Init_V8Handler.Execute(fun, argsDict, retval, exception); }
	if (app == "Login") { return VariableClass::cef_Login_V8Handler.Execute(fun, argsDict, retval, exception); }
	if (app == "Main") { return VariableClass::cef_Main_V8Handler.Execute(fun, argsDict, retval, exception); }
	if (app == "ChangePassword") { return VariableClass::cef_ChangePassword_V8Handler.Execute(fun, argsDict, retval, exception); }
	return false;
}
#endif
