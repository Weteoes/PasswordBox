#include <Weteoes/Loading.h>

#ifdef ReturnXMLStruct_
#else
#define ReturnXMLStruct_
class ReturnXMLStruct //�û��Զ�������
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
