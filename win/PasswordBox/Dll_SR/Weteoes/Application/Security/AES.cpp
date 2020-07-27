#include "pch.h"
#include "AES.h"
#include <Weteoes/More/openssl/include/openssl/aes.h>

std::string AESClass::aes_256_cbc_encode(std::string password, std::string data) {
	// 规则化密码
	password = getPassword(password);
	// 这里默认将iv全置为字符0
	unsigned char iv[AES_BLOCK_SIZE] = { '0','0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };

	AES_KEY aes_key;
	int i = AES_set_encrypt_key((const unsigned char*)password.c_str(), (int)password.length() * 8, &aes_key);
	if (AES_set_encrypt_key((const unsigned char*)password.c_str(), (int)password.length() * 8, &aes_key) < 0) {
		//assert(false);
		return "";
	}
	std::string strRet;
	std::string data_bak = data;
	unsigned int data_length = (unsigned int)data_bak.length();

	// ZeroPadding
	int padding = 0;
	if (data_bak.length() % (AES_BLOCK_SIZE) > 0)
	{
		padding = AES_BLOCK_SIZE - data_bak.length() % (AES_BLOCK_SIZE);
	}
	// 在一些软件实现中，即使是16的倍数也进行了16长度的补齐
	/*else
	{
		padding = AES_BLOCK_SIZE;
	}*/

	data_length += padding;
	while (padding > 0) {
		data_bak += '\0';
		padding--;
	}

	for (unsigned int i = 0; i < data_length / (AES_BLOCK_SIZE); i++) {
		std::string str16 = data_bak.substr(i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		unsigned char out[AES_BLOCK_SIZE];
		::memset(out, 0, AES_BLOCK_SIZE);
		AES_cbc_encrypt((const unsigned char*)str16.c_str(), out, AES_BLOCK_SIZE, &aes_key, iv, AES_ENCRYPT);
		strRet += std::string((const char*)out, AES_BLOCK_SIZE);
	}
	// base64
	std::string base64Data = WeteoesDll::Base64_Encode((char*)strRet.c_str(), (int)strRet.length());
	return base64Data;
}

std::string AESClass::aes_256_cbc_decode(std::string password, std::string strData) {
	// base64
	char* base64Data;
	int base64DataLen = WeteoesDll::Base64_UnEncode((char*)strData.c_str(), (int)strData.length(), base64Data);
	if (base64DataLen == 0) {
		return "";
	}
	std::string base64DataStr(base64Data, base64DataLen);
	strData = base64DataStr;
	// 规则化密码
	password = getPassword(password);
	// 这里默认将iv全置为字符0
	unsigned char iv[AES_BLOCK_SIZE] = { '0','0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' };

	AES_KEY aes_key;
	if (AES_set_decrypt_key((const unsigned char*)password.c_str(), (int)password.length() * 8, &aes_key) < 0) {
		//assert(false);
		return "";
	}
	std::string strRet;
	for (unsigned int i = 0; i < strData.length() / AES_BLOCK_SIZE; i++) {
		std::string str16 = strData.substr(i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		unsigned char out[AES_BLOCK_SIZE];
		::memset(out, 0, AES_BLOCK_SIZE);
		AES_cbc_encrypt((const unsigned char*)str16.c_str(), out, AES_BLOCK_SIZE, &aes_key, iv, AES_DECRYPT);
		strRet += std::string((const char*)out, AES_BLOCK_SIZE);
	}
	return strRet;
}

std::string AESClass::getPassword(std::string password) {
	int needLen = 16;
	if (password.length() > 24) {
		needLen = 32;
	}
	else if (password.length() > 16) {
		needLen = 24;
	}
	else {
		needLen = 16;
	}
	while (password.length() < needLen) {
		password += "6";
	}
	return password;
}
