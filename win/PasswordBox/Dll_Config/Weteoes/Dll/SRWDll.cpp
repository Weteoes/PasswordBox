#include <pch.h>
#ifndef SRWDll_CPP
#define SRWDll_CPP
#include "SRWDll.h"

SRWDll::Web_Entrance_ SRWDll::Web_Entrance;
SRWDll::Socket_Entrance_ SRWDll::Socket_Entrance;
SRWDll::RSA_Encode_ SRWDll::RSA_Encode;
SRWDll::RSA_UnEncode_ SRWDll::RSA_UnEncode;

bool SRWDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("SRW.dll"));//º”‘ÿdll
	if (!dll) { MessageBox(NULL, TEXT("º”‘ÿSRW-DLL ß∞‹ code:-1"), TEXT(""), MB_OK); return false; }
	Web_Entrance =
		(Web_Entrance_)GetProcAddress(dll, "Web_Entrance");
	Socket_Entrance =
		(Socket_Entrance_)GetProcAddress(dll, "Socket_Entrance");
	RSA_Encode =
		(RSA_Encode_)GetProcAddress(dll, "RSA_Encode");
	RSA_UnEncode =
		(RSA_UnEncode_)GetProcAddress(dll, "RSA_UnEncode");
	return true;
}
#endif