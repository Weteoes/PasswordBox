#include <Weteoes/Application/Management.h>
#include <Weteoes/Application/Config.h>

std::string ManagementClass::Get(char* a) {
	std::string a_s = a;
	if		(a_s == "URL_Client") { return Config_UI_URL; }  //�ͻ���ҳ��
	else if (a_s == "URL_Update") { return Config_URL; } // Update
	else if (a_s == "URL_Socket") { return Config_URL; }  // Socket
	else if (a_s == "Socket_Port") { return Config_Socket_Port; }  // Socket�˿�
	else if (a_s == "Software_Title") { return Config_Software_Title; }  // ���򴰿�����
	else if (a_s == "Version") { return Config_Version; }  // Version
	return "";
}