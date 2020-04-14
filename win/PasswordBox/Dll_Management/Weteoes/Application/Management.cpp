#include <Weteoes/Application/Management.h>
#include <Weteoes/Application/Config.h>

std::string ManagementClass::Get(char* a) {
	std::string a_s = a;
	if (a_s == "Software_Name") { return Config_Software_Name; }  // 程序名称
	else if (a_s == "Software_UI_Host") { return Config_Software_UI_Host; }  // 程序UI地址
	else if (a_s == "Software_UI_Port") { return Config_Software_UI_Port; }  // 程序UI端口
	return "";
}