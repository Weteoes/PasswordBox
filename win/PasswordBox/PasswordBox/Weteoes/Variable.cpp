#include <pch.h>
#include "Variable.h"

AppConfigClass VariableClass::appConfig;
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