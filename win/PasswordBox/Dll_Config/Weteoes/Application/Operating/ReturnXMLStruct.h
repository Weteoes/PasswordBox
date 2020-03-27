#ifndef ReturnXMLStruct_H
#define ReturnXMLStruct_H
class ReturnXMLStruct //用户自定义类型
{
public:
	struct Struct_UserAndPassword {
		char Host[255];
		char User[255];
		char Pass[255];
	};

	static ReturnXMLStruct::Struct_UserAndPassword struct_UserAndPassword;
};
#endif
