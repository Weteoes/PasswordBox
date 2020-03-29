#include <pch.h>
#include "Variable.h"

XMLClass VariableClass::xmlClass;
CreateXMLConfigClass VariableClass::createXMLConfigClass;
ReadXMLConfigClass VariableClass::readXMLConfigClass;
SetXMLConfigClass VariableClass::setXMLConfigClass;


map<string, string> VariableClass::variable_map;
// ����			 ����		 ��ע
// AES_Password 		     AES

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
