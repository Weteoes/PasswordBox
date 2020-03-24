#include <Weteoes/Loading.h>

//App
#include <Weteoes/Application/Management.h>
#include <Weteoes/Application/Convert.h>

extern "C" _declspec(dllexport) char* Get(char* a) {
	std::string b = ManagementClass().Get(a);
	return ConvertClass().GetChars(b);
}