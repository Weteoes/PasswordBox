#include <pch.h>
#ifndef CEF_V8Handler_CPP
#define CEF_V8Handler_CPP

#include "CEF_V8Handler.h"
#include <Weteoes/Variable.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>

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
#endif
