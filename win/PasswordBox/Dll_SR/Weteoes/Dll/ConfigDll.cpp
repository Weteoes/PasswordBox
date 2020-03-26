#include <Weteoes/Loading.h>
#include "ConfigDll.h"

ConfigDll::Config_CreateUser_ ConfigDll::Config_CreateUser;
ConfigDll::Config_CreateComputer_ ConfigDll::Config_CreateComputer;
ConfigDll::Config_ReadUser_ ConfigDll::Config_ReadUser;
ConfigDll::Config_ReadComputer_ ConfigDll::Config_ReadComputer;
ConfigDll::Config_SetComputer_ ConfigDll::Config_SetComputer;

bool ConfigDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("Config.dll"));//º”‘ÿdll
	if (!dll) { MessageBox(NULL, TEXT("º”‘ÿConfig-DLL ß∞‹ code:-1"), TEXT(""), MB_OK); return false; }
	Config_CreateUser =
		(Config_CreateUser_)GetProcAddress(dll, "Config_CreateUser");
	Config_CreateComputer =
		(Config_CreateComputer_)GetProcAddress(dll, "Config_CreateComputer");
	Config_ReadUser =
		(Config_ReadUser_)GetProcAddress(dll, "Config_ReadUser");
	Config_ReadComputer =
		(Config_ReadComputer_)GetProcAddress(dll, "Config_ReadComputer");
	Config_SetComputer =
		(Config_SetComputer_)GetProcAddress(dll, "Config_SetComputer");
	return true;
}