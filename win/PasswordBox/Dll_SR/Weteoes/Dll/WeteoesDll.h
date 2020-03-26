#ifdef WeteoesDll_
#else
#define WeteoesDll_
#include <Windows.h>
/*
	Process_AsUser 需要管理员权限
	Regedit_* || CMD_Run 可以不需要管理员权限，但是个别功能受限
*/
class WeteoesDll
{
private:
	typedef char*(__stdcall *Basics_GetNowFilePath_)();
	typedef char*(__stdcall *Basics_Replace_)(char* str, char* oldChar, char* newChar);
	typedef bool(__stdcall *Basics_IsNum_)(char*);
	typedef char*(__stdcall *Basics_CharToUL_)(char*, bool ToUpper);
	typedef char*(__stdcall *MD5_MD5File_)(char*);
	typedef char*(__stdcall *Http_HttpRequest_)(char* Url, short Port, char* lpUrl, char* Method, char* lpPostData, int nPostDataLen);
	typedef LPCUWSTR(__stdcall *Convert_CharToLpcuwstr_)(char*);
	typedef bool(__stdcall *Convert_CharToBool_)(char*);
	typedef void(__stdcall *IO_WriteFile_)(char* file, char* data);
	typedef char*(__stdcall *IO_ReadFile_)(char*);
	typedef void(__stdcall *IO_CreatePath_)(char*);
	typedef bool(__stdcall *IO_Exists_)(char*);
	typedef void(__stdcall *IO_Remove_)(char*);
	typedef HKEY(__stdcall *Regedit_CreateRegFile_)(HKEY Key, char* FileName);
	typedef bool(__stdcall *Regedit_CreateRegValue_)(HKEY Key, char* KeyName, char* KeyValue, DWORD KeyType, bool WriteIsNum);
	typedef char*(__stdcall *Regedit_QueryRegValue_)(HKEY Key, char* KeyName, DWORD KeyType, bool ReadIsNum);
	typedef bool(__stdcall *Regedit_QueryAddValue_)(HKEY Key, char* KeyName, char* KeyValue, DWORD KeyType, bool ReadIsNum);
	typedef HKEY(__stdcall *Regedit_OpenRegFile_)(HKEY MainPath, char* FileName);
	typedef char*(__stdcall *Process_AsUser_)(char* file, char* SoftwareName);
	typedef int*(__stdcall *Process_GetProcessidFromName_)(char* name,int *count);
	typedef bool(__stdcall *Process_SoftwareExist_)(char* name, char* title);
	typedef char*(__stdcall *Base64_Encode_)(char* data, int length);
	typedef char*(__stdcall *Base64_UnEncode_)(char* data, int length);
	typedef char*(__stdcall *CMD_Run_)(char* shell);

public:
	bool Loading();
	static Basics_GetNowFilePath_ Basics_GetNowFilePath; //获取当前运行位置
	static Basics_Replace_ Basics_Replace; //替换字符串
	static Basics_IsNum_ Basics_IsNum; //判断是否是数字
	static Basics_CharToUL_ Basics_CharToUL; //Char*到大小写
	static MD5_MD5File_ MD5_MD5File; //文件MD5
	static Http_HttpRequest_ Http_HttpRequest; //HTTP访问
	static Convert_CharToLpcuwstr_ Convert_CharToLpcuwstr;
	static Convert_CharToBool_ Convert_CharToBool;
	static IO_WriteFile_ IO_WriteFile;
	static IO_ReadFile_ IO_ReadFile;
	static IO_CreatePath_ IO_CreatePath;
	static IO_Exists_ IO_Exists;
	static IO_Remove_ IO_Remove;
	static Regedit_CreateRegFile_ Regedit_CreateRegFile; //注册表创建子键
	static Regedit_CreateRegValue_ Regedit_CreateRegValue; //注册表创建Value
	static Regedit_QueryRegValue_ Regedit_QueryRegValue; //注册表读取Value
	static Regedit_QueryAddValue_ Regedit_QueryAddValue; //注册表追加Value
	static Regedit_OpenRegFile_ Regedit_OpenRegFile; //注册表打开子键
	static Process_AsUser_ Process_AsUser; //通过管理员启动某程序(成功返回Seccess，反则错误信息)
	static Process_GetProcessidFromName_ Process_GetProcessidFromName; //检查某进程是否存在
	static Process_SoftwareExist_ Process_SoftwareExist; //检查软件是否运行中(通过进程名和标题)
	static Base64_Encode_ Base64_Encode; //Base64加密
	static Base64_UnEncode_ Base64_UnEncode; //Base64解密
	static CMD_Run_ CMD_Run; //运行CMD命令
};
#endif