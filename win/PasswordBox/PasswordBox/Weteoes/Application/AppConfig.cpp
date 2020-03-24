#include <pch.h>

#ifndef AppConfigClass_Cpp
#define AppConfigClass_Cpp

#include "AppConfig.h"
#include <Weteoes/Dll/ManagementDll.h>

std::string AppConfigClass::SoftwareName;
std::string AppConfigClass::Version;

std::string AppConfigClass::Get_SoftwareName() {
	if (!SoftwareName.empty()) { return SoftwareName; }
	AppConfigClass::SoftwareName = ManagementDll::Get("Software_Name");
	return SoftwareName;
}

std::string AppConfigClass::Get_Version() {
	if (!Version.empty()) { return Version; }
	AppConfigClass::Version = ManagementDll::Get("Version");
	return Version;
}

std::string AppConfigClass::Get_TempPath() {
	char Temp[MAX_PATH];
	GetTempPath(sizeof(Temp), Temp);
	std::string TempHome = (std::string)Temp + "Weteoes\\PasswordBox\\";
	return TempHome;
}
#endif