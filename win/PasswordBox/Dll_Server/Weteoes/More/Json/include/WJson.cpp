#include "pch.h"

Json::Value WJsonClass::GetJson(char* data) {
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	Json::Value root;
	JSONCPP_STRING error;
	if (reader->parse(data, data + strlen(data), &root, &error)) {
		return root;
	}
	return NULL;
}