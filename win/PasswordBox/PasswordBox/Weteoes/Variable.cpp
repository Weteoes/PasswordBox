#include <pch.h>
#include "Variable.h"

LoginSSOClass VariableClass::loginSSOClass;
AppConfigClass VariableClass::appConfigClass;
AppIconClass VariableClass::appIconClass;
AppDlgClass VariableClass::appDlgClass;
CreateDlgClass VariableClass::createDlgClass;
AppCefClass VariableClass::appCefClass;
AppCefBasicClass VariableClass::appCefBasicClass;
APP_Dll_SWR VariableClass::app_Dll_SWR;

CEF_Init_V8Handler VariableClass::cef_Init_V8Handler;
CEF_Login_V8Handler VariableClass::cef_Login_V8Handler;
CEF_Main_V8Handler VariableClass::cef_Main_V8Handler; 
CEF_ChangePassword_V8Handler VariableClass::cef_ChangePassword_V8Handler;



int VariableClass::dlg_CEF;
HWND VariableClass::dlg_HWND;


map<string, VariableClass::CefBrowserMapClass> VariableClass::cefBrowserMap;
//  Ãû³ÆID		 ä¯ÀÀÆ÷Ö¸Õë		

VariableClass::CefBrowserMapClass VariableClass::getCefBrowserMap(std::string key) {
	map<string, CefBrowserMapClass>::iterator i = cefBrowserMap.find(key);
	if (i == cefBrowserMap.end()) {
		return CefBrowserMapClass(0, NULL);
	} 
	return i->second;
}

bool VariableClass::setCefBrowserMap(std::string key, HWND DlgHwnd, CefRefPtr<CefBrowser> browser) {
	map<string, CefBrowserMapClass>::iterator i;
	i = cefBrowserMap.find(key);
	if (i != cefBrowserMap.end()) {
		cefBrowserMap.erase(i);
	}
	cefBrowserMap.insert(
		std::pair<std::string, CefBrowserMapClass>(
			key, 
			CefBrowserMapClass(DlgHwnd, browser)
		)
	);
	return true;
}
