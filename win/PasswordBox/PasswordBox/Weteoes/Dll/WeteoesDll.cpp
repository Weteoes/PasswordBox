#include <pch.h>

#ifndef WeteoesDll_Cpp
#define WeteoesDll_Cpp

#include "WeteoesDll.h"

WeteoesDll::Basics_GetNowFilePath_ WeteoesDll::Basics_GetNowFilePath;
WeteoesDll::Basics_Replace_ WeteoesDll::Basics_Replace;
WeteoesDll::Basics_IsNum_ WeteoesDll::Basics_IsNum;
WeteoesDll::Basics_CharToUL_ WeteoesDll::Basics_CharToUL;
WeteoesDll::MD5_MD5File_ WeteoesDll::MD5_MD5File;
WeteoesDll::Http_HttpRequest_ WeteoesDll::Http_HttpRequest;
WeteoesDll::Convert_CharToLpcuwstr_ WeteoesDll::Convert_CharToLpcuwstr;
WeteoesDll::Convert_CharToBool_ WeteoesDll::Convert_CharToBool;
WeteoesDll::IO_WriteFile_ WeteoesDll::IO_WriteFile;
WeteoesDll::IO_ReadFile_ WeteoesDll::IO_ReadFile;
WeteoesDll::IO_CreatePath_ WeteoesDll::IO_CreatePath;
WeteoesDll::IO_Exists_ WeteoesDll::IO_Exists;
WeteoesDll::IO_Remove_ WeteoesDll::IO_Remove;
WeteoesDll::Regedit_CreateRegFile_ WeteoesDll::Regedit_CreateRegFile;
WeteoesDll::Regedit_CreateRegValue_ WeteoesDll::Regedit_CreateRegValue;
WeteoesDll::Regedit_QueryRegValue_ WeteoesDll::Regedit_QueryRegValue;
WeteoesDll::Regedit_QueryAddValue_ WeteoesDll::Regedit_QueryAddValue;
WeteoesDll::Regedit_OpenRegFile_ WeteoesDll::Regedit_OpenRegFile;
WeteoesDll::Process_AsUser_ WeteoesDll::Process_AsUser;
WeteoesDll::Process_GetProcessidFromName_ WeteoesDll::Process_GetProcessidFromName;
WeteoesDll::Process_SoftwareExist_ WeteoesDll::Process_SoftwareExist;
WeteoesDll::Base64_Encode_ WeteoesDll::Base64_Encode;
WeteoesDll::Base64_UnEncode_ WeteoesDll::Base64_UnEncode;
WeteoesDll::CMD_Run_ WeteoesDll::CMD_Run;

bool WeteoesDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("WeteoesDll.dll"));//����dll
	if (!dll) { MessageBox(NULL, TEXT("����WeteoesDLLʧ�� code:-1"), TEXT(""), MB_OK); return FALSE; }
	Basics_GetNowFilePath =
		(Basics_GetNowFilePath_)GetProcAddress(dll, "Basics_GetNowFilePath");
	Basics_Replace =
		(Basics_Replace_)GetProcAddress(dll, "Basics_Replace");
	Basics_IsNum =
		(Basics_IsNum_)GetProcAddress(dll, "Basics_IsNum");
	Basics_CharToUL =
		(Basics_CharToUL_)GetProcAddress(dll, "Basics_CharToUL");
	MD5_MD5File =
		(MD5_MD5File_)GetProcAddress(dll, "MD5_MD5File");
	Http_HttpRequest =
		(Http_HttpRequest_)GetProcAddress(dll, "Http_HttpRequest");
	Convert_CharToLpcuwstr =
		(Convert_CharToLpcuwstr_)GetProcAddress(dll, "Convert_CharToLpcuwstr");
	Convert_CharToBool =
		(Convert_CharToBool_)GetProcAddress(dll, "Convert_CharToBool");
	IO_WriteFile =
		(IO_WriteFile_)GetProcAddress(dll, "IO_WriteFile");
	IO_ReadFile =
		(IO_ReadFile_)GetProcAddress(dll, "IO_ReadFile");
	IO_CreatePath =
		(IO_CreatePath_)GetProcAddress(dll, "IO_CreatePath");
	IO_Exists =
		(IO_Exists_)GetProcAddress(dll, "IO_Exists");
	IO_Remove =
		(IO_Remove_)GetProcAddress(dll, "IO_Remove");
	Regedit_CreateRegFile =
		(Regedit_CreateRegFile_)GetProcAddress(dll, "Regedit_CreateRegFile");
	Regedit_CreateRegValue =
		(Regedit_CreateRegValue_)GetProcAddress(dll, "Regedit_CreateRegValue");
	Regedit_QueryRegValue =
		(Regedit_QueryRegValue_)GetProcAddress(dll, "Regedit_QueryRegValue");
	Regedit_QueryAddValue =
		(Regedit_QueryAddValue_)GetProcAddress(dll, "Regedit_QueryAddValue");
	Regedit_OpenRegFile =
		(Regedit_OpenRegFile_)GetProcAddress(dll, "Regedit_OpenRegFile");
	Process_AsUser =
		(Process_AsUser_)GetProcAddress(dll, "Process_AsUser");
	Process_GetProcessidFromName =
		(Process_GetProcessidFromName_)GetProcAddress(dll, "Process_GetProcessidFromName");
	Process_SoftwareExist =
		(Process_SoftwareExist_)GetProcAddress(dll, "Process_SoftwareExist");
	Base64_Encode =
		(Base64_Encode_)GetProcAddress(dll, "Base64_Encode");
	Base64_UnEncode =
		(Base64_UnEncode_)GetProcAddress(dll, "Base64_UnEncode");
	CMD_Run =
		(CMD_Run_)GetProcAddress(dll, "CMD_Run");
	return TRUE;
}
#endif