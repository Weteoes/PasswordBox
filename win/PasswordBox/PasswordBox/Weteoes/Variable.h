#pragma once
#ifndef VariableClass_H
#define VariableClass_H

#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Application/AppIcon.h>
#include <Weteoes/Application/AppDlg.h>
#include <Weteoes/Application/AppDlgCallBack.h>
#include <Weteoes/Application/CreateDlg.h>
#include <Weteoes/Application/Login/LoginSSO.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/Application/CEF/AppCefBasic.h>
#include <Weteoes/Application/Dll/APP_Dll_SWR.h>
#include <Weteoes/More/CEF/Application/Dlg/Init/CEF_Init_V8Handler.h>
#include <Weteoes/More/CEF/Application/Dlg/Login/CEF_Login_V8Handler.h>
#include <Weteoes/More/CEF/Application/Dlg/Main/CEF_Main_V8Handler.h>
#include <Weteoes/More/CEF/Application/Dlg/ChangePassword/CEF_ChangePassword_V8Handler.h>


class VariableClass {
public:
	static LoginSSOClass loginSSOClass;
	static AppConfigClass appConfigClass;
	static AppIconClass appIconClass;
	static AppDlgClass appDlgClass;
	static AppDlgCallBackClass appDlgCallBackClass;
	static CreateDlgClass createDlgClass;

	static AppCefClass appCefClass;
	static AppCefBasicClass appCefBasicClass;
	static APP_Dll_SWR app_Dll_SWR;

	static CEF_Init_V8Handler cef_Init_V8Handler;
	static CEF_Login_V8Handler cef_Login_V8Handler;
	static CEF_Main_V8Handler cef_Main_V8Handler;
	static CEF_ChangePassword_V8Handler cef_ChangePassword_V8Handler;


public:
	static int dlg_CEF;								// 当前活动窗口CEF控件句柄
	static HWND dlg_HWND;							// 当前活动窗口句柄

public:
	static bool isSSOLogin;							// 是否统一身份认证登录


public:
	class CefBrowserMapClass {
	public:
		CefBrowserMapClass(HWND dlgHwnd, CefRefPtr<CefBrowser> cefBrowser) {
			this->dlgHwnd = dlgHwnd;
			this->cefBrowser = cefBrowser;
		}
	public:
		HWND dlgHwnd = 0;
		CefRefPtr<CefBrowser> cefBrowser = NULL;
	};
	static CefBrowserMapClass getCefBrowserMap(std::string key);
	static bool setCefBrowserMap(std::string key, HWND DlgHwnd, CefRefPtr<CefBrowser> browser);

private:
	static std::map<std::string, CefBrowserMapClass> cefBrowserMap;
};
#endif