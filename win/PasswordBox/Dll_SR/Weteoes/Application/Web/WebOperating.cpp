#include <Weteoes/Loading.h>
#include "WebOperating.h"
#include <Weteoes/Application/Config.h>

bool WebOperatingClass::Entrance(string operatingUrl, string &result) {
	string operatingName, operatingData;
	if (operatingUrl.find("?") != -1) {
		// 如果有参数
		operatingName = VariableClass::configClass.GetConfig(operatingUrl, "?");
		operatingData = operatingUrl;
	}
	else {
		// 没有参数
		operatingName = operatingUrl;
	}
	// 如果为空
	if (operatingName.empty()) { return false; }
	// 判断操作
	if (operatingName == "/operating/get") {
		result = operating_operating_get(operatingData);
		return true;
	}
	return false;
}

string WebOperatingClass::operating_operating_get(string data) {
	return data;
}
