#include <pch.h>
#include "ManagementDll.h"

ManagementDll::Get_ ManagementDll::Get;

bool ManagementDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("Management.dll"));//����dll
	if (!dll) { MessageBox(NULL, TEXT("����Management-DLLʧ�� code:-1"), TEXT(""), MB_OK); return false; }
	Get =
		(Get_)GetProcAddress(dll, "Get");
	return true;
}