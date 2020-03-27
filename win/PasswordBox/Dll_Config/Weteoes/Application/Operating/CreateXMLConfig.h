#include <pch.h>

#ifndef CreateXMLConfigClass_H
#define CreateXMLConfigClass_H

#include <Weteoes/More/tinyxml2/tinyxml2.h>

class CreateXMLConfigClass {
public:
	bool UserAndPassword(const char* host, const char* user, const char* pass); // 用户账户配置文件
};
#endif 