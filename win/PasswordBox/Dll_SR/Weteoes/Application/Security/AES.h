#pragma once
#ifndef AESClass_
#define AESClass_
class AESClass {
public:
	std::string aes_256_cbc_encode(std::string password, std::string data);
	std::string aes_256_cbc_decode(std::string password, std::string strData);

private:
	std::string getPassword(std::string);
};
#endif