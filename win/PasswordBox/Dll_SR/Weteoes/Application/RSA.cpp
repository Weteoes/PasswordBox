#include <Weteoes/Loading.h>
#ifndef RSAClass_CPP
#define RSAClass_CPP
#include "RSA.h"
#include <Weteoes/More/openssl/include/openssl/ssl3.h>
#include <Weteoes/More/openssl/include/openssl/rsa.h>
#pragma comment(lib,"Weteoes/More/openssl/lib/libssl.lib")
#pragma comment(lib,"Weteoes/More/openssl/lib/libcrypto.lib")
#include <Weteoes/Dll/WeteoesDll.h>

std::string B_PublicKey = "-----BEGIN RSA PUBLIC KEY-----\nMIIBCgKCAQEA0pf6nAbz1e0q6gKxbdZUNvFsi5wn4hIPsb82dnac7o4Crfoz4KFc\n/MNavirwsjkCsNBTBPuFle5560yrPL5roXog4nfol/xAKi7D+zqJil+DUmNYqkN5\ngHnrPIT+r89WadJM4EKaOE/sKJ1dUF94VJnR+mD2k9WXa3YmW+eGxvPHbUh1aHFh\n1k1vgZOIBtNyXDDXH/sULQE1b+ZddMLdeIlrO0Wdvkg23mM76dSQmLH2WMF9XMgU\nUuHTUllMRwJdWQf/XAI8GLvEtMP88ZYsJso3c5z1VVi6Fmzqc/tJXKLBU4qT3NYU\ntBSkDP3lM2QV3W9zzlRIiplvQ8Fd90ZqVQIDAQAB\n-----END RSA PUBLIC KEY-----";
//std::string A_PrivateKey = "";
//std::string B_PublicKey = "";
std::string A_PrivateKey = "-----BEGIN RSA PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQCn6L5afDofSb/a\nhgTO4kvz5UvZi9m8iczvmVydsP4lUZ5CoSlfhbSo7bzeiUl4oUwSdZ0W6GwXSjE+\n9PKqNbTu2dpQy8iX54dE/N18+9CHxrQec5YzNrFeOi72+Euo2OwJou7oKaNvbdnW\nQM8OHfWsjiKikK0Q3bQRvohcVkQEodbIERjgw7opFoPJxIlOV7duhvsC/krX2f+q\noIP1ZUWUNtMEiLHGwnRj6eCKAcim5s8EGHlN+RAU9sgFGZsbQpm50QicpY8XAEPV\nMLq5CNGNmqFsx0Altj9De8lszBsIYpxkICFciRMw+cSp03ZuaIp/9TV+fI+5JfbF\n02JJNu5tAgMBAAECggEAQtQbjyAKchGETpEwsLbYzAXjHn7O9n9SFbrQZeLgBDJr\n7tD+CorI0MNufJPfridkg6RUFZ4EB3D8ELalLqGZlccXYTj6aZs493g9H1WKNcAc\nSFJw4YlPJtW5g4pncpiDuYIj3DtWVS8/mErLHi9GbJtVpaY3e5MB7F4NH9Ml10F9\nT6C+Iru38422hgWELxZgBO9tCnvBMBbSEyLecp5UesusmZ1Xr/H8RhlPnkuuNwtN\nBO74aqDj9hvT7Vl0ArSHHfZp0YdVDpIXH9tmynlfmrN6OUcn4zLk9db9OUdez2GY\n2JUSJEHHuGmIC2m4on0vxEBcVBgofymmtzv4gEfo8QKBgQDbk57DNezfhws/ndl0\nVHJh7DHTB47M1usk1LZh5b+WeVB5R1uM5pjpN11z5eb8dObqp/6w91xS2FBXJSuM\nWuQ6HZzCr8xMwlujAjdrYrDPe5rWYXjMwGeAwKBjmwPTgdYwbrfJof2Qrg6Av8rt\nAHNDofyhhpG3CdSa205LcJl04wKBgQDDwwzL9MhhfZixE0OWKudYTZ1pDYaKLNK5\nmrRfpFkZ1gA6M8tXEt3uVp4IxemaRZ0UXqcO3m5tyfrxZKWdGT40Fo5BDsucfLHD\nUAY9LojnI4RlmDp1BX3GAI+ZoxlYiVTyv5sJeZL4ESM+DjYxc2WmU/B8NodchOX4\nd6ocp2HAbwKBgHNpeSZkHrgy1B/BCT5S8Lg1nM6uB0n1oSz/vUlhqD0gUMMeVamO\nv0q99hnn+mwxyfoHCSDdM6K73iaf++7PC2zcibvvCTRDaEUa8iQ4gHTeJDmQjB0a\n+Iw9M1CHdxBiC0HzwBh0U8ILKsZTiQbfmLYw24fPIqIRwbUPlmyip5Y/AoGBALRD\nG7mDwjDjsoL8NjRFdZp+fgCKj+UUuUZoCsg3UkTUJolxwECCAxLBd+ykMiP5Dlf/\ngN3UPOOkJgu6njY3VGwqiPunYB7NQ/OR8OzNuQr+TaAvuUSgtdxqD9Ftup0oeKy/\ne0gSRx9eyJEQDR8kH+o1STFYFPVA+3L83gxcpUrJAoGBANTmKUgbMe60Q7vKyGkW\n/7Dyid2P4+RrOuKxEVhKTJNJGwugsTMaSp8xTcnbfV44gDTwWqChjZyV6rqU/tS4\nZRdBbkhlu3yrammQItniP/vDQZXcrKO0wkdNNM0oUGIXYlFzswY9mYoxNZyk/ODW\nr9wm8JgfALXkj6/M7kds2lid\n-----END RSA PRIVATE KEY-----";
int A_CharSize = 256; //A密钥Char大小
int B_CharSize = 256; //B密钥Char大小

