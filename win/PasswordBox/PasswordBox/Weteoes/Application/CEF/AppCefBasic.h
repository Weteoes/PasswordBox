#pragma once
#include <pch.h>
#ifndef AppCefBasicClass_H
#define AppCefBasicClass_H
class AppCefBasicClass {
public:
	void ExecJavaScript(CefRefPtr<CefBrowser> browser, string js);

public:
	std::string jsHeader = "weteoes.";
	std::string GetJavaScriptNamebyDlg(string dlgFun);	 // 客户端回调浏览器（窗口）
	std::string GetJavaScriptNamebyCallBack();			 // 客户端回调浏览器（其他）

};
#endif