#pragma once
#ifndef LoginSSOClass_
#define LoginSSOClass_
class LoginSSOClass {
public:
	void Loginin(CefRefPtr<CefBrowser> browser);
	void Cookie(std::string key, std::string value);

public:
	bool PdLogin();						// �ж��Ƿ�ͳһ�����֤��¼ͨ��
	bool GetServerConfig();				// ��ȡ�����������ļ�
	bool SumbitServerConfig();			// �ύ�����������ļ�

private:
	bool SetLoginSession(std::string w);
};
#endif