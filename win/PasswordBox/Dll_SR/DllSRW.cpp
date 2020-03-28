#include <pch.h>
#include <Weteoes/Application/RSA.h>
#include <Weteoes/Application/Sockets/WebSocket.h>


bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!ConfigDll().Loading()) { return false; }
	if (!ManagementDll().Loading()) { return false; }
	return true;
}

static std::string TEMP_S;
extern "C" _declspec(dllexport) int Web_Entrance(const char* webPath) {
	if (!Loading()) { return NULL; }
	return WebSocketClass(webPath).Entrance();
}

extern "C" _declspec(dllexport) char* RSA_Encode(char* data, char* key) {
	if (!Loading()) { return NULL; }
	TEMP_S = RSAClass().Encode(data, key);
	return (char*)TEMP_S.c_str();
}

extern "C" _declspec(dllexport) char* RSA_UnEncode(char* data, char* key) {
	if (!Loading()) { return NULL; }
	TEMP_S = RSAClass().UnEncode(data, key);
	return (char*)TEMP_S.c_str();
}

extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}