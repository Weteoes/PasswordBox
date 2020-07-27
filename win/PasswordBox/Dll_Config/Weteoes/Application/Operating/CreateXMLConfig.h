#include <pch.h>

#ifndef CreateXMLConfigClass_H
#define CreateXMLConfigClass_H

#include <Weteoes/More/tinyxml2/tinyxml2.h>

class CreateXMLConfigClass {
public:
	bool CreateXML(string xmlFile);												// 创建XML模板文件

public:
	bool UserAndPassword();														// 用户账户配置文件(仅仅创建)
	bool Server();																// Server Session配置文件(仅仅创建)

private:
	tinyxml2::XMLElement* CreateXMLRoot(tinyxml2::XMLDocument& xml);			// 创建XML根节点
};
#endif 