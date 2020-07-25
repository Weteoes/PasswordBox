#include "json.h"
#ifndef WJson_
#define WJson_

#ifdef _DEBUG
#pragma comment(lib,"Json/debug/jsoncpp.lib")
#else
#pragma comment(lib,"Json/releasae/jsoncpp.lib")
#endif

class WJsonClass
{
public:
	static Json::Value GetJson(char*);

};
#endif