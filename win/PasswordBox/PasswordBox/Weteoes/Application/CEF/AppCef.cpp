#include <pch.h>

#ifndef AppCefClass_Cpp
#define AppCefClass_Cpp

#include "AppCef.h"
#include <Weteoes/More/CEF/Config.h> //CEF-Config
#include <Weteoes/More/CEF/Application/Ready/CEF_App_Ready.h> //CEF-Config
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ManagementDll.h>

bool AppCefClass::Init_CEF() {
	CefMainArgs mainArgs(AfxGetInstanceHandle());
	CefRefPtr<CEF_App_Ready> app(new CEF_App_Ready);
	CefExecuteProcess(mainArgs, app.get(), NULL);
	CefSettings settings = AppCefClass().GetSetting();
	CefInitialize(mainArgs, settings, app.get(), NULL);
	return true;
}

CefSettings AppCefClass::GetSetting() {
	std::string CEF_Path = WeteoesDll::Basics_GetNowFilePath();
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
#ifdef _DEBUG
#else
	settings.log_severity = LOGSEVERITY_DISABLE;
#endif // _DEBUG
	CefString(&settings.cache_path) = AppConfigClass::Get_TempPath() + "CEF\\";
	CefString(&settings.resources_dir_path) = ToUnicode((char*)(CEF_Path + "CEF\\Resources").c_str());
	CefString(&settings.locales_dir_path) = ToUnicode((char*)(CEF_Path + "CEF\\Resources\\locales\\").c_str());
	return settings;
}

std::string AppCefClass::GetUrl(std::string url) {
	std::string Software_UI_Host = ManagementDll::Get("Software_UI_Host");
	std::string Software_UI_Port = ManagementDll::Get("Software_UI_Port");
	if (Software_UI_Host.empty() && Software_UI_Port.empty()) { return url; }
	url = Software_UI_Host + ":" + Software_UI_Port + url;
	return url;
}

wchar_t* AppCefClass::ToUnicode(char* ansiStr)
{
	int len = MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, NULL, 0);  // 先取得转换后的UNICODE字符串所需的长度
	wchar_t* buf1 = (wchar_t*)calloc(len, sizeof(wchar_t));         // 分配缓冲区
	MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, buf1, len);    // 开始转换
	return buf1;
}
#endif