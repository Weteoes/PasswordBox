#include <pch.h>
#include "Variable.h"

WebOperatingClass VariableClass::webOperatingClass; 
ConfigClass VariableClass::configClass;
RSAClass VariableClass::rsaClass;
ConfigDll VariableClass::configDll;
WebBasicClass VariableClass::webBasicClass;
SecurityAESClass VariableClass::securityAESClass;

map<string, string> VariableClass::variable_map;
// 变量			 内容		 备注
// LoginIn		 0/1		 是否已经登录

string VariableClass::getVariable(string key) {
	map<string, string>::iterator i = variable_map.find(key);
	if (i == variable_map.end()) {
		return "";
	}
	return i->second;
}

bool VariableClass::setVariable(string key, string value) {
	variable_map.insert(pair<string, string>(key, value));
	return true;
}
