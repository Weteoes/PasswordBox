#include "pch.h"
#include "Operating.h"
#include "Wininet.h"

bool OperatingClass::SumbitConfig() {
    // �ж���������
    if (!NetWorkisConnect()) { return false; }
    // ����
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

    LogInfo("SumbitConfig JSON:" + a);
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
	if (json != NULL) {
		int all = json.size();
		if (all == 0) { return false; }
		int code = json["code"].asInt();
        if (code == 0) { return true; }
	}
    return false;
}


bool OperatingClass::GetConfig() {
    // �ж���������
    if (!NetWorkisConnect()) { return false; }
    // ����
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
    std::string a = HttpOperatingClass::HttpRequest(
        VariableClass::serverDomain, 
        VariableClass::serverPort, 
        VariableClass::serverDomainConfigGetUrl, 
        "", 
        "POST", 
        VariableClass::serverIsSSL, 
        cookies
    );

    // LogInfo("GetConfig JSON:" + a);
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

bool OperatingClass::PdLoginSession() {
    // �ж���������
    if (!NetWorkisConnect()) { return false; }
    // ����
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
    std::string a = HttpOperatingClass::HttpRequest(
        VariableClass::serverDomain,
        VariableClass::serverPort,
        VariableClass::serverDomainPdLoginUrl,
        "",
        "POST",
        VariableClass::serverIsSSL,
        cookies
    );

    LogInfo("PdLoginSession JSON:" + a);
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
    if (json != NULL) {
        int all = json.size();
        if (all == 0) { return false; }
        int code = json["code"].asInt();
        if (code == 0) { return true; }
    }
    return false;
}

// �ж������Ƿ�����
bool OperatingClass::NetWorkisConnect() {
    // �жϱ�������״̬
    bool result = false;
    for (int i = 0; i < 6; i++) {
        DWORD flag;
        bool con = InternetGetConnectedState(&flag, 0);
        if (!con) { 
            Sleep(1000);
            continue; 
        }
        else { break; }
    }

    // �ж���ҳ������״̬
    for (int i = 0; i < 6; i++) {
        std::string a = HttpOperatingClass::HttpRequest(
            VariableClass::serverDomain,
            VariableClass::serverPort,
            "",
            "",
            "POST",
            VariableClass::serverIsSSL
        );
        if (a.empty()) {
            Sleep(1000);
            continue;
        }
        else { 
            result = true;
            break; 
        }
    }

    // Log
    if (result) {
        LogInfo("NetWorkisConnect Yes");
    }
    else {
        LogInfo("NetWorkisConnect No");
    }
    return result;
}

void OperatingClass::LogInfo(std::string msg) {
    msg = "[Dll_Server] OperatingClass::" + msg;
    LogDll::Info(msg.c_str());
}