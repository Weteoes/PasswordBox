#pragma once
#ifndef OperatingClass_
#define OperatingClass_

class OperatingClass {
public:
	bool SumbitConfig();				// 提交配置
	bool GetConfig();					// 获取配置
	bool PdLoginSession();				// 判断登录态是否正常

public:
	bool NetWorkisConnect();			// 判断网络是否连接
};
#endif