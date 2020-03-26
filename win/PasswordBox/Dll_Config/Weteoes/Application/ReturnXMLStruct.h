#include <Weteoes/Loading.h>

#ifdef ReturnXMLStruct_
#else
#define ReturnXMLStruct_
class ReturnXMLStruct //用户自定义类型
{
public:
	struct UserConfig_ {
		char w[256];
	};
	struct ComputerConfig_ {
		char ComputerName[256];
		char Language[10];
	};
	static ReturnXMLStruct::UserConfig_ UserConfig;
	static ReturnXMLStruct::ComputerConfig_ ComputerConfig;
};
#endif
