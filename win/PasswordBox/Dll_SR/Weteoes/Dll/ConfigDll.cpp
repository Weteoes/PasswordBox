#include <pch.h>
#include "ConfigDll.h"

ConfigDll::Config_CreateUserAndPassword_	ConfigDll::Config_CreateUserAndPassword;
ConfigDll::Config_ReadUserAndPassword_	 	ConfigDll::Config_ReadUserAndPassword;
ConfigDll::Config_ReadAllUserAndPassword_	ConfigDll::Config_ReadAllUserAndPassword;
ConfigDll::Config_DelUserAndPassword_		ConfigDll::Config_DelUserAndPassword;

ConfigDll::Config_ExsitsUserAndPassword_	ConfigDll::Config_ExsitsUserAndPassword;
ConfigDll::Config_ExsitsServer_				ConfigDll::Config_ExsitsServer;

ConfigDll::Config_SetAESPassword_			ConfigDll::Config_SetAESPassword;
ConfigDll::Config_ResetAESPassword_			ConfigDll::Config_ResetAESPassword;

ConfigDll::Config_ServerSetw_				ConfigDll::Config_ServerSetw;
ConfigDll::Config_ServerGetw_				ConfigDll::Config_ServerGetw;

ConfigDll::Set_Variable_					ConfigDll::Set_Variable;


// 代理ServerDll
ConfigDll::Server_SumbitConfig_				ConfigDll::Server_SumbitConfig;
ConfigDll::Server_GetConfig_				ConfigDll::Server_GetConfig; 
ConfigDll::Server_NetWorkisConnect_			ConfigDll::Server_NetWorkisConnect;
ConfigDll::Server_PdLogin_					ConfigDll::Server_PdLogin;

ConfigDll::Server_Set_Variable_				ConfigDll::Server_Set_Variable;

bool ConfigDll::Ready() {
	HMODULE dll = LoadLibrary(TEXT("Config.dll"));//加载dll
	if (!dll) { MessageBox(NULL, TEXT("加载Config-DLL失败 code:-1"), TEXT(""), MB_OK); return false; }
	Config_CreateUserAndPassword =  (Config_CreateUserAndPassword_)		GetProcAddress(dll, "Config_CreateUserAndPassword");
	Config_ReadUserAndPassword =    (Config_ReadUserAndPassword_)		GetProcAddress(dll, "Config_ReadUserAndPassword");
	Config_ReadAllUserAndPassword = (Config_ReadAllUserAndPassword_)	GetProcAddress(dll, "Config_ReadAllUserAndPassword");
	Config_DelUserAndPassword =     (Config_DelUserAndPassword_)		GetProcAddress(dll, "Config_DelUserAndPassword");

	Config_ExsitsUserAndPassword =	(Config_ExsitsUserAndPassword_)		GetProcAddress(dll, "Config_ExsitsUserAndPassword");
	Config_ExsitsServer =			(Config_ExsitsServer_)				GetProcAddress(dll, "Config_ExsitsServer");

	Config_SetAESPassword =			(Config_SetAESPassword_)			GetProcAddress(dll, "Config_SetAESPassword");
	Config_ResetAESPassword =		(Config_ResetAESPassword_)			GetProcAddress(dll, "Config_ResetAESPassword");


	Config_ServerSetw =				(Config_ServerSetw_)				GetProcAddress(dll, "Config_ServerSetw");
	Config_ServerGetw =				(Config_ServerGetw_)				GetProcAddress(dll, "Config_ServerGetw");

	Set_Variable =					(Set_Variable_)						GetProcAddress(dll, "Set_Variable");


	// 代理ServerDll
	Server_SumbitConfig =			(Server_SumbitConfig_)				GetProcAddress(dll, "Server_SumbitConfig");
	Server_GetConfig =				(Server_GetConfig_)					GetProcAddress(dll, "Server_GetConfig");
	Server_PdLogin =				(Server_PdLogin_)					GetProcAddress(dll, "Server_PdLogin");
	Server_NetWorkisConnect =		(Server_NetWorkisConnect_)			GetProcAddress(dll, "Server_NetWorkisConnect");

	Server_Set_Variable =			(Server_Set_Variable_)				GetProcAddress(dll, "Server_Set_Variable");
	return true;
}