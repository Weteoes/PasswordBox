#ifndef CEF_Init_V8Handler_H
#define CEF_Init_V8Handler_H
#include <Weteoes\More\CEF\include\cef_v8.h>
#include <Weteoes\More\CEF\include\internal\cef_string.h>

class CEF_Init_V8Handler {
public:
	bool Execute(
		const CefString& name,
		CefRefPtr<CefDictionaryValue> arguments = NULL,
		CefRefPtr<CefV8Value>& retval = CefRefPtr<CefV8Value>(),
		CefString& exception = CefString()
	);

private:
	void ShowMainDlg();
	void ShowLoginDlg();
	void ShowLogin_SSODlg();
};
#endif