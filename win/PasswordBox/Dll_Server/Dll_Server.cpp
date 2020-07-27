#include <pch.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	return true;
}

extern "C" _declspec(dllexport) bool SumbitConfig() {
	if (!Loading()) { return false; }
	return VariableClass::operatingClass.sumbitConfig();
}

extern "C" _declspec(dllexport) bool GetConfig() {
	if (!Loading()) { return false; }
	return VariableClass::operatingClass.getConfig();
}

extern "C" _declspec(dllexport) bool PdLogin() {
	if (!Loading()) { return false; }
	return VariableClass::operatingClass.pdLoginSession();
}

extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}