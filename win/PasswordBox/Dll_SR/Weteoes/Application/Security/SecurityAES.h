#pragma once
#ifndef SecurityAES_H
#define SecurityAES_H
class SecurityAESClass {
public:
	string Encryption(string strSrc);
	string Decryption(string strSrc);

public:
	string key;

private:
	const char g_iv[17] = "weteoes"; // ECB MODE不需要关心chain，可以填空
};
#endif