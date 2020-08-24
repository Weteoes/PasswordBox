#include <pch.h>

bool Loading() {
	if (!WeteoesDll::Ready()) { return false; }
	if (!ConfigDll::Ready()) { return false; }
	if (!LogDll::Ready()) { return false; }
	return true;
}

extern "C" _declspec(dllexport) bool SumbitConfig() {
	if (!Loading()) { return false; }
	return VariableClass::operatingClass.SumbitConfig();
}

extern "C" _declspec(dllexport) bool GetConfig() {
	if (!Loading()) { return false; }
	return VariableClass::operatingClass.GetConfig();
}

extern "C" _declspec(dllexport) bool PdLogin() {
	if (!Loading()) { return false; }
	return VariableClass::operatingClass.PdLoginSession();
}

extern "C" _declspec(dllexport) bool NetWorkisConnect() {
	if (!Loading()) { return false; }
	return VariableClass::operatingClass.NetWorkisConnect();
}

extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}