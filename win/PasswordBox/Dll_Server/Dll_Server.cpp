#include <pch.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	return true;
}

extern "C" _declspec(dllexport) bool SumbitConfig() {
	if (!Loading()) { return false; }
	VariableClass::operatingClass.sumbitConfig();
	return true;
}

extern "C" _declspec(dllexport) bool GetConfig() {
	if (!Loading()) { return false; }
	VariableClass::operatingClass.getConfig();
	return true;
}

extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}