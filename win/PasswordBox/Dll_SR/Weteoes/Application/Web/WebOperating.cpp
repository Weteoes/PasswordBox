#include <Weteoes/Loading.h>
#include "WebOperating.h"
#include <Weteoes/Application/Config.h>

bool WebOperatingClass::Entrance(string operatingUrl, string &result) {
	string operatingName, operatingData;
	if (operatingUrl.find("?") != -1) {
		// ����в���
		operatingName = VariableClass::configClass.GetConfig(operatingUrl, "?");
		operatingData = operatingUrl;
	}
	else {
		// û�в���
		operatingName = operatingUrl;
	}
	// ���Ϊ��
	if (operatingName.empty()) { return false; }
	// �жϲ���
	if (operatingName == "/operating/get") {
		result = operating_operating_get(operatingData);
		return true;
	}
	return false;
}

string WebOperatingClass::operating_operating_get(string data) {
	return data;
}
