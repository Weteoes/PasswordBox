#include <pch.h>
#include "SetXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/Application/XML.h>


bool SetXMLConfigClass::UserAndPasswordAdd(const char* host, const char* user, const char* pass) {
	std::string file = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, file)) { return false; }
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) { return false; }

	tinyxml2::XMLElement* w_ = xml.NewElement("UserAndPassword");
	w_->SetAttribute("Host", host);
	w_->SetAttribute("User", user);
	w_->SetAttribute("Pass", pass);
	root->InsertEndChild(w_);
	xml.InsertEndChild(root);
	return VariableClass::xmlClass.SaveXML(xml, file);
}

bool SetXMLConfigClass::UserAndPasswordDel(const char* host) {
	std::string file = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, file)) { return false; }
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) { return false; }

	for (XMLElement* currentele = root->FirstChildElement(); currentele; currentele = currentele->NextSiblingElement()) {
		XMLElement* onlyElement = currentele;
		string onlyElement_Host = onlyElement->Attribute("Host");
		if (onlyElement_Host == host) {
			root->DeleteChild(onlyElement);
			VariableClass::xmlClass.SaveXML(xml, file);
			return true;
		}
	}
	return false;
}







bool SetXMLConfigClass::ServerSet(const char* key, const char* value) {
	std::string file = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::Server;
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		VariableClass::createXMLConfigClass.Server();
	}
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, file)) { return false; }
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) { return false; }
	VariableClass::xmlClass.SetElementValue(xml, root, key, value);
	return VariableClass::xmlClass.SaveXML(xml, file);
}
