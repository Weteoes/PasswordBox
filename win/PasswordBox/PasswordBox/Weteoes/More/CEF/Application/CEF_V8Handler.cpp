#include <pch.h>
#ifndef CEF_V8Handler_CPP
#define CEF_V8Handler_CPP

#include "CEF_V8Handler.h"
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes\More\CEF\include\cef_parser.h>

bool CEF_V8Handler::Execute(
	const CefString& name,                        //JavaScript���õ�C++��������
	CefRefPtr<CefV8Value> object,                 //JavaScript�����߶���
	const CefV8ValueList& arguments,              //JavaScript���ݵĲ���
	CefRefPtr<CefV8Value>& retval,                //��Ҫ���ظ�JavaScript��ֵ���ø��������
	CefString& exception)                         //֪ͨ�쳣��Ϣ��JavaScript	
{
	if (name == "Dlg_Mouse_Down") { //�˳���ť
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
	else if (name == "App") {
		App(name, object, arguments, retval, exception);
		return true;
	}
	return false;
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
	//::MoveWindow(VariableClass::dlg_HWND, x, y,0,0,0);
}

void CEF_V8Handler::Dlg_Mouse_Up() {
	Dlg_Mouse_Down_Status = false;
	Dlg_Mouse_Down_X = -1;
	Dlg_Mouse_Down_Y = -1;
}
void CEF_V8Handler::App(
	const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments, 
	CefRefPtr<CefV8Value>& retval,
	CefString& exception
) {
	string app = arguments[0]->GetStringValue();
	string fun = arguments[1]->GetStringValue();
	string args = arguments[2]->GetStringValue();
	if (args.empty()) { return; }
	CefRefPtr<CefValue> jsonObject = CefParseJSON(args, JSON_PARSER_ALLOW_TRAILING_COMMAS);
	CefRefPtr<CefDictionaryValue> dict = jsonObject->GetDictionary();
	if (app.empty() || fun.empty()) { return; }
	if (app == "Init") { VariableClass::cef_Init_V8Handler.Execute(app, dict, retval, exception); return; }
}
#endif
