#pragma once
#ifndef VariableClass_H
#define VariableClass_H
#include <Weteoes/Application/operating.h>

class VariableClass {
public:
	static OperatingClass operatingClass;

public:
	static std::string serverDomain;
	static std::string serverDomainPdLoginUrl;
	static std::string serverDomainConfigSumbitUrl;
	static std::string serverDomainConfigGetUrl;
	static int serverPort;
	static bool serverIsSSL;
	static std::string configFile;


private:
	static std::map<std::string, std::string> variable_map;

public:
	static std::string getVariable(std::string key);
	static bool setVariable(std::string key, std::string value);
};
#endif