#include <pch.h>
#include "Variable.h"

WebOperatingClass VariableClass::webOperatingClass; 
ConfigClass VariableClass::configClass;
RSAClass VariableClass::rsaClass;
WebBasicClass VariableClass::webBasicClass;
AESClass VariableClass::aesClass;

map<string, string> VariableClass::variable_map;
// 变量			 内容		 备注
// LoginIn		 0/1		 是否已经登录（全局登录判断）
// isSSOLogin	 0/1		 是否通过统一身份认证登录

string VariableClass::getVariable(string key) {
	map<string, string>::iterator i = variable_map.find(key);
	if (i == variable_map.end()) {
		return "";
	}
	return i->second;
}

bool VariableClass::setVariable(string key, string value) {
	map<string, string>::iterator i;
	i = variable_map.find(key);
	if (i != variable_map.end()) {
		variable_map.erase(i);
	}
	variable_map.insert(pair<string, string>(key, value));
	return true;
}
