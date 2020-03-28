#include <pch.h>
#include "ReadXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/Application/XML.h>
#include "ReturnXMLStruct.h"

ReturnXMLStruct::Struct_UserAndPassword ReadXMLConfigClass::ReadUserAndPassword(const char* host) {
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
		return ReturnXMLStruct::struct_UserAndPassword;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		return ReturnXMLStruct::struct_UserAndPassword;
	}
	vector<ReturnXMLStruct::Struct_UserAndPassword> list = ReadAllUserAndPassword();
	for (int i = 0; i < list.size(); i++) {
		if (string(list[i].Host) == host) {
			return list[i];
		}
	}
	return ReturnXMLStruct::struct_UserAndPassword;
}

vector<ReturnXMLStruct::Struct_UserAndPassword> ReadXMLConfigClass::ReadAllUserAndPassword() {
	vector<ReturnXMLStruct::Struct_UserAndPassword> result;
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
		return result;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		return result;
	}
	for (XMLElement* currentele = root->FirstChildElement(); currentele; currentele = currentele->NextSiblingElement()) {
		XMLElement* onlyElement = currentele;
		ReturnXMLStruct::Struct_UserAndPassword onlyElementStruct;
		string onlyElement_Host = onlyElement->Attribute("Host");
		string onlyElement_User = onlyElement->Attribute("User");
		string onlyElement_Pass = onlyElement->Attribute("Pass");
		strcpy_s(onlyElementStruct.Host, onlyElement_Host.c_str());
		strcpy_s(onlyElementStruct.User, onlyElement_User.c_str());
		strcpy_s(onlyElementStruct.Pass, onlyElement_Pass.c_str());
		result.push_back(onlyElementStruct);
	}
	return result;
}