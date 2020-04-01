#ifndef CEF_V8Handler_H
#define CEF_V8Handler_H

#include <Weteoes\More\CEF\include\cef_v8.h>
#include <Weteoes\More\CEF\include\internal\cef_string.h>

class CEF_V8Handler : public CefV8Handler {
public:
	CEF_V8Handler() {}

	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception) OVERRIDE;

	// Provide the reference counting implementation for this class.
	IMPLEMENT_REFCOUNTING(CEF_V8Handler);

private:
	bool Dlg_Mouse_Down_Status = false;
	int Dlg_Mouse_Down_X = -1, Dlg_Mouse_Down_Y = -1;
	void Dlg_Mouse_Down(int x, int y);
	void Dlg_Mouse_Move(int x, int y);
	void Dlg_Mouse_Up();
	void App(
		const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception
	);
};
#endif