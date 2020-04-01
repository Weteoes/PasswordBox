#include <pch.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/SRWDll.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!SRWDll().Loading()) { return false; }
	return true;
}

extern "C" _declspec(dllexport) bool Config_CreateUserAndPassword(const char* host, const char* user, const char* pass) {
	if (!Loading()) { return false; }
	return VariableClass::createXMLConfigClass.UserAndPassword(host, user, pass);
}

extern "C" _declspec(dllexport) ReturnXMLStruct::Struct_UserAndPassword Config_ReadUserAndPassword(const char* host) {
	if (!Loading()) { return ReturnXMLStruct::struct_UserAndPassword; }
	return VariableClass::readXMLConfigClass.ReadUserAndPassword(host);
}

extern "C++" _declspec(dllexport) vector<ReturnXMLStruct::Struct_UserAndPassword> Config_ReadAllUserAndPassword() {
	vector<ReturnXMLStruct::Struct_UserAndPassword> a;
	if (!Loading()) { return a; }
	return VariableClass::readXMLConfigClass.ReadAllUserAndPassword();
}

extern "C" _declspec(dllexport) bool Config_DelUserAndPassword(const char* host) {
	if (!Loading()) { return false; }
	return VariableClass::setXMLConfigClass.DelUserAndPassword(host);
}

extern "C" _declspec(dllexport) bool Config_Exsits() {
	if (!Loading()) { return false; }
	return WeteoesDll::IO_Exists((char*)ConfigFileClass::UserAndPassword.c_str());
}

extern "C" _declspec(dllexport) bool Config_SetAESPassword(char* pass) {
	if (!Loading()) { return false; }
	return VariableClass::aesClass.setPassword(pass);
}

extern "C" _declspec(dllexport) bool Config_ResetAESPassword(char* oldPass, char* newPass) {
	if (!Loading()) { return false; }
	return VariableClass::aesClass.resetPassword(oldPass, newPass);
}

extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}