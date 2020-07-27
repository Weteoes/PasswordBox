#include <pch.h>
#include "Variable.h"

using namespace std;

OperatingClass VariableClass::operatingClass;


std::string VariableClass::serverDomain = "passwordbox.weteoes.cn";
std::string VariableClass::serverDomainPdLoginUrl = "/sso/login";
std::string VariableClass::serverDomainConfigSumbitUrl = "/config/sumbit";
std::string VariableClass::serverDomainConfigGetUrl = "/config/get";
int VariableClass::serverPort = 443;
bool VariableClass::serverIsSSL = true;
std::string VariableClass::configFile = "Config/UserAndPassword.xml";



map<string, string> VariableClass::variable_map;
// ����			 ����		 ��ע
//  w			  *			 ͳһ��¼��Ϣ

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
