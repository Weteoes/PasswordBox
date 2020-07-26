#include <pch.h>

#ifndef AppConfigClass_H
#define AppConfigClass_H

class AppConfigClass
{
private:
	static std::string SoftwareName;
	static std::string Version;

public:
	std::string DlgInitURL = "/passwordBox/ui/1/init";
	std::string DlgLoginURL = "/passwordBox/ui/1/login";
	std::string DlgChangePasswordURL = "/passwordBox/ui/1/changePassword";
	std::string DlgMainURL = "/passwordBox/ui/2/main";
	std::string ServerLoginSSOLoginURL = "https://passwordbox.weteoes.cn/sso/redirect?url=";
	std::string ServerLoginSSOSuccessURL = "https://passwordbox.weteoes.cn/sso/login";

public:
	static std::string Get_SoftwareName();		// ��ȡ�����
	static std::string Get_Version();			// ��ȡ�汾
	static std::string Get_TempPath();			// ��ȡ��ʱ����λ��
};

#endif