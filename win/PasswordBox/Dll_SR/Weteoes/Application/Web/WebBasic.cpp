#include <pch.h>
#include "WebBasic.h"
#include <assert.h>

string WebBasicClass::get_HtmlConfig(string data, string configName) {
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

std::string WebBasicClass::UrlEncode(const std::string& str) {
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] % 16);
		}
	}
	return strTemp;
}

std::string WebBasicClass::UrlDecode(const std::string& str) {
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+') strTemp += ' ';
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
}

unsigned char WebBasicClass::ToHex(unsigned char x) {
	return  x > 9 ? x + 55 : x + 48;
}

unsigned char WebBasicClass::FromHex(unsigned char x) {
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else assert(0);
	return y;
}