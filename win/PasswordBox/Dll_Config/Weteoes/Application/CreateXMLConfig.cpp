#include "CreateXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/XML.h>
#include <Weteoes/Dll/WeteoesDll.h>

bool CreateXMLConfigClass::User(char* w)
{
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::User;
	WeteoesDll::IO_CreatePath((char*)a.c_str());
	XMLClass xmlClass;
	tinyxml2::XMLDocument xml = xmlClass.CreateXML(a);
	tinyxml2::XMLElement *root = xml.NewElement("Weteoes");
	tinyxml2::XMLElement *w_ = xml.NewElement("w"); w_->SetText(w);
	root->InsertEndChild(w_);
	xml.InsertFirstChild(root);
	SaveXML(xml, a);
	return true;
}
bool CreateXMLConfigClass::Computer(char* ComputerName,char* Language)
{
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::Computer;
	WeteoesDll::IO_CreatePath((char*)a.c_str());
	XMLClass xmlClass;
	tinyxml2::XMLDocument xml = xmlClass.CreateXML(a);
	tinyxml2::XMLElement *root = xml.NewElement("Weteoes");
	tinyxml2::XMLElement *XML_ComputerName = xml.NewElement("ComputerName"); XML_ComputerName->SetText(ComputerName);
	tinyxml2::XMLElement *XML_Language = xml.NewElement("Language"); XML_Language->SetText(Language);
	root->InsertEndChild(XML_ComputerName);
	root->InsertEndChild(XML_Language);
	xml.InsertFirstChild(root);
	SaveXML(xml, a);
	return true;
}
void CreateXMLConfigClass::SaveXML(tinyxml2::XMLDocument &xml, std::string XmlFile) {
	tinyxml2::XMLPrinter s;
	xml.Accept(&s); //获取内容到变量
	std::string s_ = s.CStr();
	XMLClass().SaveXML(XmlFile, s_);
}