#include <pch.h>
#include <Weteoes/Application/Convert.h>

// std::string to char* ���ܹ���DLL��Ϊstd::string����C����
char* ConvertClass::GetChars(std::string data_s) {
	int len = (int)data_s.length();
	char* result = (char*)malloc(sizeof(char) * len + 1);
	for (int i = 0; i < len; i++) {
		result[i] = data_s[i];
	}
	result[len] = '\0';
	return result;
}