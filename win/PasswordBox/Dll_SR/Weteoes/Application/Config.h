#ifndef ConfigClass__
#define ConfigClass__
#include <Weteoes/Loading.h>
class ConfigClass
{
public:
	static ConfigClass use;
	static char* Socket_Header; //Socket Header String
public:
	std::string GetConfig(std::string& data, std::string flag = "_"); //��ȡ����(�������ã���ȥԴ����)
	std::string StrToLower(std::string); //String��Сд

};
#endif // ConfigClass__