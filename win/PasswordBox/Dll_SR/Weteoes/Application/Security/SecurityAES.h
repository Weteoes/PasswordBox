#pragma once
#ifndef SecurityAES_H
#define SecurityAES_H
class SecurityAESClass {
public:
	string Encryption(string strSrc, string key);
	string Decryption(string strSrc, string key);

private:
	const char g_iv[17] = "Weteoes"; // ECB MODE����Ҫ����chain���������
};
#endif