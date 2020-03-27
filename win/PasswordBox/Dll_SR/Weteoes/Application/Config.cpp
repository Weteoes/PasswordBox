#include <pch.h>
#include "Config.h"

char* ConfigClass::Socket_Header = (char*)"Weteoes";
ConfigClass ConfigClass::use;

std::string ConfigClass::GetConfig(std::string &data, std::string flag) {
	int a = (int)data.find(flag);
	if (a != -1) {
		std::string b = data.substr(0, a);
		std::string c = data.substr(b.length() + 1);
		data = c;
		return b;
	}
	return "";
}

#include <algorithm>
std::string ConfigClass::StrToLower(std::string str) {
	std::string strTmp = str;
	transform(strTmp.begin(), strTmp.end(), strTmp.begin(), tolower);
	return strTmp;
}

#include <sstream>
std::vector<std::string> ConfigClass::split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}