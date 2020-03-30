#include <pch.h>
#include "CreateXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/Application/XML.h>

bool CreateXMLConfigClass::UserAndPassword(const char* host, const char* user, const char* pass)
{
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a, true)) {
		return false;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		root = xml.NewElement(VariableClass::xmlClass.RootElementName.c_str());
	}
	tinyxml2::XMLElement* w_ = xml.NewElement("UserAndPassword");
	w_->SetAttribute("Host", host);
	w_->SetAttribute("User", user);
	w_->SetAttribute("Pass", pass);
	root->InsertEndChild(w_);
	xml.InsertEndChild(root);
	return VariableClass::xmlClass.SaveXML(xml, a);
}
