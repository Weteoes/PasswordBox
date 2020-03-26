#include <Weteoes/Loading.h>
#include "ManagementDll.h"

ManagementDll::Get_ ManagementDll::Get;

bool ManagementDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("Management.dll"));//º”‘ÿdll
	if (!dll) { MessageBox(NULL, TEXT("º”‘ÿManagement-DLL ß∞‹ code:-1"), TEXT(""), MB_OK); return false; }
	Get =
		(Get_)GetProcAddress(dll, "Get");
	return true;
}