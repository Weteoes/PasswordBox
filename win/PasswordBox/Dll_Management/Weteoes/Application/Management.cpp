#include <Weteoes/Application/Management.h>
#include <Weteoes/Application/Config.h>

std::string ManagementClass::Get(char* a) {
	std::string a_s = a;
	if (a_s == "Software_Name") { return Config_Software_Name; }  // ��������
	else if (a_s == "Software_UI_Host") { return Config_Software_UI_Host; }  // ����UI��ַ
	else if (a_s == "Software_UI_Port") { return Config_Software_UI_Port; }  // ����UI�˿�
	return "";
}