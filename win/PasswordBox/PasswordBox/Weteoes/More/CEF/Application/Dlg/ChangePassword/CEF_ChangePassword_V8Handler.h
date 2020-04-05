#ifndef CEF_ChangePassword_V8Handler_H
#define CEF_ChangePassword_V8Handler_H
#include <Weteoes\More\CEF\include\cef_v8.h>
#include <Weteoes\More\CEF\include\internal\cef_string.h>

class CEF_ChangePassword_V8Handler {
public:
	bool Execute(
		const CefString& name,
		CefRefPtr<CefDictionaryValue> arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception
		);
};
#endif