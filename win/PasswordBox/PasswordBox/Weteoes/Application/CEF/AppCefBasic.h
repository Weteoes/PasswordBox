#pragma once
#include <pch.h>
#ifndef AppCefBasicClass_H
#define AppCefBasicClass_H
class AppCefBasicClass {
public:
	void ExecJavaScript(CefRefPtr<CefBrowser> browser, string js);

public:
	std::string jsHeader = "weteoes.";
	std::string GetJavaScriptNamebyDlg(string dlgFun);	 // �ͻ��˻ص�����������ڣ�
	std::string GetJavaScriptNamebyCallBack();			 // �ͻ��˻ص��������������

};
#endif