std::string RSAClass::A_PublicEncode(std::string data) {
	std::string result = RSA_PublicEncode(data, B_PublicKey);
	char *a = (char*)malloc(sizeof(char)*result.length());
	GetChars(result, a);
	//result.copy(a, result.length(), 0);
	result = WeteoesDll::Base64_Encode(a, (int)result.length());
	return result;
}
std::string RSAClass::B_PrivateUnEncode(std::string data) {
	std::string result = std::string(WeteoesDll::Base64_UnEncode((char*)data.c_str(), (int)data.length()), B_CharSize);
	result = RSA_PrivateUnEncode(result, A_PrivateKey);
	return result;
}
std::string RSAClass::Encode(std::string data, std::string key) {
	std::string result = RSA_PublicEncode(data, key);
	char *a = (char*)malloc(sizeof(char)*result.length());
	GetChars(result, a);
	//result.copy(a, result.length(), 0);
	result = WeteoesDll::Base64_Encode(a, (int)result.length());
	return result;
}
void RSAClass::GetChars(std::string data_s, char* data_c) { //std::string to char*
	for (int i = 0; i < data_s.length(); i++) {
		data_c[i] = data_s[i];
	}
}
std::string RSAClass::UnEncode(std::string data, std::string key) {
	std::string result = std::string(WeteoesDll::Base64_UnEncode((char*)data.c_str(), (int)data.length()), B_CharSize);
	result = RSA_PrivateUnEncode(result, key);
	return result;
}

std::string RSAClass::RSA_PublicEncode(std::string data, const std::string &pubKey)
{
	std::string strRet;
	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);
	RSA* pRSAPublicKey = RSA_new();
	rsa = PEM_read_bio_RSAPublicKey(keybio, NULL, NULL, NULL);

	int len = RSA_size(rsa);
	char *encryptedText = new char[len + 1];
	//memset(encryptedText, 0, len + 1);

	// 加密函数 
	//int len1 = sizeof(data);
	int ret = RSA_public_encrypt((int)data.length(), (const unsigned char*)data.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(encryptedText, ret);

	// 释放内存   
	free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}
std::string RSAClass::RSA_PrivateUnEncode(std::string data, const std::string &privateKey)
{
	std::string strRet;
	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf((unsigned char *)privateKey.c_str(), -1);
	RSA* pRSAPrivateKey = RSA_new();
	rsa = PEM_read_bio_RSAPrivateKey(keybio, NULL, NULL, NULL);

	int len = RSA_size(rsa);
	char *encryptedText = new char[len + 1];
	//memset(encryptedText, 0, len + 1);

	// 加密函数   
	//int len1 = sizeof(data);
	int ret = RSA_private_decrypt((int)data.length(), (const unsigned char*)data.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(encryptedText, ret);

	// 释放内存 
	free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}
#endif