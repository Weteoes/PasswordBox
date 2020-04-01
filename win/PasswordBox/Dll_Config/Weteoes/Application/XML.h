#include <pch.h>
#ifndef XMLClass_H
#define XMLClass_H
#include <Weteoes/More/tinyxml2/tinyxml2.h>

class XMLClass {
public:
	bool GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file, bool replace = false);
	bool SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile); // ����XML

public:
	string RootElementName = "Weteoes";

private:
	bool CreateXML(tinyxml2::XMLDocument& xml, std::string XMLPath); // ����XML
	std::string ReadXmlParse(std::string); // ����XML


private:
	std::string RSA_PublicKey;
	std::string RSA_PrivateKey;
};
#endif