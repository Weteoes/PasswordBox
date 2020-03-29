#pragma once
#ifndef VariableClass_H
#define VariableClass_H
#include <Weteoes/Application/XML.h>
#include <Weteoes/Application/Operating/CreateXMLConfig.h>
#include <Weteoes/Application/Operating/ReadXMLConfig.h>
#include <Weteoes/Application/Operating/SetXMLConfig.h>

class VariableClass {
public:
	static XMLClass xmlClass;
	static CreateXMLConfigClass createXMLConfigClass;
	static ReadXMLConfigClass readXMLConfigClass;
	static SetXMLConfigClass setXMLConfigClass;

private:
	static map<string, string> variable_map;
public:
	static string getVariable(string key);
	static bool setVariable(string key, string value);
};
#endif