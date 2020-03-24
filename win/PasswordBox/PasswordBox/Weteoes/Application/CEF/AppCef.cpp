#include <pch.h>

#ifndef AppCefClass_Cpp
#define AppCefClass_Cpp

#include "AppCef.h"
#include <Weteoes/More/CEF/Config.h> //CEF-Config
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ManagementDll.h>
#include <cstring>

std::string AppCefClass::Url;

CefSettings AppCefClass::GetSetting()
{
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
	//CefString(&settings.locales_dir_path) = ToUnicode((char*)(CEF_Path + "CEF\\Resources\\locales\\").c_str());
	return settings;
}

std::string AppCefClass::GetUrl(std::string url) {
	std::string URL_Client = ManagementDll::Get("URL_Client");
	if (URL_Client.empty()) { return url; }
	url = URL_Client + url;
	return url;
}

wchar_t* AppCefClass::ToUnicode(char* ansiStr)
{
	int len = MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, NULL, 0);  // ��ȡ��ת�����UNICODE�ַ�������ĳ���
	wchar_t* buf1 = (wchar_t*)calloc(len, sizeof(wchar_t));         // ���仺����
	MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, buf1, len);    // ��ʼת��
	return buf1;
}
#endif