#include <pch.h>
#include "CreateXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/Application/XML.h>

bool CreateXMLConfigClass::CreateXML(string xmlFile) {
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, xmlFile, true)) {
		return false;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		root = CreateXMLRoot(xml);
	}
	xml.InsertEndChild(root);
	return VariableClass::xmlClass.SaveXML(xml, xmlFile);
}

bool CreateXMLConfigClass::UserAndPassword() {
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	return CreateXML(a);
}

bool CreateXMLConfigClass::Server() {
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::Server;
	return CreateXML(a);
}

tinyxml2::XMLElement* CreateXMLConfigClass::CreateXMLRoot(tinyxml2::XMLDocument& xml) {
	return xml.NewElement(VariableClass::xmlClass.RootElementName.c_str());
}
