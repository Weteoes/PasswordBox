#include <Weteoes/Application/Management.h>
#include <Weteoes/Application/Config.h>

std::string ManagementClass::Get(char* a) {
	std::string a_s = a;
	if (a_s == "Software_Name") { return Config_Software_Name; }  // ��������
	else if (a_s == "Software_UI_Host") { return Config_Software_UI_Host; }  // ����UI��ַ
	else if (a_s == "Software_UI_Port") { return Config_Software_UI_Port; }  // ����UI�˿�
	//else if	(a_s == "URL_Client") { return Config_UI_Host; }  //�ͻ���ҳ��
	//else if (a_s == "URL_Update") { return Config_URL; } // Update
	//else if (a_s == "URL_Socket") { return Config_URL; }  // Socket
	//else if (a_s == "Socket_Port") { return Config_Socket_Port; }  // Socket�˿�
	//else if (a_s == "Version") { return Config_Version; }  // Version
	return "";
}