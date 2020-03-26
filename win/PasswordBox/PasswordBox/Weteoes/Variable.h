#pragma once
#ifndef VariableClass_H
#define VariableClass_H

#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Application/Dll/APP_Dll_SWR.h>

class VariableClass {
public:
	static AppConfigClass appConfig;
	static APP_Dll_SWR app_Dll_SWR;
	static HWND dlg_HWND;
};
#endif