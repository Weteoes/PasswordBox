#include <pch.h>
#include "AppCefBasic.h"

void AppCefBasicClass::ExecJavaScript(CefRefPtr<CefBrowser> browser, string js) {
	CefRefPtr<CefFrame> frame = browser->GetMainFrame();
	if (frame)
		frame->ExecuteJavaScript(js, L"", 0);
}

string AppCefBasicClass::GetJavaScriptNamebyDlg(string dlgFun) {
	if (dlgFun == "OnActivate") {
		// ´°¿Ú½¹µã
		return jsHeader + "softwareDlgApi.activate_(%d)";
	}
	return "";
}

string AppCefBasicClass::GetJavaScriptNamebyCallBack() {
	return jsHeader + "softwareDlgCallBack";
}