#include <pch.h>

#ifndef CreateXMLConfigClass_H
#define CreateXMLConfigClass_H

#include <Weteoes/More/tinyxml2/tinyxml2.h>

class CreateXMLConfigClass {
public:
	bool CreateXML(string xmlFile);												// ����XMLģ���ļ�

public:
	bool UserAndPassword();														// �û��˻������ļ�(��������)
	bool Server();																// Server Session�����ļ�(��������)

private:
	tinyxml2::XMLElement* CreateXMLRoot(tinyxml2::XMLDocument& xml);			// ����XML���ڵ�
};
#endif 