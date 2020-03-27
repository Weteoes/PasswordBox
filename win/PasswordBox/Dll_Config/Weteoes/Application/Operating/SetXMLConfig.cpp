#include <pch.h>
#include "SetXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/Application/XML.h>

bool SetXMLConfigClass::DelUserAndPassword(const char* host) {
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
		return false;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		return false;
	}
	for (XMLElement* currentele = root->FirstChildElement(); currentele; currentele = currentele->NextSiblingElement()) {
		XMLElement* onlyElement = currentele;
		string onlyElement_Host = onlyElement->Attribute("Host");
		if (onlyElement_Host == host) {
			root->DeleteChild(onlyElement);
			VariableClass::xmlClass.SaveXML(xml, a);
			return true;
		}
	}
	return false;
}