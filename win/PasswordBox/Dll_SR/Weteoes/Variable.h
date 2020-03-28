#pragma once
#ifndef VariableClass_H
#define VariableClass_H

#include <Weteoes/Application/Config.h>
#include <Weteoes/Application/RSA.h>
#include <Weteoes/Application/Web/WebOperating.h>
#include <Weteoes/Application/Web/WebBasic.h>

class VariableClass {
public:
	static ConfigClass configClass;
	static WebOperatingClass webOperatingClass;
	static RSAClass rsaClass;
	static ConfigDll configDll;
	static WebBasicClass webBasicClass;

private:
	static map<string, string> variable_map;
public: 
	static string getVariable(string key);
	static bool setVariable(string key, string value);
};
#endif