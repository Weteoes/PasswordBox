#include <pch.h>

#ifndef AppCefClass_H
#define AppCefClass_H
#include <Weteoes/More/CEF/include/cef_app.h>

#ifdef _DEBUG
#pragma comment(lib, "CEF/libcef_dll_wrapper_d.lib")
#else
#pragma comment(lib, "CEF/libcef_dll_wrapper.lib")
#endif
#pragma comment(lib, "CEF/libcef.lib")

class AppCefClass
{
public:
	bool Init_CEF();
	CefSettings GetSetting();
	std::string GetUrl(std::string);

private:
	wchar_t* ToUnicode(char*);
};

#endif