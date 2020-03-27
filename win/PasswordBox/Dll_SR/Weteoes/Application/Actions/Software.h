#ifndef SoftwareClass_H
#define SoftwareClass_H
#include <pch.h>

class SoftwareClass {
public:
	void RebootSoftware();
};
#endif

#ifndef SoftwareClass_CPP
#define SoftwareClass_CPP
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ManagementDll.h>
#include <Weteoes/Dll/ConfigDll.h>

void SoftwareClass::RebootSoftware() {
	ConfigDll().Loading();
	ManagementDll().Loading();
	ConfigDll::Config_CreateUser((char*)""); //清空配置
	std::string Software_Name = ManagementDll::Get((char*)"Software_Name");
	if (Software_Name.empty()) { return; }
	std::string ApplictionPath = WeteoesDll::Basics_GetNowFilePath();
	std::string a = ApplictionPath + Software_Name + ".exe";
	WeteoesDll::CMD_Run((char*)a.c_str()); //重新启动
	exit(0x51);
}
#endif