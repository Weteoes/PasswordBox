#ifndef ConfigClass__
#define ConfigClass__
#include <pch.h>
class ConfigClass
{
public:
	static ConfigClass use;
	static char* Socket_Header; //Socket Header String
public:
	std::string GetConfig(std::string& data, std::string flag = "_"); //��ȡ����(�������ã���ȥԴ����)
	std::string StrToLower(std::string); //String��Сд
	std::vector<std::string> split(const std::string& s, char delimiter);

};
#endif // ConfigClass__