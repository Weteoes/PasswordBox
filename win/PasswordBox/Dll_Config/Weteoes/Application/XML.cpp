#include <pch.h>
#include "XML.h"
#include <Weteoes\Application\ConfigFile.h>

bool XMLClass::GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file, bool isAes, bool replace) {
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		// �����ļ�������
		WeteoesDll::IO_CreatePath((char*)file.c_str());
		return CreateXML(xml, file);
	}
	char* result;
	int result_len = WeteoesDll::IO_ReadFile((char*)file.c_str(), result);
	std::string XmlData = string(result, result_len);
	// �Ƿ���Ҫ����
	if (isAes) {
		// ��ȡAES Key
		string aes = VariableClass::aesClass.getAESPassByFile(file);
		if (aes.empty()) { return false; }
		XmlData = VariableClass::xmlClass.ReadXmlParse(XmlData, aes);
	}
	if (xml.Parse(XmlData.c_str(), XmlData.length()) != 0) { 
		//��ȡ�ļ�ʧ��
		if (replace == true) {
			// �����Ҫ�滻
			return CreateXML(xml, file);
		}
		return false; 
	}
	return true;
}

void XMLClass::SetElementValue(tinyxml2::XMLDocument& xml, tinyxml2::XMLElement* rootElement, string key, string value) {
	tinyxml2::XMLElement* element = rootElement->FirstChildElement(key.c_str());
	if (!element) {
		// �Ҳ�������
		element = xml.NewElement(key.c_str());
		element->SetText(value.c_str());
		rootElement->InsertEndChild(element);
		xml.InsertEndChild(rootElement);
	}
	else {
		// �ҵ�����
		element->SetText(value.c_str());
	}
}

bool XMLClass::SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile, bool isAes) {
	tinyxml2::XMLPrinter s;
	xml.Accept(&s); //��ȡ���ݵ�����
	std::string data = s.CStr();
	char* XmlFile_C = (char*)XmlFile.c_str();
	// �Ƿ���Ҫ����
	if (isAes) {
		// ��ȡAES Key
		string aes = VariableClass::aesClass.getAESPassByFile(XmlFile);
		if (aes.empty()) { return false; }
		char* result;
		int result_l = SRWDll::AES_Encode((char*)data.c_str(), (int)data.length(), (char*)aes.c_str(), result);
		data = string(result, (size_t)result_l);
	}
	if (data.empty()) { return false; }
	if (WeteoesDll::IO_Exists(XmlFile_C)) {
		WeteoesDll::IO_Remove(XmlFile_C);
	}
	WeteoesDll::IO_WriteFile((char*)XmlFile.c_str(), (char*)data.c_str(), (int)data.length());
	return true;
}

std::string XMLClass::ReadXmlParse(std::string data, std::string aesPass) {
	// ����
	if (aesPass.empty()) { return ""; }
	char* result;
	int result_l = SRWDll::AES_UnEncode((char*)data.c_str(), (int)data.length(), (char*)aesPass.c_str(), result);
	data = string(result, (size_t)result_l);
	if (data.empty()) { return ""; }
	return data;
}

bool XMLClass::CreateXML(tinyxml2::XMLDocument& xml, std::string XMLPath) {
	if (WeteoesDll::IO_Exists((char*)XMLPath.c_str())) { //����
		WeteoesDll::IO_Remove((char*)XMLPath.c_str()); //ɾ���ļ�
	}
	//�����������ʹ����������
	tinyxml2::XMLDeclaration* declaration = xml.NewDeclaration();
	xml.InsertFirstChild(declaration);
	return true;
}