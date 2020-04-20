#include <pch.h>
#ifndef XMLClass_H
#define XMLClass_H
#include <Weteoes/More/tinyxml2/tinyxml2.h>

class XMLClass {
public:
	bool GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file, bool replace = false);
	void SetElementValue(tinyxml2::XMLDocument& xml, tinyxml2::XMLElement* rootElement, string key, string value); // 设置节点内容
	bool SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile); // 保存XML

public:
	string RootElementName = "Weteoes";

private:
	bool CreateXML(tinyxml2::XMLDocument& xml, std::string XMLPath); // 创建XML
	std::string ReadXmlParse(std::string); // 解密XML


private:
	std::string RSA_PublicKey;
	std::string RSA_PrivateKey;
};
#endif