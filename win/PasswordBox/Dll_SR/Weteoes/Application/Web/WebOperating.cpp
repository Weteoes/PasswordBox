#include <pch.h>
#include "WebOperating.h"
#include <Weteoes/Application/Config.h>

bool WebOperatingClass::Entrance(string operatingUrl, string &result) {
	// 判断是否登录
	string LoginIn = VariableClass::getVariable("LoginIn");
	if (LoginIn == "" || LoginIn == "0") {
		// 如果未登录，不执行
		return false;
	}
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
		operating_operating_browser_del(operatingData); // 删除原本的
		result = operating_operating_browser_create(operatingData); // 创建
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
	string Host = VariableClass::webBasicClass.get_HtmlConfig(data, "Host");
	char* result_c = new char[100];
	string result_format_s = "{\"Code\":%d}";
	int code = 1;
	if (Host.empty()) {
		goto result;
	}
	else {
		// 解码
		Host = VariableClass::webBasicClass.UrlDecode(Host);
		code = VariableClass::configDll.Config_DelUserAndPassword(Host.c_str()) ? 0 : 1;
	}
result:
	sprintf_s(result_c, 100, result_format_s.c_str(), code);
	return result_c;
}

string WebOperatingClass::operating_operating_browser_create(string data) {
	string Host = VariableClass::webBasicClass.get_HtmlConfig(data, "Host");
	string User = VariableClass::webBasicClass.get_HtmlConfig(data, "User");
	string Pass = VariableClass::webBasicClass.get_HtmlConfig(data, "Pass");
	char* result_c = new char[100];
	string result_format_s = "{\"Code\":%d}";
	int code = 1;
	if (Host.empty() || User.empty() || Pass.empty()) {
		goto result;
	}
	else {
		// 解码
		Host = VariableClass::webBasicClass.UrlDecode(Host);
		code = VariableClass::configDll.Config_CreateUserAndPassword(Host.c_str(), User.c_str(), Pass.c_str()) ? 0 : 1;
	}
result:
	sprintf_s(result_c, 100, result_format_s.c_str(), code);
	return result_c;
}

string WebOperatingClass::operating_operating_browser_get(string data) {
	string Host = VariableClass::webBasicClass.get_HtmlConfig(data, "Host");
	char* result_c = new char[1000];
	string result_format_s = "{\"Code\":%d, \"Data\":{%s}}";
	string result_format_data = "";
	int code = 1;
	if (Host.empty()) {
		goto result;
	}
	else {
		// 解码
		Host = VariableClass::webBasicClass.UrlDecode(Host);
		ConfigDll::Struct_UserAndPassword a = VariableClass::configDll.Config_ReadUserAndPassword(Host.c_str());
		if (strlen(a.Host) != 0) {
			// 有数据
			code = 0;
			char* result_format_data_c = new char[1000];
			sprintf_s(result_format_data_c, 1000, "\"Host\":\"%s\",\"User\":\"%s\",\"Pass\":\"%s\"", a.Host, a.User, a.Pass);
			result_format_data = result_format_data_c;
			goto result;
		}
		else {
			// 无数据
			code = 2;
			goto result;
		}
	}
result:
	sprintf_s(result_c, 1000, result_format_s.c_str(), code, result_format_data.c_str());
	return result_c;
}

string WebOperatingClass::operating_operating_console_getAll(string data) {
	char* result_c = new char[10000];
	string result_format_s = "{\"Code\":%d, \"List\":[%s]}";
	string result_list = "";
	int code = 0;
	vector<ConfigDll::Struct_UserAndPassword> a = VariableClass::configDll.Config_ReadAllUserAndPassword();
	for (int i = 0; i < a.size(); i++) {
		string Host = a[i].Host;
		string User = a[i].User;
		string Pass = a[i].Pass;
		char* aaa = new char[200];
		char* onlyData_c = new char[1000];
		sprintf_s(onlyData_c, 1000, "{\"Host\":\"%s\",\"User\":\"%s\",\"Pass\":\"%s\"}", Host.c_str(), User.c_str(), Pass.c_str());
		result_list += onlyData_c;
		if (i + 1 < (int)a.size()) {
			result_list += ",";
		}
	}
	sprintf_s(result_c, 10000, result_format_s.c_str(), code, result_list.c_str());
	return result_c;
}

