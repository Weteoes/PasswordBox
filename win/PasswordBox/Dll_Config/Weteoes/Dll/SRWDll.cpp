#include <pch.h>
#include "SRWDll.h"

SRWDll::Web_Entrance_ SRWDll::Web_Entrance;
SRWDll::RSA_Encode_ SRWDll::RSA_Encode;
SRWDll::RSA_UnEncode_ SRWDll::RSA_UnEncode;
SRWDll::AES_Encode_ SRWDll::AES_Encode;
SRWDll::AES_UnEncode_ SRWDll::AES_UnEncode;
SRWDll::Set_Variable_ SRWDll::Set_Variable;
SRWDll::Get_Variable_ SRWDll::Get_Variable;

bool SRWDll::Ready() {
	HMODULE dll = LoadLibrary(TEXT("SRW.dll")); //����dll
	if (!dll) { MessageBox(NULL, TEXT("����SRW-DLLʧ�� code:-1"), TEXT(""), MB_OK); return false; }
	Web_Entrance =  (Web_Entrance_)GetProcAddress(dll, "Web_Entrance");
	RSA_Encode =	(RSA_Encode_)GetProcAddress(dll, "RSA_Encode");
	RSA_UnEncode =  (RSA_UnEncode_)GetProcAddress(dll, "RSA_UnEncode");
	AES_Encode =	(AES_Encode_)GetProcAddress(dll, "AES_Encode");
	AES_UnEncode =  (AES_UnEncode_)GetProcAddress(dll, "AES_UnEncode");
	Set_Variable = (Set_Variable_)GetProcAddress(dll, "Set_Variable");
	Get_Variable =  (Get_Variable_)GetProcAddress(dll, "Get_Variable");
	return true;
}