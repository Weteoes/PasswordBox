#include <Weteoes/Loading.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/SRWDll.h>
#include <Weteoes/Application/CreateXMLConfig.h>
#include <Weteoes/Application/ReadXMLConfig.h>
#include <Weteoes/Application/SetXMLConfig.h>
#include <Weteoes/Application/ReturnXMLStruct.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!SRWDll().Loading()) { return false; }
	return true;
}

#ifndef CreateConfig
extern "C" _declspec(dllexport) bool Config_CreateUser(char* user) {
	if (!Loading()) { return false; }
	return CreateXMLConfigClass().User(user);
}
extern "C" _declspec(dllexport) bool Config_CreateComputer(char* ComputerName,char* Language) {
	if (!Loading()) { return false; }
	return CreateXMLConfigClass().Computer(ComputerName, Language);
}
#endif // !CreateConfig

#ifndef ReadConfig
extern "C" _declspec(dllexport) ReturnXMLStruct::UserConfig_ Config_ReadUser() {
	if (!Loading()) { return ReturnXMLStruct::UserConfig_(); }
	return ReadXMLConfigClass().User();
}
extern "C" _declspec(dllexport) ReturnXMLStruct::ComputerConfig_ Config_ReadComputer() {
	if (!Loading()) { return ReturnXMLStruct::ComputerConfig_(); }
	return ReadXMLConfigClass().Computer();
}
#endif // !ReadConfig

#ifndef SetConfig
extern "C" _declspec(dllexport) bool Config_SetComputer(char* menu,char* data) {
	if (!Loading()) { return false; }
	return SetXMLConfigClass().Computer(menu, data);
}
#endif // !SetConfig


