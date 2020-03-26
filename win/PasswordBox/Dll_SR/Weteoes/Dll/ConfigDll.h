#ifdef ConfigDll_
#else
#define ConfigDll_
#include <Windows.h>
class ConfigDllStruct {
public:
	struct UserConfig_ {
		char w[256];
	};
	struct ComputerConfig_ {
		char ComputerName[256];
		char Language[10];
	};
};

class ConfigDll
{
private:
#ifndef CreateConfig
	typedef bool(__stdcall *Config_CreateUser_)(char* w);
	typedef bool(__stdcall *Config_CreateComputer_)(char* ComputerName,char* Language);
#endif // !CreateConfig
#ifndef ReadConfig
	typedef ConfigDllStruct::UserConfig_(__stdcall *Config_ReadUser_)();
	typedef ConfigDllStruct::ComputerConfig_(__stdcall *Config_ReadComputer_)();
#endif // !CreateConfig
#ifndef SetConfig
	typedef bool(__stdcall *Config_SetComputer_)(char* menu,char* data);
#endif // !SetConfig

public:
	bool Loading();
	static Config_CreateUser_ Config_CreateUser;
	static Config_CreateComputer_ Config_CreateComputer;
	static Config_ReadUser_ Config_ReadUser;
	static Config_ReadComputer_ Config_ReadComputer;
	static Config_SetComputer_ Config_SetComputer;
};
#endif

