#include <pch.h>

#ifndef AppConfigClass_H
#define AppConfigClass_H

class AppConfigClass
{
private:
	static std::string SoftwareName;
	static std::string Version;

public:
	static std::string Get_SoftwareName();		// 获取软件名
	static std::string Get_Version();			// 获取版本
	static std::string Get_TempPath();			// 获取临时数据位置
};

#endif