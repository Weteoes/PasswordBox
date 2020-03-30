#pragma once
#ifndef VariableClass_H
#define VariableClass_H

#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Application/AppIcon.h>
#include <Weteoes/Application/AppDlg.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/Application/Dll/APP_Dll_SWR.h>


class VariableClass {
public:
	static AppConfigClass appConfig;
	static AppIconClass appIconClass;
	static AppDlgClass appDlgClass;
	static AppCefClass appCefClass;
	static APP_Dll_SWR app_Dll_SWR;

	static HWND dlg_HWND; // 当前活动窗口句柄
};
#endif