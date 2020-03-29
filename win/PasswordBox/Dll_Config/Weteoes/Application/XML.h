#include <pch.h>
#ifndef XMLClass_H
#define XMLClass_H
#include <Weteoes/More/tinyxml2/tinyxml2.h>

class XMLClass {
public:
	bool GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file); 
	bool SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile); // 保存XML

public:
	string RootElementName = "Weteoes";

private:
	tinyxml2::XMLDocument* CreateXML(std::string); // 创建XML
	std::string ReadXmlParse(std::string); // 解密XML


private:
	std::string RSA_PublicKey;
	std::string RSA_PrivateKey;
	bool Ready_RSA();
};
#endif