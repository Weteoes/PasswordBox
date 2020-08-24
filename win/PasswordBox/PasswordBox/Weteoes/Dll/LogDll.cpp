#include <pch.h>
#include "LogDll.h"

LogDll::Info_ LogDll::Info;
LogDll::Write_ LogDll::Write;

bool LogDll::Ready() {
	HMODULE dll = LoadLibrary(TEXT("Log.dll"));//����dll
	if (!dll) { MessageBox(NULL, TEXT("����Log-DLLʧ�� code:-1"), TEXT(""), MB_OK); return false; }
	Info =	(Info_)		GetProcAddress(dll, "Info");
	Write = (Write_)	GetProcAddress(dll, "Write");
	return true;
}