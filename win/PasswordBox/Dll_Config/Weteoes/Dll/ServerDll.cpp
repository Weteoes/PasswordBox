#include <pch.h>
#include "ServerDll.h"

ServerDll::SumbitConfig_			ServerDll::SumbitConfig;
ServerDll::GetConfig_				ServerDll::GetConfig;
ServerDll::PdLogin_					ServerDll::PdLogin;

ServerDll::Set_Variable_			ServerDll::Set_Variable; 

bool ServerDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("Server.dll"));//º”‘ÿdll
	if (!dll) { MessageBox(NULL, TEXT("º”‘ÿServer-DLL ß∞‹ code:-1"), TEXT(""), MB_OK); return false; }
	SumbitConfig =			(SumbitConfig_)				GetProcAddress(dll, "SumbitConfig");
	GetConfig =				(GetConfig_)				GetProcAddress(dll, "GetConfig");
	PdLogin =				(PdLogin_)					GetProcAddress(dll, "PdLogin");

	Set_Variable =			(Set_Variable_)				GetProcAddress(dll, "Set_Variable");
	return true;
}
