#include <pch.h>
#include <sstream>
#include <Weteoes/Application/Security/RSA.h>
#include <Weteoes/Application/Sockets/WebSocket.h>

bool Loading_Management() {
	bool debug;
	string debug_s = ManagementDll::Get((char*)"Debug");
	if (debug_s.empty()) {
		return false;
	}
	istringstream(debug_s) >> debug;
	VariableClass::DEBUG = debug;
	return true;
}

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!ConfigDll().Loading()) { return false; }
	if (!ManagementDll().Loading()) { return false; }
	if (!Loading_Management()) { return false; }
	return true;
}

char* GetChars(std::string data_s) {
	int len = (int)data_s.length();
	char* result = (char*)malloc(sizeof(char) * len + 1);
	for (int i = 0; i < len; i++) {
		result[i] = data_s[i];
	}
	result[len] = '\0';
	return result;
}


extern "C" _declspec(dllexport) int Web_Entrance(const char* webPath) {
	if (!Loading()) { return NULL; }
	return WebSocketClass(webPath).Entrance();
}

extern "C" _declspec(dllexport) int RSA_Encode(char* data, int dataLen, char* key, char*& result) {
	if (!Loading()) { return NULL; }
	string a = VariableClass::rsaClass.Encode(string(data, dataLen), key);
	int l = (int)a.length();
	result = GetChars(a);
	return l;
}

extern "C" _declspec(dllexport) int RSA_UnEncode(char* data, int dataLen, char* key, char*& result) {
	if (!Loading()) { return NULL; }
	string a = VariableClass::rsaClass.UnEncode(string(data, dataLen), key);
	int l = (int)a.length();
	result = GetChars(a);
	return l;
}

extern "C" _declspec(dllexport) int AES_Encode(char* data, int dataLen, char* key, char*& result) {
	if (!Loading()) { return NULL; }
	string a = VariableClass::securityAESClass.Encryption(string(data, dataLen), key);
	int l = (int)a.length();
	result = GetChars(a);
	return l;
}

extern "C" _declspec(dllexport) int AES_UnEncode(char* data, int dataLen, char* key, char*& result) {
	if (!Loading()) { return NULL; }
	string a = VariableClass::securityAESClass.Decryption(string(data, dataLen), key);
	int l = (int)a.length();
	result = GetChars(a);
	return l;
}

extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}