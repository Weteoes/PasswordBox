#include <pch.h>
#include "Log.h"

bool LogClass::Write(const char* msg) {
	std::string msgStr = std::string(msg);
	return WriteLog(msgStr);
}

bool LogClass::Info(const char* msg) {
	std::string msgStr = "[Info] " + std::string(msg) + "\n";
	return WriteLog(msgStr);
}

bool LogClass::WriteLog(std::string msgStr) {
	std::string logFile = WeteoesDll::Basics_GetNowFilePath() + VariableClass::logFile;
	if (!WeteoesDll::IO_Exists((char*)logFile.c_str())){
		// �ļ������ڣ������ļ���
		WeteoesDll::IO_CreatePath((char*)logFile.c_str());
	}
	// д����־
	WeteoesDll::IO_WriteFile(
		(char*)logFile.c_str(),
		(char*)msgStr.c_str(),
		(int)msgStr.length()
	);
	return true;
}