#pragma once
#ifndef VariableClass_H
#define VariableClass_H

#include <Weteoes/Application/Config.h>
#include <Weteoes/Application/RSA.h>
#include <Weteoes/Application/Web/WebOperating.h>

class VariableClass {
public:
	static ConfigClass configClass;
	static WebOperatingClass webOperatingClass;
	static RSAClass rsaClass;
	static ConfigDll configDll;
};
#endif