#pragma once
#include <pch.h>
#ifndef AppCefBasicClass_H
#define AppCefBasicClass_H
class AppCefBasicClass {
public:
	void ExecJavaScript(CefRefPtr<CefBrowser> browser, string js);
	string GetJavaScriptNamebyDlg(string dlgFun);
};
#endif