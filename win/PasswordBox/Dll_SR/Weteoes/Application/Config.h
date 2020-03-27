#ifndef ConfigClass__
#define ConfigClass__
#include <pch.h>
class ConfigClass
{
public:
	static ConfigClass use;
	static char* Socket_Header; //Socket Header String
public:
	std::string GetConfig(std::string& data, std::string flag = "_"); //获取配置(返回配置，减去源内容)
	std::string StrToLower(std::string); //String到小写
	std::vector<std::string> split(const std::string& s, char delimiter);

};
#endif // ConfigClass__