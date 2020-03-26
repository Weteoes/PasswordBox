#ifndef CEF_Main_V8Handler_H
#define CEF_Main_V8Handler_H
#include <Weteoes\More\CEF\include\cef_v8.h>
#include <Weteoes\More\CEF\include\internal\cef_string.h>

class CEF_Main_V8Handler : public CefV8Handler {
public:
	CEF_Main_V8Handler() {}

	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception) OVERRIDE;

	// Provide the reference counting implementation for this class.
	IMPLEMENT_REFCOUNTING(CEF_Main_V8Handler);
};
#endif