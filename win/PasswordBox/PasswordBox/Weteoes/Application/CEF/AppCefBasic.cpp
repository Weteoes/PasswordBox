#include <pch.h>
#include "AppCefBasic.h"

void AppCefBasicClass::ExecJavaScript(CefRefPtr<CefBrowser> browser, string js) {
	CefRefPtr<CefFrame> frame = browser->GetMainFrame();
	if (frame)
		frame->ExecuteJavaScript(js, L"", 0);
}

string AppCefBasicClass::GetJavaScriptNamebyDlg(string dlgFun) {
	string a = "weteoes.";
	if (dlgFun == "OnActivate") {
		// ´°¿Ú½¹µã
		return a + "softwareDlgApi.activate_(%d)";
	}
	return "";
}
