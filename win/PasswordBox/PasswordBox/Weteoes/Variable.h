#pragma once
#ifndef VariableClass_H
#define VariableClass_H

#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Application/AppIcon.h>
#include <Weteoes/Application/AppDlg.h>
#include <Weteoes/Application/CreateDlg.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/Application/CEF/AppCefBasic.h>
#include <Weteoes/Application/Dll/APP_Dll_SWR.h>
#include <Weteoes/More/CEF/Application/Dlg/Init/CEF_Init_V8Handler.h>
#include <Weteoes/More/CEF/Application/Dlg/Login/CEF_Login_V8Handler.h>
#include <Weteoes/More/CEF/Application/Dlg/Main/CEF_Main_V8Handler.h>
#include <Weteoes/More/CEF/Application/Dlg/ChangePassword/CEF_ChangePassword_V8Handler.h>


class VariableClass {
public:
	static AppConfigClass appConfig;
	static AppIconClass appIconClass;
	static AppDlgClass appDlgClass;
	static CreateDlgClass createDlgClass;
	static AppCefClass appCefClass;
	static AppCefBasicClass appCefBasicClass;
	static APP_Dll_SWR app_Dll_SWR;

	static CEF_Init_V8Handler cef_Init_V8Handler;
	static CEF_Login_V8Handler cef_Login_V8Handler;
	static CEF_Main_V8Handler cef_Main_V8Handler;
	static CEF_ChangePassword_V8Handler cef_ChangePassword_V8Handler;

	static int dlg_CEF; // ��ǰ�����CEF�ؼ����
	static HWND dlg_HWND; // ��ǰ����ھ��
};
#endif