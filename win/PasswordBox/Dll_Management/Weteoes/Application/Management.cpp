#include <Weteoes/Application/Management.h>
#include <Weteoes/Application/Config.h>

std::string ManagementClass::Get(char* a) {
	std::string a_s = a;
	if		(a_s == "URL_Client") { return Config_UI_URL; }  //客户端页面
	else if (a_s == "URL_Update") { return Config_URL; } // Update
	else if (a_s == "URL_Socket") { return Config_URL; }  // Socket
	else if (a_s == "Socket_Port") { return Config_Socket_Port; }  // Socket端口
	else if (a_s == "Software_Title") { return Config_Software_Title; }  // 程序窗口名称
	else if (a_s == "Version") { return Config_Version; }  // Version
	return "";
}