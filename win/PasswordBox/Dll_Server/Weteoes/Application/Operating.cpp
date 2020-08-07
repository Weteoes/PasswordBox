#include "pch.h"
#include "Operating.h"

bool OperatingClass::sumbitConfig() {
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
    std::string a = HttpOperatingClass::HttpRequestUpdateFile(
        VariableClass::serverDomain, 
        VariableClass::serverPort, 
        VariableClass::serverDomainConfigSumbitUrl, 
        VariableClass::configFile, 
        "POST", 
        VariableClass::serverIsSSL, 
        cookies
    );
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
	if (json != NULL) {
		int all = json.size();
		if (all == 0) { return false; }
		int code = json["code"].asInt();
        if (code == 0) { return true; }
	}
    return false;
}


bool OperatingClass::getConfig() {
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
    std::string a = HttpOperatingClass::HttpRequestUpdateFile(
        VariableClass::serverDomain, 
        VariableClass::serverPort, 
        VariableClass::serverDomainConfigGetUrl, 
        "", 
        "POST", 
        VariableClass::serverIsSSL, 
        cookies
    );
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
    if (json != NULL) {
        int all = json.size();
        if (all == 0) { return false; }
        int code = json["code"].asInt();
        if (code == 0) { 
            std::string configServerData = json["config"].asString();
            // ������û����
            if (configServerData.empty()) { return false; }
            char* configFileChar = (char*)VariableClass::configFile.c_str();
            // �ж��ļ��Ƿ����
            if (WeteoesDll::IO_Exists(configFileChar)) {
                // �ж������Ƿ���ͬ
                char* configFileData;
                int configFileDataLen = WeteoesDll::IO_ReadFile(configFileChar, configFileData);
                std::string configFileDataStr(configFileData, configFileDataLen);
                if (configFileDataStr != configServerData) {
                    // ����ͬ������Ҫ���ǣ�����
                    CopyFile(configFileChar, (VariableClass::configFile + ".bak").c_str(), false);
                    WeteoesDll::IO_Remove(configFileChar);
                }
                else {
                    // ��ͬ���ݲ��ø���
                    return true;
                }
            }
            WeteoesDll::IO_WriteFile(
                configFileChar,
                (char*)configServerData.c_str(),
                (int)configServerData.length()
            );
            return true; 
        }
    }
    return false;
}

bool OperatingClass::pdLoginSession() {
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
    std::string a = HttpOperatingClass::HttpRequestUpdateFile(
        VariableClass::serverDomain,
        VariableClass::serverPort,
        VariableClass::serverDomainPdLoginUrl,
        "",
        "POST",
        VariableClass::serverIsSSL,
        cookies
    );
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
    if (json != NULL) {
        int all = json.size();
        if (all == 0) { return false; }
        int code = json["code"].asInt();
        if (code == 0) { return true; }
    }
    return false;
}