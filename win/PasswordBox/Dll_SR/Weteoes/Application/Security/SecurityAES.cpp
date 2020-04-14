#include <pch.h>
#include "AES.h"
#include "SecurityAES.h"


string SecurityAESClass::Encryption(string strSrc) {
	size_t length = strSrc.length();
	int block_num = (int)length / BLOCK_SIZE + 1;
	//明文
	char* szDataIn = new char[(INT64)block_num * BLOCK_SIZE + 1];
	memset(szDataIn, 0x00, (INT64)block_num * BLOCK_SIZE + 1);
	strcpy_s(szDataIn, (INT64)block_num * BLOCK_SIZE + 1, strSrc.c_str());

	//进行PKCS7Padding填充。
	int k = (int)length % BLOCK_SIZE;
	int j = (int)length / BLOCK_SIZE;
	int padding = BLOCK_SIZE - k;
	for (int i = 0; i < padding; i++) {
		szDataIn[j * BLOCK_SIZE + k + i] = padding;
	}
	szDataIn[block_num * BLOCK_SIZE] = '\0';

	//加密后的密文
	char* szDataOut = new char[(INT64)block_num * BLOCK_SIZE + 1];
	memset(szDataOut, 0, (INT64)block_num * BLOCK_SIZE + 1);

	//进行进行AES的CBC模式加密
	AES aes;
	aes.MakeKey(key.c_str(), g_iv, 16, 16);
	aes.Encrypt(szDataIn, szDataOut, (INT64)block_num * BLOCK_SIZE, AES::CBC);

	string str(WeteoesDll::Base64_Encode(szDataOut, block_num * BLOCK_SIZE));
	delete[] szDataIn;
	delete[] szDataOut;
	return str;
}

string SecurityAESClass::Decryption(string strSrc) {
	char* result;
	int result_len = WeteoesDll::Base64_UnEncode((char*)strSrc.c_str(), (int)strSrc.length(), result);
	string strData(result, result_len);
	size_t length = strData.length();
	//密文
	char* szDataIn = new char[length + 1];
	memcpy(szDataIn, strData.c_str(), length);
	//明文
	char* szDataOut = new char[length + 1];
	memcpy(szDataOut, strData.c_str(), length + 1);

	//进行AES的CBC模式解密
	AES aes;
	aes.MakeKey(key.c_str(), g_iv, 16, 16);
	aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);

	//去PKCS7Padding填充
	if (0x00 < szDataOut[length - 1] && szDataOut[length - 1] <= 0x16) {
		int tmp = szDataOut[length - 1];
		for (int i = (int)length - 1; i >= length - tmp; i--) {
			if (szDataOut[i] != tmp) {
				memset(szDataOut, 0, length);
				break;
			}
			else
				szDataOut[i] = 0;
		}
	}
	string strDest(szDataOut);
	delete[] szDataIn;
	delete[] szDataOut;
	return strDest;
}
