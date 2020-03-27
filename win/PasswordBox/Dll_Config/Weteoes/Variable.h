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
};
#endif