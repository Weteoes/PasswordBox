#include <pch.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/SRWDll.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!SRWDll().Loading()) { return false; }
	return true;
}

char* GetChars(std::string data_s) { //std::string to char* 不能public因为std::string
	int len = (int)data_s.length();
	char* result = (char*)calloc(len + 1, sizeof(char));
	for (int i = 0; i < len; i++) {
		result[i] = data_s[i];
	}
	result[len] = '\0';
	return result;
}

extern "C" _declspec(dllexport) bool Config_CreateUserAndPassword(const char* host, const char* user, const char* pass) {
	if (!Loading()) { return false; }
	return VariableClass::setXMLConfigClass.UserAndPasswordAdd(host, user, pass);
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
	return VariableClass::setXMLConfigClass.UserAndPasswordDel(host);
}

extern "C" _declspec(dllexport) bool Config_Exsits() {
	if (!Loading()) { return false; }
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	return WeteoesDll::IO_Exists((char*)a.c_str());
}

extern "C" _declspec(dllexport) bool Config_SetAESPassword(char* pass) {
	if (!Loading()) { return false; }
	return VariableClass::aesClass.setPassword(pass);
}

extern "C" _declspec(dllexport) bool Config_ResetAESPassword(char* oldPass, char* newPass) {
	if (!Loading()) { return false; }
	return VariableClass::aesClass.resetPassword(oldPass, newPass);
}

extern "C" _declspec(dllexport) bool Config_ServerSetw(const char* w) {
	if (!Loading()) { return false; }
	return VariableClass::setXMLConfigClass.ServerSet("w", w);
}

extern "C" _declspec(dllexport) int Config_ServerGetw(char* &w) {
	if (!Loading()) { return 0; }
	std::string value = VariableClass::readXMLConfigClass.ServerGet("w");
	w = GetChars(value);
	return (int)value.length();
}

extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}