#include <pch.h>
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
	if (operatingName == "/operating/browser/get") {
		result = operating_operating_browser_get(operatingData);
		return true;
	}
	else if (operatingName == "/operating/browser/create") {
		result = operating_operating_browser_create(operatingData);
		return true;
	}
	else if (operatingName == "/operating/browser/del") {
		result = operating_operating_browser_del(operatingData);
		return true;
	}
	else if (operatingName == "/operating/console/getAll") {
		result = operating_operating_console_getAll(operatingData);
		return true;
	}
	return false;
}


string WebOperatingClass::operating_operating_browser_del(string data) {
	string Host = get_HtmlConfig(data, "Host");
	char* result_c = new char[100];
	string result_format_s = "{code:%d}";
	int code = 1;
	if (Host.empty()) {
		goto result;
	}
	else {
		code = VariableClass::configDll.Config_DelUserAndPassword(Host.c_str()) ? 0 : 1;
	}
result:
	sprintf_s(result_c, 100, result_format_s.c_str(), code);
	return result_c;
}

string WebOperatingClass::operating_operating_browser_create(string data) {
	string Host = get_HtmlConfig(data, "Host");
	string User = get_HtmlConfig(data, "User");
	string Pass = get_HtmlConfig(data, "Pass");
	char* result_c = new char[100];
	string result_format_s = "{code:%d}";
	int code = 1;
	if (Host.empty() || User.empty() || Pass.empty()) {
		goto result;
	}
	else {
		code = VariableClass::configDll.Config_CreateUserAndPassword(Host.c_str(), User.c_str(), Pass.c_str()) ? 0 : 1;
	}
result:
	sprintf_s(result_c, 100, result_format_s.c_str(), code);
	return result_c;
}

string WebOperatingClass::operating_operating_browser_get(string data) {
	string Host = get_HtmlConfig(data, "Host");
	char* result_c = new char[1000];
	string result_format_s = "{code:%d}";
	int code = 1;
	if (Host.empty()) {
		sprintf_s(result_c, 1000, result_format_s.c_str(), code);
	}
	else {
		ConfigDll::Struct_UserAndPassword a = VariableClass::configDll.Config_ReadUserAndPassword(Host.c_str());
		if (strlen(a.Host) != 0) {
			// 有数据
			sprintf_s(result_c, 1000, "{Host:\"%s\",User:\"%s\",Pass:\"%s\"}", a.Host, a.User, a.Pass);
		}
		else {
			// 无数据
			code = 2;
			sprintf_s(result_c, 1000, result_format_s.c_str(), code);
		}
	}
	return result_c;
}

string WebOperatingClass::operating_operating_console_getAll(string data) {
	char* result_c = new char[10000];
	string result_format_s = "{code:%d, list:[%s]}";
	string result_list = "";
	int code = 0;
	vector<ConfigDll::Struct_UserAndPassword> a = VariableClass::configDll.Config_ReadAllUserAndPassword();
	for (int i = 0; i < a.size(); i++) {
		string Host = a[i].Host;
		string User = a[i].User;
		string Pass = a[i].Pass;
		char* aaa = new char[200];
		char* onlyData_c = new char[1000];
		sprintf_s(onlyData_c, 1000, "{Host:\"%s\",User:\"%s\",Pass:\"%s\"},", Host.c_str(), User.c_str(), Pass.c_str());
		result_list += onlyData_c;
	}
	sprintf_s(result_c, 10000, result_format_s.c_str(), code, result_list.c_str());
	return result_c;
}

string WebOperatingClass::get_HtmlConfig(string data, string configName) {
	// a=1&b=2
	vector<string> a = VariableClass::configClass.split(data, '&');
	for (int i = 0; i < a.size(); i++) {
		string onlyData = a[i];
		size_t b = onlyData.find("=");
		if (b == -1) {
			// 如果找不到就退出本次
			continue;
		}
		string onlyData_name = onlyData.substr(0, b);
		string onlyData_value = onlyData.substr(b + 1);
		if (onlyData_name == configName) {
			return onlyData_value;
		}
	}
	return string();
}
