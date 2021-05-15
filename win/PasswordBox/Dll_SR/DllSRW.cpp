#include <pch.h>
#include <sstream>
#include <Weteoes/Application/Security/RSA.h>
#include <Weteoes/Application/Sockets/WebSocket.h>

bool ReadyDll() {
	if (!WeteoesDll::Ready()) { return false; }
	if (!ConfigDll::Ready()) { return false; }
	if (!ManagementDll::Ready()) { return false; }
	if (!ApplicationExports::Ready()) { return false; }
	return true;
}

bool ReadyVariableMap() {
	static bool first = true;
	if (!first) {
		return true;
	}
	first = false;
	VariableClass::setVariable("LoginIn", "0");				// 是否已经登录（全局登录判断）
	VariableClass::setVariable("isSSOLogin", "0");			// 是否统一身份认证登录
	return true;
}

bool Ready() {
	if (!ReadyDll()) { return false; }
	if (!ReadyVariableMap()) { return false; }
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
	if (!Ready()) { return NULL; }
	return WebSocketClass(webPath).Entrance();
}

extern "C" _declspec(dllexport) int RSA_Encode(char* data, int dataLen, char* key, char*& result) {
	if (!Ready()) { return NULL; }
	string a = VariableClass::rsaClass.Encode(string(data, dataLen), key);
	int l = (int)a.length();
	result = GetChars(a);
	return l;
}

extern "C" _declspec(dllexport) int RSA_UnEncode(char* data, int dataLen, char* key, char*& result) {
	if (!Ready()) { return NULL; }
	string a = VariableClass::rsaClass.UnEncode(string(data, dataLen), key);
	int l = (int)a.length();
	result = GetChars(a);
	return l;
}

extern "C++" _declspec(dllexport) int AES_Encode(char* data, int dataLen, char* key, char*& result) {
	if (!Ready()) { return NULL; }
	string data_s = string(data, dataLen);
	string a = VariableClass::aesClass.aes_256_cbc_encode(std::string(key), data_s);
	int l = (int)a.length();
	result = GetChars(a);
	return l;
}

extern "C++" _declspec(dllexport) int AES_UnEncode(char* data, int dataLen, char* key, char*& result) {
	if (!Ready()) { return NULL; }
	string data_s = string(data, dataLen);
	string a = VariableClass::aesClass.aes_256_cbc_decode(std::string(key), data_s);
	int l = (int)a.length();
	result = GetChars(a);
	return l;
}

extern "C" _declspec(dllexport) bool Set_Variable(char* key, char* value) {
	if (!Ready()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}

extern "C" _declspec(dllexport) char* Get_Variable(char* key) {
	if (!Ready()) { return NULL; }
	return GetChars(VariableClass::getVariable(key));
}