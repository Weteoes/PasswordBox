#include <pch.h>
#include "ConfigDll.h"

ConfigDll::Config_CreateUserAndPassword_	ConfigDll::Config_CreateUserAndPassword;
ConfigDll::Config_ReadUserAndPassword_	 	ConfigDll::Config_ReadUserAndPassword;
ConfigDll::Config_ReadAllUserAndPassword_	ConfigDll::Config_ReadAllUserAndPassword;
ConfigDll::Config_DelUserAndPassword_		ConfigDll::Config_DelUserAndPassword;
ConfigDll::Config_Exsits_					ConfigDll::Config_Exsits;
ConfigDll::Config_SetAESPassword_			ConfigDll::Config_SetAESPassword;
ConfigDll::Config_ResetAESPassword_			ConfigDll::Config_ResetAESPassword;
ConfigDll::Set_Variable_					ConfigDll::Set_Variable;

bool ConfigDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("Config.dll"));//º”‘ÿdll
	if (!dll) { MessageBox(NULL, TEXT("º”‘ÿConfig-DLL ß∞‹ code:-1"), TEXT(""), MB_OK); return false; }
	Config_CreateUserAndPassword =  (Config_CreateUserAndPassword_)		GetProcAddress(dll, "Config_CreateUserAndPassword");
	Config_ReadUserAndPassword =    (Config_ReadUserAndPassword_)		GetProcAddress(dll, "Config_ReadUserAndPassword");
	Config_ReadAllUserAndPassword = (Config_ReadAllUserAndPassword_)	GetProcAddress(dll, "Config_ReadAllUserAndPassword");
	Config_DelUserAndPassword =     (Config_DelUserAndPassword_)		GetProcAddress(dll, "Config_DelUserAndPassword");
	Config_Exsits =					(Config_Exsits_)					GetProcAddress(dll, "Config_Exsits");
	Config_SetAESPassword =			(Config_SetAESPassword_)			GetProcAddress(dll, "Config_SetAESPassword");
	Config_ResetAESPassword =		(Config_ResetAESPassword_)			GetProcAddress(dll, "Config_ResetAESPassword");
	Set_Variable =					(Set_Variable_)						GetProcAddress(dll, "Set_Variable");
	return true;
}