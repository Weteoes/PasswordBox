#include <pch.h>
#include <mutex>

// DLL操作事务锁
std::mutex dllMutex;

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!ServerDll().Loading()) { return false; }
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
	dllMutex.lock();
	bool result = VariableClass::setXMLConfigClass.UserAndPasswordAdd(host, user, pass);
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) ReturnXMLStruct::Struct_UserAndPassword Config_ReadUserAndPassword(const char* host) {
	if (!Loading()) { return ReturnXMLStruct::struct_UserAndPassword; }
	dllMutex.lock();
	ReturnXMLStruct::Struct_UserAndPassword result = VariableClass::readXMLConfigClass.ReadUserAndPassword(host);
	dllMutex.unlock();
	return result;
}

extern "C++" _declspec(dllexport) vector<ReturnXMLStruct::Struct_UserAndPassword> Config_ReadAllUserAndPassword() {
	vector<ReturnXMLStruct::Struct_UserAndPassword> a;
	if (!Loading()) { return a; }
	dllMutex.lock();
	vector<ReturnXMLStruct::Struct_UserAndPassword> result = VariableClass::readXMLConfigClass.ReadAllUserAndPassword();
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Config_DelUserAndPassword(const char* host) {
	if (!Loading()) { return false; }
	dllMutex.lock();
	bool result = VariableClass::setXMLConfigClass.UserAndPasswordDel(host);
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Config_ExsitsUserAndPassword() {
	if (!Loading()) { return false; }
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	return WeteoesDll::IO_Exists((char*)a.c_str());
}

extern "C" _declspec(dllexport) bool Config_ExsitsServer() {
	if (!Loading()) { return false; }
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::Server;
	return WeteoesDll::IO_Exists((char*)a.c_str());
}

extern "C" _declspec(dllexport) bool Config_SetAESPassword(char* pass) {
	if (!Loading()) { return false; }
	dllMutex.lock();
	bool result = VariableClass::aesClass.setPassword(pass);
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Config_ResetAESPassword(char* oldPass, char* newPass) {
	if (!Loading()) { return false; }
	dllMutex.lock();
	bool result = VariableClass::aesClass.resetPassword(oldPass, newPass);
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Config_ServerSetw(const char* w) {
	if (!Loading()) { return false; }
	dllMutex.lock();
	bool result = VariableClass::setXMLConfigClass.ServerSet("w", w);
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) int Config_ServerGetw(char* &w) {
	if (!Loading()) { return 0; }
	dllMutex.lock();
	std::string value = VariableClass::readXMLConfigClass.ServerGet("w");
	w = GetChars(value);
	dllMutex.unlock();
	return (int)value.length();
}



extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}







extern "C" _declspec(dllexport) bool Server_SumbitConfig() {
	if (!Loading()) { return false; }
	dllMutex.lock();
	bool result = ServerDll::SumbitConfig();
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Server_GetConfig() {
	if (!Loading()) { return false; }
	dllMutex.lock();
	bool result = ServerDll::GetConfig();
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Server_PdLogin() {
	if (!Loading()) { return false; }
	dllMutex.lock();
	bool result = ServerDll::PdLogin();
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Server_NetWorkisConnect() {
	if (!Loading()) { return false; }
	dllMutex.lock();
	bool result = ServerDll::NetWorkisConnect();
	dllMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Server_Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	return ServerDll::Set_Variable(key, value);
}

