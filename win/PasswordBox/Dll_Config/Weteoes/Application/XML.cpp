#include <pch.h>
#include "XML.h"

bool XMLClass::GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file) {
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		// �����ļ�������
		WeteoesDll::IO_CreatePath((char*)file.c_str());
		tinyxml2::XMLDocument xml = CreateXML(file);
		return true;
	}
	std::string XmlDataEncode = WeteoesDll::IO_ReadFile((char*)file.c_str());
	std::string XmlData = VariableClass::xmlClass.ReadXmlParse(XmlDataEncode.c_str());
	if (xml.Parse(XmlData.c_str(), XmlData.length()) != 0) { return false; } //��ȡ�ļ�ʧ��
	return true;
}

void XMLClass::SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile) {
	tinyxml2::XMLPrinter s;
	xml.Accept(&s); //��ȡ���ݵ�����
	std::string data = s.CStr();
	char* XmlFile_C = (char*)XmlFile.c_str();
	if (WeteoesDll::IO_Exists(XmlFile_C)) {
		WeteoesDll::IO_Remove(XmlFile_C);
	}
	data = SRWDll::RSA_Encode((char*)data.c_str(), (char*)PublicKey.c_str());
	if (data.empty()) { return; }
	WeteoesDll::IO_WriteFile((char*)XmlFile.c_str(), (char*)data.c_str());
}

std::string XMLClass::ReadXmlParse(std::string data) {
	data = SRWDll::RSA_UnEncode((char*)data.c_str(), (char*)PrivateKey.c_str());
	if (data.empty()) { return ""; }
	return data;
}


tinyxml2::XMLDocument* XMLClass::CreateXML(std::string XMLPath) {
	static tinyxml2::XMLDocument xml;
	if (WeteoesDll::IO_Exists((char*)XMLPath.c_str())) { //����
		WeteoesDll::IO_Remove((char*)XMLPath.c_str()); //ɾ���ļ�
	}
	//�����������ʹ����������
	tinyxml2::XMLDeclaration* declaration = xml.NewDeclaration();
	xml.InsertFirstChild(declaration);
	return &xml;
}