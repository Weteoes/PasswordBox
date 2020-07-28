#include <pch.h>
#include "Variable.h"

WebOperatingClass VariableClass::webOperatingClass; 
ConfigClass VariableClass::configClass;
RSAClass VariableClass::rsaClass;
WebBasicClass VariableClass::webBasicClass;
AESClass VariableClass::aesClass;

map<string, string> VariableClass::variable_map;
// ����			 ����		 ��ע
// LoginIn		 0/1		 �Ƿ��Ѿ���¼��ȫ�ֵ�¼�жϣ�
// isSSOLogin	 0/1		 �Ƿ�ͨ��ͳһ�����֤��¼

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
